#include "documentmanager.h"

#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QMessageBox>
#include <QFileInfo>

#include "messagemanager.h"

const QString DocumentManager::TempName = "UnsavedProgram.t";

DocumentManager::DocumentManager(QWidget *parent, MessageManager *manager) :
    QTabWidget(parent), messMan(manager)
{
    setTabsClosable(true);
    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));

    connect(this,SIGNAL(currentChanged(int)),this,SLOT(currentTabChanged(int)));

    setDocumentMode(true);
    setUsesScrollButtons(true);
    setMovable(true);

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setMinimumSize(300,400);

    multiplex = new SignalMultiplexer(this);

    // start with one tab
    TuringEditorWidget *doc = newFile();
    multiplex->setCurrentObject(doc);

    multiplex->connect(SIGNAL(statusChanged()),this,SLOT(documentChanged()));
}

QSize DocumentManager::sizeHint() const {
    return QSize(700,550);
}

void DocumentManager::readSettings()
{
    // pass it on
    foreach(TuringEditorWidget *doc, documents)
        doc->readSettings();
}

TuringEditorWidget *DocumentManager::openFile(QString fileName) {
    TuringEditorWidget *doc;

    //QMessageBox::warning(this, tr("Open Turing Editor"),tr("Opening File %1.").arg(fileName));

    // is it already open?
    foreach(TuringEditorWidget *d,documents) {
        if(d->getFileName() == fileName) {
            return d;
        }
    }

    // use the current document if it is untitled and empty
    if(currentDoc()->isUnnamed() && currentDoc()->text().isEmpty()) {
        doc = currentDoc();
    } else {
        doc = newFile();
    }

    doc->setFileName(fileName);;

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("Open Turing Editor"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return doc;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    doc->setText(in.readAll());
    QApplication::restoreOverrideCursor();
    doc->setModified(false);

    updateName(doc);

    setCurrentWidget(doc);

    //messMan->handleMessageFile(5,"This is a test error",fileName,4,7);

    return doc;
}

//! creates a new untitled document
TuringEditorWidget *DocumentManager::newFile() {
    TuringEditorWidget *doc = new TuringEditorWidget(this,messMan);
    doc->setFileName(""); // empty == untitled

    addTab(doc,getTabText(doc));

    documents.append(doc);

    setCurrentWidget(doc);

    return doc;
}

void DocumentManager::currentTabChanged(int index) {
    QWidget *wid = widget(index);
    if(wid != NULL) {
        TuringEditorWidget *doc = static_cast<TuringEditorWidget*>(wid);

        multiplex->setCurrentObject(doc);
        doc->emitStatus();
    }
}

void DocumentManager::closeTab(int index) {
    QWidget *closed = widget(index);
    TuringEditorWidget *doc = static_cast<TuringEditorWidget*>(closed);

    if(doc->maybeSave()) {
        documents.removeOne(doc);
        removeTab(index);

        // we can't have no tabs!
        if(count() == 0) {
            newFile();
        }

        // it may have changed
        multiplex->setCurrentObject(currentDoc());
    }
}

//! returns the text editor for the currently selected tab
TuringEditorWidget *DocumentManager::currentDoc() {
    // the widget is always a text editor
    return static_cast<TuringEditorWidget*>(currentWidget());
}

bool DocumentManager::promptCloseAll() {
    foreach(TuringEditorWidget *doc,documents) {
        bool res = doc->maybeSave();
        if(!res) return false;
    }
    return true;
}

void DocumentManager::documentChanged() {
    updateName(currentDoc());
}

//! updates the tab name for a document
void DocumentManager::updateName(TuringEditorWidget *doc) {
    setTabText(indexOf(doc),getTabText(doc));
}

QString DocumentManager::getTabText(TuringEditorWidget *doc) {
    QString tabText;

    if(doc->isUnnamed()) {
        tabText += tr("Untitled.t");
    } else {
        tabText += strippedName(doc->getFileName());
    }
    if(doc->isModified())
        tabText += "*";

    if(doc->hasMessage())
        tabText += " !";

    return tabText;
}

void DocumentManager::showMessage(const QModelIndex &index) {
    QStandardItem *item = messMan->itemFromIndex(index);
    QStandardItem *parent = item->parent();

    // if the parent is null it is a file item, if not, it is a message
    bool isMessage = (parent != NULL);
    QVariant filePath = (isMessage ? parent : item)->data(MessageManager::FilePathRole);
    TuringEditorWidget *doc = openFile(filePath.toString());
    setCurrentWidget(doc);

    if(isMessage)
        doc->ensureLineVisible(item->data(MessageManager::LineNumberRole).toInt());
}

QString DocumentManager::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
