#include "turingrunner.h"

#include <QFileInfo>
#include <QFile>
#include <QIODevice>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>

TuringRunner::TuringRunner(QObject *parent, const QString &program) :
    QObject(parent)
{
    mainProgram = QFileInfo(program).absoluteFilePath();
    turingRunner = NULL;
}

void TuringRunner::compileAndRun() {
    QString runnerPath = QCoreApplication::applicationDirPath () + "/" + RUNNER_PATH;
    turingRunner = new QProcess(this);
    turingRunner->setWorkingDirectory(QCoreApplication::applicationDirPath());
    QStringList args;
    args += "-run";
    args += QDir::toNativeSeparators(mainProgram);
    connect(turingRunner,SIGNAL(finished(int)),this,SLOT(runnerClosed(int)));
    connect(turingRunner,SIGNAL(readyReadStandardOutput()),this,SLOT(handleNewOutput()));
    turingRunner->start(runnerPath,args);
}

void TuringRunner::handleNewOutput() {
    qDebug() << L"Handling Output";
    while(turingRunner->bytesAvailable() > 0) {
        QString line(turingRunner->readLine());
        line = line.trimmed();
        if(line != "") {
            qDebug() << L"Read line " << line;
            if(line.startsWith("Running")) {
                emit runningProgram();
            } else if(line.startsWith("Error on line") || line.startsWith("Run time error")) {
                handleError(line);
            }
        }
    }
}

void TuringRunner::runnerClosed(int status) {
    if (status != 0) {
        emit errorGeneral("Turing runner closed unexpectedly.");
        emit runFinished(false);
        return;
    }

    QString runnerOutput(turingRunner->readAllStandardOutput().constData());
    QStringList outputLines = runnerOutput.split(QRegExp("\\r?\\n"));

    // did something go wrong with the compile or run?
    if(outputLines.first().startsWith("Compile Errors:") || runnerOutput.indexOf("Run time error") != -1) {
        //handleErrors(outputLines);
        emit runFinished(false);
    } else {
        emit runFinished(true);
    }
}

void TuringRunner::handleProcessError (QProcess::ProcessError error) {
    emit errorGeneral(tr("An error ooccured starting the compiler or runner. Error Number: %d").arg(error));
}

/**
  Emits error signals for compile errors.
  Takes a text stream that is synced to the first error message.
  The errors it reads look like:
  Error on line 2 [1 - 3] of BasicTest.t: 'Hi' has not been declared
  */
void TuringRunner::handleErrors(const QStringList &outputLines) {
    QRegExp tokErrRegex("line (\\d+) \\[(\\d+) ?- ?(\\d+)\\] of (.+): (.+)");
    QRegExp lineErrRegex("line (\\d+) \\[(\\d+)\\] of (.+): (.+)");

    // handle the errors
    foreach(QString line, outputLines) {
        qDebug() << L"Error line: " << line;
        if(tokErrRegex.indexIn(line) != -1) {

            int line = tokErrRegex.cap(1).toInt();
            int from = tokErrRegex.cap(2).toInt();
            int to = tokErrRegex.cap(3).toInt();
            if(to==0) to = -1; // turing uses 0 to convey no end. We use -1.
            QString file = QDir::fromNativeSeparators(tokErrRegex.cap(4));
            QString msg = tokErrRegex.cap(5);

            emit errorFile(line,msg,file,from,to);
        } else if(lineErrRegex.indexIn(line) != -1) {

            int line = lineErrRegex.cap(1).toInt();
            int from = lineErrRegex.cap(2).toInt();
            int to = -1;
            QString file = QDir::fromNativeSeparators(lineErrRegex.cap(3));
            QString msg = lineErrRegex.cap(4);

            emit errorFile(line,msg,file,from,to);
        }
    }
}
void TuringRunner::handleError(QString line) {
    QRegExp tokErrRegex("line (\\d+) \\[(\\d+) ?- ?(\\d+)\\] of (.+): (.+)");
    QRegExp lineErrRegex("line (\\d+) \\[(\\d+)\\] of (.+): (.+)");
    qDebug() << L"Error line: " << line;
    if(tokErrRegex.indexIn(line) != -1) {

        int line = tokErrRegex.cap(1).toInt();
        int from = tokErrRegex.cap(2).toInt()-1;
        int to = tokErrRegex.cap(3).toInt()-1;
        QString file = QDir::fromNativeSeparators(tokErrRegex.cap(4));
        QString msg = tokErrRegex.cap(5);

        emit errorFile(line,msg,file,from,to);
    } else if(lineErrRegex.indexIn(line) != -1) {

        int line = lineErrRegex.cap(1).toInt();
        int from = lineErrRegex.cap(2).toInt()-1;
        int to = -1;
        QString file = QDir::fromNativeSeparators(lineErrRegex.cap(3));
        QString msg = lineErrRegex.cap(4);

        emit errorFile(line,msg,file,from,to);
    }
}

void TuringRunner::stopRun() {
    if (turingRunner && turingRunner->state() == QProcess::Running) {
        turingRunner->terminate();
        //runFinished(); should get called by close handler
    }
}
