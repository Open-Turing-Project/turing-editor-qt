/****************************************************************************
**
** Copyright (C) 2004-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** Licensees holding a valid Qt License Agreement may use this file in
** accordance with the rights, responsibilities and obligations
** contained therein.  Please consult your licensing agreement or
** contact sales@trolltech.com if any conditions of this licensing
** agreement are not clear to you.
**
** Further information about Qt licensing is available at:
** http://www.trolltech.com/products/qt/licensing.html or by
** contacting info@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QtGui>
#include <QtDebug>
#include <QPalette>
#include <QCoreApplication>
#include <QStringList>
#include <QLabel>

#include <Qsci/qscistyle.h>

#include "mainwindow.h"

#include "turingeditorwidget.h"
#include "Qsci/qscilexer.h"
#include "turinglexer.h"
#include "findreplacedialog.h"
#include "aboutbox.h"
#include "settingsdialog.h"

#include "turingrunner.h"

MainWindow::MainWindow()
{
    setWindowIcon(QIcon(":/images/pixel_icon.png"));

    docMan = new DocumentManager(this);

    // BUG find next after switching tabs
    findDialog = new FindReplaceDialog();
    docMan->multiplex->connect(findDialog,SIGNAL(findAll(QString)),SLOT(findAll(QString)));
    docMan->multiplex->connect(findDialog,SIGNAL(findAll(QString)),SLOT(findAll(QString)));
    docMan->multiplex->connect(findDialog,SIGNAL(find(QString,bool,bool,bool)),SLOT(find(QString,bool,bool,bool)));
    docMan->multiplex->connect(findDialog,SIGNAL(findNext()),SLOT(findNextOccurence()));
    docMan->multiplex->connect(findDialog,SIGNAL(replace(QString)),SLOT(replace(QString)));
    docMan->multiplex->connect(findDialog,SIGNAL(replaceAll(QString,QString,bool,bool)),
                               SLOT(replaceAll(QString,QString,bool,bool)));

    lineLabel = new QLabel(this);
    docMan->multiplex->connect(SIGNAL(cursorPositionChanged(int,int)),this,SLOT(cursorMoved(int,int)));
    lineLabel->setFixedWidth(170);
    statusBar()->addPermanentWidget(lineLabel);

    setCentralWidget(docMan);

    createActions();
    createMenus();

    createToolBars();
    createStatusBar();

    updateRecentFileActions();

    setWindowTitle(tr("Open Turing Editor"));

    currentRunner = NULL;
    runDoc = NULL;

    readSettings();

    docMan->currentDoc()->setFocus();
}

QSize MainWindow::sizeHint() const {
    return QSize(660,540);
}

void MainWindow::cursorMoved(int line, int index) {
    QString lineText("Line ");
    lineText += QString::number(line);
    lineText += " of ";
    lineText += QString::number(docMan->currentDoc()->lines());
    lineText +=  " col ";
    lineText += QString::number(index);
    lineText += " "; // for spacing

    lineLabel->setText(lineText);
}

void MainWindow::runProgram() {

    runDoc = docMan->currentDoc();
    QString runFile = runDoc->fileName;

    if (saveOnRun && !(runDoc->fileName.isEmpty())) // if saveonrun and not untitled
        runDoc->save();

    if(currentRunner != NULL) {
        if(currentRunner->isCompiled()) {
            currentRunner->stopRun();
        } else {
            statusBar()->showMessage(tr("Already compiling a program."));
            return;
        }
    }
    if(runDoc->fileName.isEmpty()) { // if untitled, use a temp file
        QString tmpFile = QDir::temp().absoluteFilePath(DocumentManager::TempName);
        runDoc->saveFile(tmpFile,true); // true = temp file
        runFile = tmpFile;
    }

    statusBar()->showMessage(tr("Compiling..."));

    QCoreApplication::processEvents();

    docMan->clearAllErrors();

    // LEAK TODO old runner is left hanging in QObject tree
    currentRunner = new TuringRunner(this,runFile);
    connect(currentRunner,SIGNAL(errorFile(int,QString,QString,int,int)),docMan,
            SLOT(handleErrorFile(int,QString,QString,int,int)));
    connect(currentRunner,SIGNAL(errorGeneral(QString)),this,SLOT(handleError(QString)));
    connect(currentRunner,SIGNAL(compileFinished(bool)),this,SLOT(compileComplete(bool)));

    currentRunner->startCompile();
}

void MainWindow::compileComplete(bool success) {
    if (success){
        if (currentRunner != NULL && currentRunner->isCompiled()) {
            statusBar()->showMessage(tr("Compile suceeded. Running..."));
            currentRunner->startRun();
        }
    } else {
        currentRunner = NULL;
        statusBar()->showMessage(tr("Compile failed."));
    }
}

void MainWindow::handleError(QString errMsg) {
    QMessageBox::warning(this, tr("Open Turing Editor"),errMsg);
}

void MainWindow::completeStruct() {
    QString msg = docMan->currentDoc()->completeStruct();
    if (msg != NULL && msg != "") {
        statusBar()->showMessage(msg);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (docMan->promptCloseAll()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QString fileName = action->data().toString();
        addRecentFile(fileName);
        docMan->openFile(fileName);
    }
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Program File"),
                                                    docMan->currentDoc()->fileName,
                                                    tr("Turing Files (*.t *.ti *.tu *.tur)"));
    if (!fileName.isEmpty()){
        addRecentFile(fileName);

        docMan->openFile(fileName);
    }
}

void MainWindow::openFile(const QString &fileName){
    if (!fileName.isEmpty()){
        addRecentFile(fileName);

        docMan->openFile(fileName);
    }
}

void MainWindow::closeTab()
{
    docMan->closeTab(docMan->currentIndex());
}

void MainWindow::addRecentFile(const QString &fileName) {
    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > MaxRecentFiles)
     files.removeLast();

    settings.setValue("recentFileList", files);

    updateRecentFileActions();
}

void MainWindow::updateRecentFileActions()
 {
     QSettings settings;
     QStringList files = settings.value("recentFileList").toStringList();

     int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

     for (int i = 0; i < numRecentFiles; ++i) {
         QString text = tr("&%1 %2").arg(i + 1).arg(QFileInfo(files[i]).fileName());
         recentFileActs[i]->setText(text);
         recentFileActs[i]->setData(files[i]);
         recentFileActs[i]->setVisible(true);
     }
     for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
         recentFileActs[j]->setVisible(false);
}

void MainWindow::populateMarkMenu() {
    // TODO LEAK previous actions not leaked because of QObject tree,
    // but they do sit using up memory
    markMenu->clear();

    QList<TuringEditorWidget::POILine *> marks;
    marks = docMan->currentDoc()->findPOIs();

    int numMarks = 0;
    foreach(TuringEditorWidget::POILine *mark, marks) {
        if(mark->type != "end" && mark->id != "") {
            QAction *act = new QAction(mark->id,this);
            act->setData(mark->line);
            connect(act,SIGNAL(triggered()),this, SLOT(goToMark()));
            markMenu->addAction(act);
        }
    }
}

void MainWindow::goToMark()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        int line = action->data().toInt();
        docMan->currentDoc()->ensureLineVisible(line);
    }
}

void MainWindow::about()
{
    AboutBox aboutBox;
    aboutBox.exec();
}

void MainWindow::showHelp()
{
    QDesktopServices::openUrl(QString("file:///") + QCoreApplication::applicationDirPath () + "/" + HELP_FILE_PATH);
}

void MainWindow::showSettings()
{
    SettingsDialog settings;
    if(settings.exec()) {
        readSettings();
    }
}

void MainWindow::createActions()
{

    settingsAct = new QAction(tr("&Preferences"), this);
    settingsAct->setStatusTip(tr("Change settings/preferences."));
    connect(settingsAct, SIGNAL(triggered()), this, SLOT(showSettings()));

    closeTabAct = new QAction(tr("&Close Tab"), this);
    closeTabAct->setShortcut(tr("Ctrl+W"));
    closeTabAct->setStatusTip(tr("Closes the current file"));
    connect(closeTabAct, SIGNAL(triggered()), this, SLOT(closeTab()));

    helpAct = new QAction(QIcon(":/images/help.png"),tr("Turing &Help"), this);
    helpAct->setShortcut(Qt::Key_F10);
    helpAct->setStatusTip(tr("Open Turing help."));
    connect(helpAct, SIGNAL(triggered()), this, SLOT(showHelp()));

    runAct = new QAction(QIcon(":/images/control_play.png"),tr("&Run"), this);
    runAct->setShortcut(Qt::Key_F1);
    runAct->setStatusTip(tr("Run this Turing program."));
    connect(runAct, SIGNAL(triggered()), this, SLOT(runProgram()));


    structCompleteAct = new QAction(QIcon(":/images/wand.png"),tr("Complete &Structure"), this);
    structCompleteAct->setShortcut(Qt::CTRL + Qt::Key_Return);
    structCompleteAct->setStatusTip(tr("Insert an ending for a structure."));
    connect(structCompleteAct, SIGNAL(triggered()), this, SLOT(completeStruct()));


    findAct = new QAction(QIcon(":/images/magnifier.png"),tr("&Find"), this);
    findAct->setShortcut(tr("Ctrl+F"));
    findAct->setStatusTip(tr("Find text in file."));
    connect(findAct, SIGNAL(triggered()), findDialog, SLOT(activate()));

    newAct = new QAction(QIcon(":/images/page_add.png"), tr("&New"), this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), docMan, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/folder.png"), tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About Open Turing"), this);
    aboutAct->setStatusTip(tr("View version and other informtion about Open Turing."));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    // FOR CURRENT DOCUMENT

    autoCompleteAct = new QAction(tr("Completion &Menu"), this);
    autoCompleteAct->setShortcut(Qt::CTRL + Qt::Key_Space);
    autoCompleteAct->setStatusTip(tr("Insert an ending for a structure."));
    docMan->multiplex->connect(autoCompleteAct, SIGNAL(triggered()), SLOT(autoCompleteFromAll()));

    autoIndentAct = new QAction(tr("Auto-&Indent"), this);
    autoIndentAct->setShortcut(Qt::Key_F2);
    autoIndentAct->setStatusTip(tr("Automatically indent the file."));
    docMan->multiplex->connect(autoIndentAct, SIGNAL(triggered()), SLOT(autoIndentAll()));

    clearAct = new QAction(QIcon(":/images/cross.png"),tr("&Clear Messages"), this);
    clearAct->setShortcut(Qt::Key_Escape);
    clearAct->setStatusTip(tr("Clear all error messages, boxes, lines, etc. in the document."));
    docMan->multiplex->connect(clearAct, SIGNAL(triggered()), SLOT(clearEverything()));

    cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcut(tr("Ctrl+X"));
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    docMan->multiplex->connect(cutAct, SIGNAL(triggered()), SLOT(cut()));

    copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAct->setShortcut(tr("Ctrl+C"));
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    docMan->multiplex->connect(copyAct, SIGNAL(triggered()), SLOT(copy()));

    pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcut(tr("Ctrl+V"));
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    docMan->multiplex->connect(pasteAct, SIGNAL(triggered()), SLOT(paste()));

    saveAct = new QAction(QIcon(":/images/disk.png"), tr("&Save"), this);
    saveAct->setShortcut(tr("Ctrl+S"));
    saveAct->setStatusTip(tr("Save the document to disk"));
    docMan->multiplex->connect(saveAct, SIGNAL(triggered()), SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    docMan->multiplex->connect(saveAsAct, SIGNAL(triggered()), SLOT(saveAs()));

    zoomOutAct = new QAction(tr("Zoom &Out"), this);
    zoomOutAct->setShortcut(Qt::CTRL + Qt::Key_Minus);
    zoomOutAct->setStatusTip(tr("Make text smaller."));
    docMan->multiplex->connect(zoomOutAct, SIGNAL(triggered()), SLOT(zoomOut()));

    zoomInAct = new QAction(tr("Zoom &In"), this);
    zoomInAct->setShortcut(Qt::CTRL + Qt::Key_Plus);
    zoomInAct->setStatusTip(tr("Make text larger."));
    docMan->multiplex->connect(zoomInAct, SIGNAL(triggered()), SLOT(zoomIn()));





    for (int i = 0; i < MaxRecentFiles; ++i) {
     recentFileActs[i] = new QAction(this);
     recentFileActs[i]->setVisible(false);
     connect(recentFileActs[i], SIGNAL(triggered()),
             this, SLOT(openRecentFile()));
    }
}

void MainWindow::createMenus()
{
    QMenu *recentMenu = new QMenu(tr("Open &Recent"),this);
    for (int i = 0; i < MaxRecentFiles; ++i)
             recentMenu->addAction(recentFileActs[i]);

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(recentMenu);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(closeTabAct);
    fileMenu->addAction(runAct);
    fileMenu->addSeparator();

    fileMenu->addAction(settingsAct);
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addAction(findAct);
    editMenu->addAction(structCompleteAct);
    editMenu->addAction(autoIndentAct);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(clearAct);
    viewMenu->addAction(autoCompleteAct);
    viewMenu->addSeparator();
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(zoomInAct);

    markMenu = menuBar()->addMenu(tr("&Mark"));
    markMenu->setTearOffEnabled(true);
    connect(markMenu,SIGNAL(aboutToShow()),this,SLOT(populateMarkMenu()));

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpAct);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars()
{
    mainToolBar = addToolBar(tr("Actions"));
    mainToolBar->setMovable(false);
    mainToolBar->setIconSize(QSize(16,16));
    mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    mainToolBar->addAction(runAct);

    mainToolBar->addAction(newAct);
    mainToolBar->addAction(openAct);
    mainToolBar->addAction(saveAct);

    mainToolBar->addSeparator();

    mainToolBar->addAction(structCompleteAct);
    mainToolBar->addAction(findAct);
    mainToolBar->addAction(clearAct);
    mainToolBar->addAction(helpAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings;

    saveOnRun = settings.value("saveOnRun",true).toBool();

    docMan->readSettings();
}
