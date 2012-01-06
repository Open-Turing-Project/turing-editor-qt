#include "turingeditorwidget.h"

#include <QtDebug>
#include <QPalette>
#include <QRegExp>
#include <QSettings>

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

    setCallTipsStyle(QsciScintilla::CallTipsNoContext);
    setAutoCompletionCaseSensitivity(false);
    setAutoCompletionUseSingle(QsciScintilla::AcusExplicit);

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

void TuringEditorWidget::replace(QString repText) {
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
}
//! removes all error annotations from display.
void TuringEditorWidget::clearErrors() {
    clearAnnotations();
    clearIndicatorRange(0,0,lines(),text(lines()).length(),2);
    markerDeleteAll(1);
}

//! clears all annotations, markers and indicators
void TuringEditorWidget::clearEverything() {
    clearAnnotations();
    clearIndicatorRange(0,0,lines(),text(lines()).length(),-1);
    markerDeleteAll(-1);
}

/*!
Returns a structure stack of pairs.
The first element in each pair is the indentation level.
Second is the structure identifier.
Each stack element represents an unclosed structure.

stopLine is the line to stop parsing at.

when stopLine is 0 it will parse the entire document.

when stopLine is 0 it should return an empty stack if all
the structures in the document are closed.
*/
QStack<QPair<int,QString> > TuringEditorWidget::makeStack(int stopLine) {
    // stack for structs. string is identifier
    QStack<QPair<int,QString> > structStack;

    QRegExp endRegex("[\\t ]*end[\\t ]+([_a-zA-Z0-9]+).*");
    QRegExp funcRegex("[\\t ]*(body +|pervasive +)*(proc|procedure|fcn|function|class|module)[\\t\\* ]+([_a-zA-Z0-9]+).*");
    QRegExp structRegex("[\\t ]*(if|for|loop|case|record).*");

    // Stops either at the stop line or the end of the document
    int lastLine;
    if(stopLine > 0) {
        lastLine = std::min(lines(),stopLine);
    } else {
        lastLine = lines();
    }
    for(int i = 0; i < lastLine;++i) {
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
        } else if(funcRegex.exactMatch(line)) {
            QPair<int,QString> decl;
            QStringList captures = funcRegex.capturedTexts();
            decl.first = indentation(i);
            decl.second = captures[3];
            structStack.push(decl);
        } else if(structRegex.exactMatch(line)) {
            QPair<int,QString> decl;
            QStringList captures = structRegex.capturedTexts();
            decl.first = indentation(i);
            decl.second = captures[1];
            structStack.push(decl);
        }
    }

    return structStack;
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

    int nextLine,dummyCursorPos;
    getCursorPosition(&nextLine,&dummyCursorPos);
    nextLine++; // this makes it the line after the cursor

    QStack<QPair<int,QString> > structStack;
    structStack = makeStack(nextLine);

    if (!structStack.isEmpty()) {
        QPair<int,QString> toComplete = structStack.pop();

        QString curText = text(nextLine - 1); // nextLine - 1 == current line

        QString endText;
        if (curText.length() != 0 && curText[curText.length() - 1] != '\n') {
            endText += "\n";
        }
        endText += "end "; // \n is so insertAt() creates a new line
        endText += toComplete.second;
        endText += "\n";
        insertAt(endText,nextLine,0);
        setIndentation(nextLine,toComplete.first);
        setCursorPosition(nextLine,(text(nextLine).length()-1));
    } else {
        return "All structures are complete.";
    }

    return "";
}
