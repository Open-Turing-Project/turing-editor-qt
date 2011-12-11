#include "turingeditorwidget.h"

#include <QtDebug>
#include <QPalette>

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

    setFolding(QsciScintilla::PlainFoldStyle);
    setAutoIndent(true);
    setTabWidth(4);

    setCallTipsStyle(QsciScintilla::CallTipsNoContext);
    setAutoCompletionCaseSensitivity(false);
    setAutoCompletionSource(QsciScintilla::AcsAll);
    setAutoCompletionThreshold(5);

    markerDefine(QsciScintilla::RightArrow,1);
    setAnnotationDisplay(QsciScintilla::AnnotationBoxed);
    indicatorDefine(QsciScintilla::SquiggleIndicator,2);
    indicatorDefine(QsciScintilla::BoxIndicator,3);
    setIndicatorForegroundColor(QColor(50,250,50),3);

    darkErrMsgStyle = new QsciStyle(-1,"dark error style",QColor(255,220,220),QColor(184,50,50),QFont());
    lightErrMsgStyle = new QsciStyle(-1,"light error style",Qt::black,QColor(230,150,150),QFont());
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
