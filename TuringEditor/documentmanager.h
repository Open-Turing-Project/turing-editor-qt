#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <QTabWidget>
#include <QList>
#include <QModelIndex>

#include "signalmultiplexer.h"
#include "turingeditorwidget.h"

class MessageManager;

class DocumentManager : public QTabWidget
{
    Q_OBJECT
public:
    explicit DocumentManager(QWidget *parent, MessageManager *manager);

    SignalMultiplexer *multiplex;

    TuringEditorWidget *currentDoc();

    virtual QSize sizeHint() const;

signals:

public slots:
    TuringEditorWidget *openFile(QString fileName);
    TuringEditorWidget *newFile();
    void readSettings();
    bool promptCloseAll();

    void closeTab (int index);

    //! Takes a model index into the message model and selects or opens the file
    //! and scrolls to the message. If the index points to a file item the file is selected.
    void showMessage(const QModelIndex & index);

private slots:
    void currentTabChanged(int index);
    void updateName(TuringEditorWidget *doc);
    void documentChanged();

private:
    bool saveFile(TuringEditorWidget *doc, const QString &fileName);
    QString strippedName(const QString &fullFileName);
    QString getTabText(TuringEditorWidget *doc);
    TuringEditorWidget *findByNumber(int num);

    QList<TuringEditorWidget *> documents;

    MessageManager *messMan;

    // prefs
    bool confirmSave;

    //! next file number to give out
    int nextFileNumber;

};

#endif // DOCUMENTMANAGER_H
