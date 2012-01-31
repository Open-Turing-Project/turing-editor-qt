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

#include <QtSingleApplication>
#include <QFontDatabase>
#include <QFile>
#include <QFileInfo>
#include <QSharedMemory>
#include <QMessageBox>
#include <QString>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(turing);
    QtSingleApplication app(argc, argv);

    QString openFileName("");
    if (argc >= 2) {
        openFileName = QFileInfo(argv[1]).absoluteFilePath();
    }

    if (app.isRunning())
        return !app.sendMessage(openFileName);

    // placing a stylesheet in the same folder allows the editor to be themed.
    QFile file("stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    app.setStyleSheet(styleSheet);

    QCoreApplication::setOrganizationName("The Open Turing Project");
    QCoreApplication::setOrganizationDomain("compsci.ca");
    QCoreApplication::setApplicationName("Open Turing Editor");

    MainWindow mainWin;
    mainWin.show();

    QObject::connect(&app,SIGNAL(messageReceived(const QString&)),&mainWin,SLOT(openFile(const QString&)));

    // open a file?
    if (openFileName != "") {
        mainWin.openFile(openFileName);
    }

    return app.exec();
}
