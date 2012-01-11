#ifndef TURINGRUNNER_H
#define TURINGRUNNER_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QProcess>

class TuringRunner : public QObject
{
    Q_OBJECT
public:
    explicit TuringRunner(QObject *parent, const QString &program);

    bool isCompiled();

signals:
    void errorFile(int line,QString errMsg, QString file, int from, int to);
    void errorGeneral(QString errMsg);

    void compileFinished(bool success);

public slots:
    void startCompile();
    void startRun();
    void runFinished();
    void stopRun();

private slots:
    void compilerClosed(int status);
    void handleProcessError (QProcess::ProcessError error);
private:
    void handleErrors(QTextStream &stream);

    QProcess *turingRunner;

    QString mainProgram;
    QString compiledFile;
};

#endif // TURINGRUNNER_H
