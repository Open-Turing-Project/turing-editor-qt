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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QMenu;
class TuringEditorWidget;
class QsciStyle;

class FindReplaceDialog;
class TuringLexer;
class TestEditor;

class TuringRunner;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    void loadFile(const QString &fileName);
    virtual QSize sizeHint() const;

    friend class TestEditor;

public slots:
    void readSettings();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void documentWasModified();
    void completeStruct();
    void showHelp();
    void showSettings();

    void runProgram();
    void compileComplete(bool success);

    void handleErrorFile(int line,QString errMsg, QString file, int from, int to);
    void handleError(QString errMsg);

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    bool maybeSave();

    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    // prefs
    bool saveOnRun;
    bool confirmSave;

    TuringEditorWidget *textEdit;
    QString curFile;

    TuringRunner *currentRunner;

    FindReplaceDialog *findDialog;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QMenu *viewMenu;
    QToolBar *mainToolBar;

    //! completion
    QAction *structCompleteAct;
    QAction *autoCompleteAct;
    //! find and replace
    QAction *findAct;
    //! file actions
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    //! window actions
    QAction *exitAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *runAct;
    QAction *clearAct;
    QAction *helpAct;
    QAction *settingsAct;
};

#endif
