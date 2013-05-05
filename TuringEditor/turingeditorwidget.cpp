#include "turingeditorwidget.h"

#include <QtDebug>
#include <QPalette>
#include <QRegExp>
#include <QSettings>
#include <QFile>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItem>

// for min
#include <algorithm>

#include <Qsci/qscistyle.h>

#include "mainwindow.h"
#include "Qsci/qscilexer.h"
#include "turinglexer.h"
#include "messagemanager.h"


//! override various editor defaults
TuringEditorWidget::TuringEditorWidget(QWidget *parent, MessageManager *messMan, int fNum) :
    QsciScintilla(parent), messageManager(messMan), fileNumber(fNum)
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


    // multi-cursor support
    SendScintilla(QsciScintillaBase::SCI_SETMULTIPLESELECTION,true);
    SendScintilla(QsciScintillaBase::SCI_SETMULTIPASTE,1);
    SendScintilla(QsciScintillaBase::SCI_SETADDITIONALSELECTIONTYPING,true);

    markerDefine(QPixmap(":/images/exclamation.png"),1);
    setMarginWidth(1,18); // 2px larger than the 16px markers to give some room
    setAnnotationDisplay(QsciScintilla::AnnotationBoxed);
    indicatorDefine(QsciScintilla::SquiggleIndicator,2);
    indicatorDefine(QsciScintilla::BoxIndicator,3);
    setIndicatorForegroundColor(QColor(50,250,50),3);

    // Dark error message style
    SendScintilla(QsciScintillaBase::SCI_STYLESETFORE,100,QColor(255,220,220));
    SendScintilla(QsciScintillaBase::SCI_STYLESETBACK,100,QColor(184,50,50));
    // Light error message style
    SendScintilla(QsciScintillaBase::SCI_STYLESETFONT,101,"Times New Roman");
    SendScintilla(QsciScintillaBase::SCI_STYLESETFORE,101,QColor(189,0,15));
    SendScintilla(QsciScintillaBase::SCI_STYLESETBACK,101,QColor(255,240,240));


    connect(this,SIGNAL(textChanged()),this,SLOT(textEdited()));
    connect(this,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(cursorMoved(int,int)));
    connect(this,SIGNAL(modificationChanged(bool)),this,SLOT(modificationStatusChanged(bool)));

    connect(messageManager,SIGNAL(fileMessagesChanged(QString)),this,SLOT(messagesChanged(QString)));
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

    bool wrapLongLines = settings.value("wrapLongLines",true).toBool();
    if(wrapLongLines) {
        setWrapMode(QsciScintilla::WrapWord);
        SendScintilla(QsciScintillaBase::SCI_SETWRAPVISUALFLAGS,QsciScintillaBase::SC_WRAPVISUALFLAG_START);
        setWrapIndentMode(QsciScintilla::WrapIndentIndented);
    } else {
        setWrapMode(QsciScintilla::WrapNone);
    }

    setTabWidth(settings.value("indentSize", 4).toInt());
    setAutoCompletionThreshold(settings.value("autoCompleteThreshold", 5).toInt());

    bool autoComp = settings.value("autoCompleteEnabled",true).toBool();
    setAutoCompletionSource(autoComp ? QsciScintilla::AcsAll : QsciScintilla::AcsNone);
}

void TuringEditorWidget::replaceSlot(QString repText) {
    replace(repText);
}
void TuringEditorWidget::textEdited() {
    int line,col;
    getCursorPosition(&line,&col);
    //if(errorLines.contains(line)) {
        clearErrorsLine(line);
        //messageManager->removeMessage(messageFileName(),line+1);
    //}
}
void TuringEditorWidget::cursorMoved(int line, int col)  {
    QString word = findWordAtPoint(line,col);
    if(!word.isEmpty()) {
        //qDebug() << LWord Selected:  << word;
        emit wordSelected(word);
    }
}

QString TuringEditorWidget::findWordAtPoint(int line, int col) {
    QString lineTxt = text(line);

    // Find the keyword that the cursor is currently on.
    QRegExp rx("([_A-Za-z][_\\.A-Za-z0-9]*)");
    int pos = 0;
    while ((pos = rx.indexIn(lineTxt, pos)) != -1) {
        int endPos = pos + rx.matchedLength();
        if(pos > col) {
            return ""; // We have already passed it, so stop trying to find it.
        }
        // if we are not past it see if it is within the current range
        if(col <= endPos) {
            // Found it. Return the full word.
            return rx.cap(1);
        } else
        pos = endPos;
    }
    return "";
}

void TuringEditorWidget::modificationStatusChanged(bool state) {
    emit statusChanged();
}

void TuringEditorWidget::messagesChanged(QString file) {
    if(file == messageFileName())
        updateMessages();
}

void TuringEditorWidget::emitStatus() {
    int line,col;
    getCursorPosition(&line,&col);
    QString word = findWordAtPoint(line,col);
    if(!word.isEmpty()) {
        emit wordSelected(word);
    }
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
    qDebug() << L"Switching to dark theme";
    lex->setTheme("Dark");
    setCaretForegroundColor(QColor(167,167,167));
    setSelectionBackgroundColor(QColor(221,240,255,45));
    clearErrors();
}
//! Switch to the dark coding theme. Based on the theme used
//! in the original Turing editor.
void TuringEditorWidget::lightTheme() {
    qDebug() << L"Switching to light theme";
    lex->setTheme("Default");
    setCaretForegroundColor(QColor(0,0,0));
    setSelectionForegroundColor(palette().color(QPalette::HighlightedText));
    setSelectionBackgroundColor(palette().color(QPalette::Highlight));
    clearErrors();
}

QString TuringEditorWidget::messageFileName() {
    if(isUnnamed()) {
        return getTempFileName();
    } else {
        return fileName;
    }
}

void TuringEditorWidget::updateMessages() {
    clearErrors();

    QStandardItem *file = messageManager->getFileItem(messageFileName());
    if(file == NULL) return;

    QStandardItem *message;
    for(int i = 0, e = file->rowCount(); i < e;++i) {
        message = file->child(i);
        int line = message->data(MessageManager::LineNumberRole).toInt();
        int from = message->data(MessageManager::FromColRole).toInt();
        int to = message->data(MessageManager::ToColRole).toInt();
        showError(line,message->text(),from,to);
    }
}

//! Uses a scintilla annotation to display an error box below a certain line.
//! if from and to are provided a squiggly underline is used.
//! From and to are character indexes into the line.
//! If to is greater than the line length it will wrap.
void TuringEditorWidget::showError(int messageLine,QString errMsg,int from, int to)
{
    int line = messageLine - 1; // scintilla uses 0-based lines
    markerAdd(line,1);
    int errStyle = lex->getTheme() == "Dark" ? 100 : 101;
    annotate(line,"^ " + errMsg,errStyle);

    if(from >= 0 && to >= 0) {
        fillIndicatorRange(line,from,line,to,2);
    }

    errorLines.insert(line);

    ensureLineVisible(line); // scroll to it
}
//! removes all error annotations from display.
void TuringEditorWidget::clearErrors() {
    clearAnnotations();
    clearIndicatorRange(0,0,lines(),lineLength(lines()),2);
    markerDeleteAll(1);

    errorLines.clear();
    emit statusChanged();
}
//! removes errors from a specific line
void TuringEditorWidget::clearErrorsLine(int line) {
    clearAnnotations(line);
    clearIndicatorRange(line,0,line,lineLength(line),2);
    markerDelete(line,1);
    errorLines.remove(line);
    if(errorLines.empty()) {
        emit statusChanged();
    }
}

//! clears all annotations, markers and indicators
void TuringEditorWidget::clearEverything() {
    clearAnnotations();
    clearIndicatorRange(0,0,lines(),text(lines()).length(),-1);
    markerDeleteAll(-1);

    messageManager->clearMessagesFile(messageFileName());
    errorLines.clear();
    emit statusChanged();
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

    emit statusChanged();

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

//! Find all the structures and endings in the file. Used for structure completion and auto-indent.
// TODO rewrite this to use a lexer-based design that can handle multi-line comments and multiple
// POIs on one line properly
QList<TuringEditorWidget::POILine*> TuringEditorWidget::findPOIs(int lastLine) {
    // stack for structs. string is identifier
    QList<TuringEditorWidget::POILine*> pois;

    QRegExp endRegex("^[\\t ]*end[\\t ]+([_a-zA-Z0-9]+).*");
    QRegExp funcRegex("^[\\t ]*(body +|pervasive +)*(proc|procedure|fcn|function|class|module|process|monitor)[\\t\\* ]+([_a-zA-Z0-9]+).*");
    QRegExp structRegex("[\\t ]*(if|for|loop|case|record|union|handler)( .*)?\\s*");

    // if lastLine is the default value set it to the last line in the file
    if(lastLine < 0)
        lastLine = lines()-1; // -1 to account for zero-indexing

    bool commentMode = false; // are we in a multi-line comment
    for(int i = 0; i <= lastLine;++i) {
        QString line = text(i);

        // TODO hacky fix to the problem of multi-line comments
        // does not deal with situations like "if bob then /*"
        // luckily these rarely happen in practice
        if(!commentMode && line.contains("/*")) {
            commentMode = true;
            continue;
        } else if(commentMode) { // skip lines in comment mode
            if(line.contains("*/"))
                commentMode = false;
            continue;
        }

        TuringEditorWidget::POILine *curLine = new TuringEditorWidget::POILine();
        curLine->indent = indentation(i);
        curLine->line = i;
        if(endRegex.exactMatch(line)) {
            QStringList captures = endRegex.capturedTexts();

            curLine->type = "end";
            curLine->id = captures[1];


            // find the beginning struct.
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
        } else {
            delete curLine; // not needed
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
    pois = findPOIs(curLine); // stop at the current line

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

    // clean up.
    foreach(TuringEditorWidget::POILine *poi, pois) {
        delete poi;
    }

    return "";
}

void TuringEditorWidget::autoIndentAll() {
    QList<TuringEditorWidget::POILine *> pois;
    pois = findPOIs();

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

    // clean up.
    foreach(TuringEditorWidget::POILine *poi, pois) {
        delete poi;
    }
}
