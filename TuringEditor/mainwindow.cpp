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

#include <Qsci/qscistyle.h>

#include "mainwindow.h"

#include "turingeditorwidget.h"
#include "Qsci/qscilexer.h"
#include "turinglexer.h"
#include "findreplacedialog.h"
#include "aboutbox.h"

#include "turingrunner.h"

MainWindow::MainWindow()
{
    setWindowIcon(QIcon(":/images/pixel_icon.png"));

    textEdit = new TuringEditorWidget(this);

    findDialog = new FindReplaceDialog();
    connect(findDialog,SIGNAL(findAll(QString)),textEdit,SLOT(findAll(QString)));
    connect(findDialog,SIGNAL(find(QString,bool,bool,bool)),textEdit,SLOT(find(QString,bool,bool,bool)));
    connect(findDialog,SIGNAL(findNext()),textEdit,SLOT(findNextOccurence()));
    connect(findDialog,SIGNAL(replace(QString)),textEdit,SLOT(replace(QString)));
    connect(findDialog,SIGNAL(replaceAll(QString,QString,bool,bool)),textEdit,SLOT(replaceAll(QString,QString,bool,bool)));

    setCentralWidget(textEdit);

    createActions();
    createMenus();

    createToolBars();
    createStatusBar();

    readSettings();

    connect(textEdit, SIGNAL(textChanged()),
            this, SLOT(documentWasModified()));

    setCurrentFile("");

    currentRunner = NULL;
}

QSize MainWindow::sizeHint() const {
    return QSize(660,630);
}

void MainWindow::runProgram() {
    if(currentRunner != NULL) {
        statusBar()->showMessage(tr("Already running a program."));
        return;
    }
    if(curFile.isEmpty()) {
        statusBar()->showMessage(tr("Can't run unsaved files."));
        return;
    }

    statusBar()->showMessage(tr("Compiling..."));

    QCoreApplication::processEvents();

    currentRunner = new TuringRunner(this,curFile);
    connect(currentRunner,SIGNAL(errorFile(int,QString,QString,int,int)),this,
            SLOT(handleErrorFile(int,QString,QString,int,int)));
    connect(currentRunner,SIGNAL(errorGeneral(QString)),this,SLOT(handleError(QString)));
    connect(currentRunner,SIGNAL(compileFinished(bool)),this,SLOT(compileComplete(bool)));

    currentRunner->startCompile();
}

void MainWindow::compileComplete(bool success) {
    if (success){
        if (currentRunner != NULL) {
            statusBar()->showMessage(tr("Compile suceeded. Running..."));
            currentRunner->startRun();
        }
    } else {
        statusBar()->showMessage(tr("Compile failed."));
    }
    // TODO better memory mangement. not leaked because of QObject tree. Bad though.
    currentRunner = NULL;
}

void MainWindow::handleErrorFile(int line,QString errMsg, QString file, int from, int to) {
    if(to != -1) {
        textEdit->showError(line-1,errMsg,from-1,to);
    } else {
        textEdit->showError(line-1,errMsg);
    }
}
void MainWindow::handleError(QString errMsg) {
    QMessageBox::warning(this, tr("Open Turing Editor"),errMsg);
}

void MainWindow::completeStruct() {
    QString msg = textEdit->completeStruct();
    if (msg != NULL && msg != "") {
        statusBar()->showMessage(msg);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFile("");
    }
}



void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Program File"),curFile,
                                                    tr("Turing Files (*.t *.ti *.tu)"));
    if (!fileName.isEmpty()){
        // is the current file untitled.t and empty?
        if (curFile.isEmpty() && textEdit->text().isEmpty()) {
            loadFile(fileName);
        } else {
            MainWindow *newWin = new MainWindow();
            newWin->loadFile(fileName);
            newWin->move(newWin->x() + 5, newWin->y() + 10);
            newWin->show();
        }
    }
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save Program","",
                                                    tr("Turing Files (*.t *.ti *.tu)"));
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void MainWindow::about()
{
    AboutBox aboutBox;
    aboutBox.exec();
}

void MainWindow::documentWasModified()
{
    setWindowModified(textEdit->isModified());
}

void MainWindow::createActions()
{

    runAct = new QAction(QIcon(":/images/control_play.png"),tr("&Run"), this);
    runAct->setShortcut(Qt::Key_F1);
    runAct->setStatusTip(tr("Run this Turing program."));
    connect(runAct, SIGNAL(triggered()), this, SLOT(runProgram()));


    structCompleteAct = new QAction(QIcon(":/images/wand.png"),tr("Complete &Structure"), this);
    structCompleteAct->setShortcut(Qt::CTRL + Qt::Key_Return);
    structCompleteAct->setStatusTip(tr("Insert an ending for a structure."));
    connect(structCompleteAct, SIGNAL(triggered()), this, SLOT(completeStruct()));

    autoCompleteAct = new QAction(tr("Completion &Menu"), this);
    autoCompleteAct->setShortcut(Qt::CTRL + Qt::Key_Space);
    autoCompleteAct->setStatusTip(tr("Insert an ending for a structure."));
    connect(autoCompleteAct, SIGNAL(triggered()), textEdit, SLOT(autoCompleteFromAll()));

    lightThemeAct = new QAction(tr("&Light theme"), this);
    lightThemeAct->setStatusTip(tr("Change to a light theme."));
    connect(lightThemeAct, SIGNAL(triggered()), textEdit, SLOT(lightTheme()));

    darkThemeAct = new QAction(tr("&Dark theme"), this);
    darkThemeAct->setStatusTip(tr("Change to a dark theme."));
    connect(darkThemeAct, SIGNAL(triggered()), textEdit, SLOT(darkTheme()));

    findAct = new QAction(QIcon(":/images/magnifier.png"),tr("&Find"), this);
    findAct->setShortcut(tr("Ctrl+F"));
    findAct->setStatusTip(tr("Find text in file."));
    connect(findAct, SIGNAL(triggered()), findDialog, SLOT(activate()));

    clearAct = new QAction(QIcon(":/images/cross.png"),tr("&Clear Messages"), this);
    clearAct->setShortcut(Qt::Key_Escape);
    clearAct->setStatusTip(tr("Clear all error messages, boxes, lines, etc. in the document."));
    connect(clearAct, SIGNAL(triggered()), textEdit, SLOT(clearEverything()));

    newAct = new QAction(QIcon(":/images/page_add.png"), tr("&New"), this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/folder.png"), tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/images/disk.png"), tr("&Save"), this);
    saveAct->setShortcut(tr("Ctrl+S"));
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcut(tr("Ctrl+X"));
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

    copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAct->setShortcut(tr("Ctrl+C"));
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

    pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcut(tr("Ctrl+V"));
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

    aboutAct = new QAction(tr("&About Open Turing"), this);
    aboutAct->setStatusTip(tr("View version and other informtion about Open Turing."));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addAction(findAct);
    editMenu->addAction(structCompleteAct);
    editMenu->addAction(autoCompleteAct);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(clearAct);
    viewMenu->addSeparator();
    viewMenu->addAction(lightThemeAct);
    viewMenu->addAction(darkThemeAct);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
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
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings("The Open Turing Project", "Open Turing Editor");
    QString theme = settings.value("theme", "Default").toString();
    qDebug() << "Loading settings. Theme: " << theme;
    if(theme == "Dark") {
        textEdit->darkTheme();
    } else {
        textEdit->lightTheme();
    }
}

void MainWindow::writeSettings()
{
    qDebug() << "Saving settings. Theme: " << textEdit->lex->getTheme();
    QSettings settings("The Open Turing Project", "Open Turing Editor");
    settings.setValue("theme", textEdit->lex->getTheme());
}

bool MainWindow::maybeSave()
{
    if (textEdit->isModified()) {
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

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("Open Turing Editor"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("Open Turing Editor"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << textEdit->text();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit->setModified(false);
    setWindowModified(false);

    QString shownName;
    if (curFile.isEmpty())
        shownName = "Untitled.t";
    else
        shownName = strippedName(curFile);

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Open Turing Editor")));
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
