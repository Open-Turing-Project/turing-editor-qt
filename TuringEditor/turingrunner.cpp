#include "turingrunner.h"

#include <QFileInfo>
#include <QFile>
#include <QIODevice>
#include <QDir>

TuringRunner::TuringRunner(QObject *parent, const QString &program) :
    QObject(parent), compiledFile("")
{
    mainProgram = program;
}

void TuringRunner::startCompile() {
    QProcess *turingCompiler = new QProcess(this);
    QStringList args;
    args += "-compile";
    args += QDir::toNativeSeparators(mainProgram);
    connect(turingCompiler,SIGNAL(finished(int)),this,SLOT(compilerClosed(int)));
    turingCompiler->start(COMPILER_PATH,args);
}

void TuringRunner::compilerClosed(int status) {
    QFileInfo fInfo(mainProgram);
    QString byteCodeFile(fInfo.absolutePath() + "/" + fInfo.baseName() + ".tbc");

    QFile myFile(byteCodeFile); // Create a file handle for the file named
    QString line;

    if (!myFile.open(QIODevice::ReadOnly)) // Open the file
    {
        emit errorGeneral(tr("Can't open the compiled file: ") + byteCodeFile);
    }

    QTextStream stream( &myFile ); // Set the stream to read from myFile

    line = stream.readLine(); // this reads a line (QString) from the file

    // did something go wrong with the compile
    if(line.startsWith("ERROR")) {
        handleErrors(stream);
        emit compileFinished(false);
    } else {
        // good to go
        compiledFile = byteCodeFile;
        emit compileFinished(true);
    }
}

void TuringRunner::startRun() {
    if (!compiledFile.isEmpty()) {
        QProcess *turingRunner = new QProcess(this);
        QStringList args;
        args += "-file";
        args += QDir::toNativeSeparators(compiledFile);
        //connect(turingRunner,SIGNAL(finished(int)),this,SLOT(compilerClosed(int)));
        turingRunner->start(RUNNER_PATH,args);
    } else {
        emit errorGeneral(tr("No compiled file to run."));
    }
}

void TuringRunner::handleProcessError (QProcess::ProcessError error) {
    emit errorGeneral(tr("An error ooccured starting the compiler or runner. Error Number: %d").arg(error));
}

/**
  Emits error signals for compile errors.
  Takes a text stream that is synced to the first error message.
  The errors it reads look like:
  Line 2 [1 - 3] of BasicTest.t: 'Hi' has not been declared
  */
void TuringRunner::handleErrors(QTextStream &stream) {
    QRegExp tokErrRegex("Line (\\d+) \\[(\\d+) - (\\d+)\\] of (.+): (.+)");
    QRegExp lineErrRegex("Line (\\d+) \\[(\\d+)\\] of (.+): (.+)");
    QString line;

    // handle the errors
    line = stream.readLine();
    do {
        if(tokErrRegex.exactMatch(line) != -1) {

            int line = tokErrRegex.cap(1).toInt();
            int from = tokErrRegex.cap(2).toInt();
            int to = tokErrRegex.cap(3).toInt();
            QString file = tokErrRegex.cap(4);
            QString msg = tokErrRegex.cap(5);

            emit errorFile(line,msg,file,from,to);
        } else if(lineErrRegex.exactMatch(line)) {

            int line = lineErrRegex.cap(1).toInt();
            int from = lineErrRegex.cap(2).toInt();
            QString file = lineErrRegex.cap(3);
            QString msg = lineErrRegex.cap(4);

            emit errorFile(line,msg,file,from,-1);
        } else {
            // this should not happen. Just being safe
            emit errorGeneral("Error: " + line);
        }

        // get next line
        line = stream.readLine();
    } while(line != "");
}
