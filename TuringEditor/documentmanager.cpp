#include "documentmanager.h"

#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QMessageBox>
#include <QFileInfo>

const QString DocumentManager::TempName = "UnsavedProgram.t";

DocumentManager::DocumentManager(QWidget *parent) :
    QTabWidget(parent)
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
void DocumentManager::clearAllErrors() {
    foreach(TuringEditorWidget *doc, documents){
        doc->clearErrors();
        updateName(doc);
    }
}

//! add an error annotation to a file at a certain line
//! `file` must be a full path
void DocumentManager::handleErrorFile(int line,QString errMsg, QString file, int from, int to) {

    TuringEditorWidget *doc;
    if(QFileInfo(file).fileName() == DocumentManager::TempName) {
        doc = currentDoc();
    } else {
        // should return an existing file if it is already open
        doc = openFile(file);
    }

    if(to != -1) {
        doc->showError(line-1,errMsg,from-1,to);
    } else {
        doc->showError(line-1,errMsg);
    }

    setCurrentWidget(doc);
    updateName(doc);
}

TuringEditorWidget *DocumentManager::openFile(QString fileName) {
    TuringEditorWidget *doc;

    //QMessageBox::warning(this, tr("Open Turing Editor"),tr("Opening File %1.").arg(fileName));

    // is it already open?
    foreach(TuringEditorWidget *d,documents) {
        if(d->fileName == fileName) {
            return d;
        }
    }

    // use the current document if it is untitled and empty
    if(currentDoc()->fileName.isEmpty() && currentDoc()->text().isEmpty()) {
        doc = currentDoc();
    } else {
        doc = newFile();
    }

    doc->fileName = fileName;

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

    //doc->showError(8,"error: This is the error text.");

    return doc;
}

//! creates a new untitled document
TuringEditorWidget *DocumentManager::newFile() {
    TuringEditorWidget *doc = new TuringEditorWidget(this);
    doc->fileName = ""; // empty == untitled

    addTab(doc,getTabText(doc));

    documents.append(doc);

    setCurrentWidget(doc);

    return doc;
}

void DocumentManager::currentTabChanged(int index) {
    QWidget *wid = widget(index);
    TuringEditorWidget *doc = static_cast<TuringEditorWidget*>(wid);

    multiplex->setCurrentObject(doc);
    doc->emitStatus();
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

    if(doc->fileName.isEmpty()) {
        tabText += tr("Untitled.t");
    } else {
        tabText += strippedName(doc->fileName);
    }
    if(doc->isModified())
        tabText += "*";

    if(doc->hasMessage)
        tabText += " !";

    return tabText;
}

QString DocumentManager::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
