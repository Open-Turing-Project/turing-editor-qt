#ifndef TESTEDITOR_H
#define TESTEDITOR_H

#include <QtTest/QtTest>
#include <QObject>

#include "mainwindow.h"

class TestEditor : public QObject
{
    Q_OBJECT
public slots:
    void initTestCase();
    void init();
private slots:
    void structureComplete_data();
    void structureComplete();
    void makeStack();
private:
    MainWindow edWin;
};

#endif // TESTEDITOR_H
