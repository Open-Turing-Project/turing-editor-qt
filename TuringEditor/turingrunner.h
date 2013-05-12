#ifndef TURINGRUNNER_H
#define TURINGRUNNER_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QProcess>

#define RUNNER_FOLDER "/Users/tristan/Box/Dev/Projects/OpenTuringCompiler/dist/"
#define RUNNER_EXECUTABLE "compiler"

class TuringRunner : public QObject
{
    Q_OBJECT
public:
    explicit TuringRunner(QObject *parent, const QString &program);

signals:
    void errorFile(int line,QString errMsg, QString file, int from, int to);
    void errorGeneral(QString errMsg);

    void runFinished(bool success);
    void runningProgram();

public slots:
    void compileAndRun();
    void stopRun();

private slots:
    void runnerClosed(int status);
    void handleProcessError (QProcess::ProcessError error);
    void handleNewOutput();
private:
    void handleErrors(const QStringList &outputLines);
    void handleError(QString line);

    QProcess *turingRunner;

    QString mainProgram;
};

#endif // TURINGRUNNER_H
