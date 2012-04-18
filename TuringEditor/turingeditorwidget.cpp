#include "turingeditorwidget.h"

#include <QtDebug>
#include <QPalette>
#include <QRegExp>
#include <QSettings>
#include <QFile>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>

// for min
#include <algorithm>

#include <Qsci/qscistyle.h>

#include "mainwindow.h"
#include "Qsci/qscilexer.h"
#include "turinglexer.h"

//! override various editor defaults
TuringEditorWidget::TuringEditorWidget(QWidget *parent) :
    QsciScintilla(parent)
{
    lex = new TuringLexer(this);
    setLexer(lex);

    readSettings();

    setFolding(QsciScintilla::PlainFoldStyle);
    setAutoIndent(true);
    setIndentationsUseTabs(false);
    setBackspaceUnindents(true);

    setCallTipsStyle(QsciScintilla::CallTipsNoContext);
    setCallTipsVisible(0);
    setAutoCompletionCaseSensitivity(false);
    setAutoCompletionUseSingle(QsciScintilla::AcusExplicit);

    // line wrapping
    SendScintilla(QsciScintillaBase::SCI_SETWRAPMODE,QsciScintillaBase::SC_WRAP_WORD);
    SendScintilla(QsciScintillaBase::SCI_SETWRAPVISUALFLAGS,QsciScintillaBase::SC_WRAPVISUALFLAG_START);
    SendScintilla(QsciScintillaBase::SCI_SETWRAPINDENTMODE,QsciScintillaBase::SC_WRAPINDENT_INDENT);

    // multi-cursor support
    SendScintilla(QsciScintillaBase::SCI_SETMULTIPLESELECTION,true);
    SendScintilla(QsciScintillaBase::SCI_SETMULTIPASTE,1);
    SendScintilla(QsciScintillaBase::SCI_SETADDITIONALSELECTIONTYPING,true);

    markerDefine(QsciScintilla::RightArrow,1);
    setAnnotationDisplay(QsciScintilla::AnnotationBoxed);
    indicatorDefine(QsciScintilla::SquiggleIndicator,2);
    indicatorDefine(QsciScintilla::BoxIndicator,3);
    setIndicatorForegroundColor(QColor(50,250,50),3);

    darkErrMsgStyle = new QsciStyle(-1,"dark error style",QColor(255,220,220),QColor(184,50,50),QFont());
    lightErrMsgStyle = new QsciStyle(-1,"light error style",Qt::black,QColor(230,150,150),QFont());
}

void TuringEditorWidget::readSettings() {
    // load lexer settings
    lex->loadSettings();

    // load editor settings
    QSettings settings;    

    confirmSave = settings.value("confirmSave",true).toBool();

    //setMarginLineNumbers(0,settings.value("showLineNumbers",true).toBool());

    QString theme = settings.value("theme", "Default").toString();
    if(theme == "Dark") {
        darkTheme();
    } else {
        lightTheme();
    }

    setTabWidth(settings.value("indentSize", 4).toInt());
    setAutoCompletionThreshold(settings.value("autoCompleteThreshold", 5).toInt());

    bool autoComp = settings.value("autoCompleteEnabled",true).toBool();
    setAutoCompletionSource(autoComp ? QsciScintilla::AcsAll : QsciScintilla::AcsNone);
}

void TuringEditorWidget::replaceSlot(QString repText) {
    replace(repText);
}
//! Selects the first appearance of a string and sets it up for the find next command.
void TuringEditorWidget::find(QString findText,bool caseSensitive,bool regex,bool wholeWord) {
    findFirst(findText,regex,caseSensitive,wholeWord,true);
}
//! Replaces all occurences of a string in the current document.
//! the regex and greedyRegex switches are to allow regex matching.
void TuringEditorWidget::replaceAll(QString findText,QString repText,bool regex,bool greedyRegex)
{
    QString docText = text();
    if(regex){
        QRegExp findRE(findText);
        findRE.setMinimal(!greedyRegex);
        docText.replace(findRE, repText);
    } else {
        docText.replace(findText,repText);
    }
    setText(docText);
}
//! Places a green box indicator around all occurences of a string.
void TuringEditorWidget::findAll(QString findText)
{
    QString docText = text();
    int end = docText.lastIndexOf(findText);
    int cur = -1; // so when it does the first +1 it starts at the beginning

    SendScintilla(QsciScintillaBase::SCI_INDICATORCLEARRANGE,0,length());
    SendScintilla(QsciScintillaBase::SCI_SETINDICATORCURRENT,3);

    if(end != -1){ // end is -1 if the text is not found
        while(cur != end) {
            cur = docText.indexOf(findText,cur+1);

            //SendScintilla(QsciScintillaBase::SCI_SETINDICATORCURRENT,QsciScintillaBase::INDIC_ROUNDBOX);
            SendScintilla(QsciScintillaBase::SCI_INDICATORFILLRANGE,cur,findText.length());
        }
    }
}

void TuringEditorWidget::findNextOccurence() {
    findNext();
}

//! Switch to the dark coding theme. Based on the common "Twilight" theme
void TuringEditorWidget::darkTheme() {
    qDebug() << "Switching to dark theme";
    lex->setTheme("Dark");
    setCaretForegroundColor(QColor(167,167,167));
    setSelectionBackgroundColor(QColor(221,240,255,45));
    clearErrors();
}
//! Switch to the dark coding theme. Based on the theme used
//! in the original Turing editor.
void TuringEditorWidget::lightTheme() {
    qDebug() << "Switching to light theme";
    lex->setTheme("Default");
    setCaretForegroundColor(QColor(0,0,0));
    setSelectionForegroundColor(palette().color(QPalette::HighlightedText));
    setSelectionBackgroundColor(palette().color(QPalette::Highlight));
    clearErrors();
}
//! Uses a scintilla annotation to display an error box below a certain line.
//! if from and to are provided a squiggly underline is used.
//! From and to are character indexes into the line.
//! If to is greater than the line length it will wrap.
void TuringEditorWidget::showError(int line,QString errMsg,int from, int to)
{
    markerAdd(line,1);
    QsciStyle *errStyle = lex->getTheme() == "Dark" ? darkErrMsgStyle : lightErrMsgStyle;
    annotate(line,"^ " + errMsg,*errStyle);

    if(from >= 0 && to >= 0) {
        fillIndicatorRange(line,from,line,to,2);
    }

    ensureLineVisible(line); // scroll to it
    hasMessage = true;
}
//! removes all error annotations from display.
void TuringEditorWidget::clearErrors() {
    clearAnnotations();
    clearIndicatorRange(0,0,lines(),text(lines()).length(),2);
    markerDeleteAll(1);

    hasMessage = false;
    // hack to get tab updated
    emit modificationChanged(isModified());
}

//! clears all annotations, markers and indicators
void TuringEditorWidget::clearEverything() {
    clearAnnotations();
    clearIndicatorRange(0,0,lines(),text(lines()).length(),-1);
    markerDeleteAll(-1);

    hasMessage = false;
    // hack to get tab updated
    emit modificationChanged(isModified());
}

bool TuringEditorWidget::saveFile(const QString &newFileName, bool temporary)
{
    QFile file(newFileName);
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("Open Turing Editor"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(newFileName)
                             .arg(file.errorString()));
        return false;
    }

    if (!temporary) fileName = newFileName;

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << text();
    QApplication::restoreOverrideCursor();
    if (!temporary) setModified(false);

    return true;
}

bool TuringEditorWidget::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save Program","",
                                                    tr("Turing Files (*.t *.ti *.tu)"));
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

bool TuringEditorWidget::save()
{
    if (fileName.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(fileName);
    }
}

bool TuringEditorWidget::maybeSave()
{
    if (confirmSave && isModified()) {
        int ret = QMessageBox::warning(this, tr("Open Turing Editor"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Yes | QMessageBox::Default,
                     QMessageBox::No,
                     QMessageBox::Cancel | QMessageBox::Escape);
        if (ret == QMessageBox::Yes)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

/*!
DEPRECATED

Returns a structure stack of pairs.
The first element in each pair is the indentation level.
Second is the structure identifier.
Each stack element represents an unclosed structure.

stopLine is the line to stop parsing at.

when stopLine is 0 it will parse the entire document.

when stopLine is 0 it should return an empty stack if all
the structures in the document are closed.

stopIsStruct is set to true when stopLine contains a construct
*/
QStack<QPair<int,QString> > TuringEditorWidget::makeStack(int stopLine, bool *stopIsStruct) {
    // stack for structs. string is identifier
    QStack<QPair<int,QString> > structStack;

    QRegExp endRegex("[\\t ]*end[\\t ]+([_a-zA-Z0-9]+).*");
    QRegExp funcRegex("[\\t ]*(body +|pervasive +)*(proc|procedure|fcn|function|class|module)[\\t\\* ]+([_a-zA-Z0-9]+).*");
    QRegExp structRegex("[\\t ]*(if|for|loop|case|record|monitor|union|handler).*");

    // used to set stopIsStruct
    bool lastLineWasStruct = false;

    // Stops either at the stop line or the end of the document
    int lastLine;
    if(stopLine >= 0) {
        lastLine = std::min(lines()-1,stopLine);
    } else {
        lastLine = lines();
    }
    for(int i = 0; i <= lastLine;++i) {
        QString line = text(i);
        if(endRegex.exactMatch(line)) {
            // pop assumes non-empty stack
            if (!structStack.isEmpty()) {
                QStringList captures = endRegex.capturedTexts();
                QPair<int,QString> beginning = structStack.pop();

                // if beginning identifier doesn't match end
                if(beginning.second != captures[1]) {
                    showError(i,tr("Ending identifier %1 does not match %2").arg(captures[1],beginning.second));
                }
            }
            lastLineWasStruct = false;
        } else if(funcRegex.exactMatch(line)) {
            QPair<int,QString> decl;
            QStringList captures = funcRegex.capturedTexts();
            decl.first = indentation(i);
            decl.second = captures[3];
            structStack.push(decl);
            lastLineWasStruct = true;

        } else if(structRegex.exactMatch(line)) {
            QPair<int,QString> decl;
            QStringList captures = structRegex.capturedTexts();
            decl.first = indentation(i);
            decl.second = captures[1];
            structStack.push(decl);
            lastLineWasStruct = true;
        } else {
            // just a plain 'ol line
            lastLineWasStruct = false;
        }
    }

    // if not null set it
    if(stopIsStruct != NULL) {
        *stopIsStruct = lastLineWasStruct;
    }

    return structStack;
}

QList<TuringEditorWidget::POILine*> TuringEditorWidget::findPOIs() {
    // stack for structs. string is identifier
    QList<TuringEditorWidget::POILine*> pois;

    QRegExp endRegex("^[\\t ]*end[\\t ]+([_a-zA-Z0-9]+).*");
    QRegExp funcRegex("^[\\t ]*(body +|pervasive +)*(proc|procedure|fcn|function|class|module|process|monitor)[\\t\\* ]+([_a-zA-Z0-9]+).*");
    QRegExp structRegex("[\\t ]*(if|for|loop|case|record|union|handler)( .*)?\\s*");

    // -1 to account for zero-indexing
    int lastLine = lines()-1;

    for(int i = 0; i <= lastLine;++i) {
        QString line = text(i);
        TuringEditorWidget::POILine *curLine = new TuringEditorWidget::POILine();
        curLine->indent = indentation(i);
        curLine->line = i;
        if(endRegex.exactMatch(line)) {
            QStringList captures = endRegex.capturedTexts();

            curLine->type = "end";
            curLine->id = captures[1];


            // find the beginning struct
            for(int j = pois.size() - 1;j >= 0;--j) {
                TuringEditorWidget::POILine *poi = pois[j];
                // is it not closed and the end tag matches?
                // FIXME poi->type == curLine->id allows "end proc"
                if(poi->other == NULL && poi->type != "end" &&
                        (poi->id == curLine->id || poi->type == curLine->id)) {
                    // we have found our beginning. Link it.
                    poi->other = curLine;
                    curLine->other = poi;
                    break;
                }
            }

            pois.append(curLine);
        } else if(funcRegex.exactMatch(line)) {
            QStringList captures = funcRegex.capturedTexts();
            curLine->type = captures[2];
            curLine->id = captures[3];
            pois.append(curLine);

        } else if(structRegex.exactMatch(line)) {
            QStringList captures = structRegex.capturedTexts();
            curLine->type = captures[1];
            pois.append(curLine);
        }
    }

    return pois;
}

/*! inserts the end of the closest open struct.

  I.E
  proc Foo
    something()
    <completeStruct called>
  end Foo < --- this is inserted

  Returns a QString which contains an error message or a blank string
  if nothing went wrong.
*/
QString TuringEditorWidget::completeStruct() {

    int curLine,dummyCursorPos;
    getCursorPosition(&curLine,&dummyCursorPos);

    QList<TuringEditorWidget::POILine *> pois;
    pois = findPOIs(); // TODO FIXME memory leaked

    beginUndoAction();

    TuringEditorWidget::POILine *toComplete = NULL;
    foreach(TuringEditorWidget::POILine *poi, pois) {
        if(poi->line > curLine) break; // -1 for zero indexing
        // if it's a beginning and isn't linked to an end
        if(poi->type != "end" && poi->other == NULL) {
            toComplete = poi;
        }
    }

    if (toComplete != NULL) {

        bool stopIsStruct = (toComplete->line == curLine);


        QString curText = text(curLine);

        QString endText;
        // if the current line doesn't already have a newline, add one.
        if (curText.length() != 0 && curText[curText.length() - 1] != '\n') {
            endText += "\n";
        }
        if (stopIsStruct) {
            // extra newline if cursor is on a struct
            endText += "\n";
        }
        endText += "end "; // \n is so insertAt() creates a new line
        // if there is an id, use it. Otherwise complete with the type
        endText += toComplete->id != "" ? toComplete->id : toComplete->type;
        endText += "\n";

        int nextLine = curLine + 1;
        insertAt(endText,nextLine,0);

        if(stopIsStruct) {
            // the empty one
            setIndentation(nextLine,toComplete->indent + tabWidth());
            // the ending
            setIndentation(nextLine+1,toComplete->indent);
        } else {
            setIndentation(nextLine,toComplete->indent);
        }
        setCursorPosition(nextLine,(text(nextLine).length()-1));
    } else {
        endUndoAction();
        return "Can't find structure to complete.";
    }

    endUndoAction();

    return "";
}

void TuringEditorWidget::autoIndentAll() {
    QList<TuringEditorWidget::POILine *> pois;
    pois = findPOIs(); // TODO FIXME memory leaked

    // lines that are indented one less than the rest of the body
    QRegExp oneLess("(else|elsif|label).*");
    // next line is indented if one of these is at the end
    QRegExp endContinue(".*(,|or|and)");

    // whole indent should be undone with 1 undo
    beginUndoAction();

    // reset everything. Removes hard tabs
    for(int i = 0; i < lines();++i) {
        setIndentation(i,0);
    }

    int lastLine = 0;
    int curLevel = 0;
    bool nextInd = false; // indent next line
    foreach(TuringEditorWidget::POILine *poi, pois) {
        // all the lines before the first POI should have 0 indent
        for(int i = lastLine + 1; i <= poi->line;++i) {
            int indent = curLevel * tabWidth();
            QString line = text(i).trimmed();

            if(nextInd) {
                indent += tabWidth();
                nextInd = false;
            }

            if(oneLess.exactMatch(line)) {
                indent -= tabWidth();
            }

            if(endContinue.exactMatch(line)) {
                nextInd = true;
            }

            setIndentation(i,indent);
        }


        if(poi->type == "end") {
            setIndentation(poi->line,(curLevel-1) * tabWidth());
            curLevel--;
        } else {
            curLevel++;
        }
        lastLine = poi->line;
    }

    endUndoAction();
}
