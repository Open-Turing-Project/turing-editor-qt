#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <QTabWidget>
#include <QList>

#include "signalmultiplexer.h"
#include "turingeditorwidget.h"

class DocumentManager : public QTabWidget
{
    Q_OBJECT
public:
    explicit DocumentManager(QWidget *parent = 0);

    SignalMultiplexer *multiplex;

    TuringEditorWidget *currentDoc();

    static const QString TempName;

signals:

public slots:
    TuringEditorWidget *openFile(QString fileName);
    TuringEditorWidget *newFile();
    void readSettings();
    bool promptCloseAll();
    void clearAllErrors();

    void handleErrorFile(int line,QString errMsg, QString file, int from, int to);



private slots:
    void closeTab(int index);
    void currentTabChanged(int index);
    void updateName(TuringEditorWidget *doc);
    void documentChanged(bool state);

private:
    bool saveFile(TuringEditorWidget *doc, const QString &fileName);
    QString strippedName(const QString &fullFileName);
    QString getTabText(TuringEditorWidget *doc);

    QList<TuringEditorWidget *> documents;

    // prefs
    bool confirmSave;

};

#endif // DOCUMENTMANAGER_H
