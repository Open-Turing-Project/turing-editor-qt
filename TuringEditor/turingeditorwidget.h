#ifndef TURINGEDITORWIDGET_H
#define TURINGEDITORWIDGET_H

#include <Qsci/qsciscintilla.h>

#include <QStack>
#include <QPair>
#include <QSet>

class TuringLexer;
class QsciStyle;

class TuringEditorWidget : public QsciScintilla
{
    Q_OBJECT
public:
    explicit TuringEditorWidget(QWidget *parent = 0);
    TuringLexer *lex;

    QStack<QPair<int,QString> > makeStack(int stopLine = -1, bool *stopIsStruct = 0);

    QString fileName;

    //! Is there a message currently visible?
    bool hasMessage;

    //! POI is GPS parlance for Point Of Interest
    struct POILine {
        POILine() : type(""),id(""),other(NULL),indent(0) {}

        //! structure type. I.E if, proc, end
        QString type;
        //! identifier. empty if same as type. I.E DoStuff, ScreenLoad
        QString id;
        //! if it is a beginning. Other is a pointer to the ending.
        //! or vice-versa. Null if none.
        POILine *other;
        //! indent level
        int indent;
        int line;
    };

    QList<POILine*> findPOIs(int lastLine = -1);
    QString findWordAtPoint(int line, int col);

signals:
    //! emitted whenever important status like modification state or error messages changes.
    //! Used to update the tab name.
    void statusChanged();
    //! Emitted when the cursor is over a keyword or identifier like "loop" or "Draw.Box"
    //! Can be used to display docs for the selected function.
    void wordSelected(QString word);
public slots:
    void findAll(QString findText);
    void find(QString findText, bool CaseSensitive,bool regex,bool wholeWord);
    void findNextOccurence();
    void replaceSlot(QString repText);
    void replaceAll(QString findText,QString repText,bool regex,bool greedyRegex);

    bool maybeSave();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName, bool temporary = false);

    void lightTheme();
    void darkTheme();

    void showError(int line,QString errMsg,int from = -1, int to = -1);
    void clearErrors();
    void clearErrorsLine(int line);
    void clearEverything();

    void readSettings();

    //! Re-emits all the status signals such as selected word.
    void emitStatus();

    QString completeStruct();
    void autoIndentAll();
private slots:
    void textEdited();
    void cursorMoved(int line, int col);
    void modificationStatusChanged(bool state);

private:

    bool confirmSave;

    QsciStyle *darkErrMsgStyle;
    QsciStyle *lightErrMsgStyle;

    QSet<int> errorLines;

};

#endif // TURINGEDITORWIDGET_H
