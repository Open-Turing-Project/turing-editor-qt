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

#include "documentmanager.h"

class QAction;
class QMenu;
class QLabel;
class QWebView;
class QDockWidget;
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
    //virtual QSize sizeHint() const;

    friend class TestEditor;

    DocumentManager *docMan;

public slots:
    void readSettings();
    void openFile(const QString &fileName);


protected:
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void open();
    void openRecentFile();
    void about();
    void completeStruct();
    void showHelp();
    void showSettings();

    void showDocs(QString page);

    void populateMarkMenu();
    void goToMark();

    void closeTab();

    void cursorMoved(int line, int index);

    void runProgram();
    void compileComplete(bool success);

    void handleError(QString errMsg);

private:

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createPanels();
    bool maybeSave();

    void addRecentFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    void updateRecentFileActions();

    // prefs
    bool saveOnRun;

    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];

    TuringRunner *currentRunner;
    TuringEditorWidget *runDoc;

    FindReplaceDialog *findDialog;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QMenu *viewMenu;
    QMenu *markMenu;
    QToolBar *mainToolBar;

    QDockWidget *docsPanel;
    QWebView *docsView;

    QLabel *lineLabel;

    //! auto-stuff
    QAction *structCompleteAct;
    QAction *autoCompleteAct;
    QAction *autoIndentAct;
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
    QAction *closeTabAct;
    QAction *pasteAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *runAct;
    QAction *clearAct;
    QAction *helpAct;
    QAction *settingsAct;
    QAction *zoomOutAct;
    QAction *zoomInAct;
};

#endif
