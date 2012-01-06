#ifndef TURINGEDITORWIDGET_H
#define TURINGEDITORWIDGET_H

#include <Qsci/qsciscintilla.h>

#include <QStack>
#include <QPair>

class TuringLexer;
class QsciStyle;

class TuringEditorWidget : public QsciScintilla
{
    Q_OBJECT
public:
    explicit TuringEditorWidget(QWidget *parent = 0);
    TuringLexer *lex;

    QStack<QPair<int,QString> > makeStack(int stopLine = 0);
signals:

public slots:
    void findAll(QString findText);
    void find(QString findText, bool CaseSensitive,bool regex,bool wholeWord);
    void findNextOccurence();
    void replace(QString repText);
    void replaceAll(QString findText,QString repText,bool regex,bool greedyRegex);

    void lightTheme();
    void darkTheme();

    void showError(int line,QString errMsg,int from = -1, int to = -1);
    void clearErrors();
    void clearEverything();

    void readSettings();

    QString completeStruct();

private:

    QsciStyle *darkErrMsgStyle;
    QsciStyle *lightErrMsgStyle;

};

#endif // TURINGEDITORWIDGET_H
