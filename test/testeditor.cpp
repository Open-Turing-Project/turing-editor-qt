#include "testeditor.h"

#include "turingeditorwidget.h"

void TestEditor::initTestCase() {
    edWin.show();
}

void TestEditor::init() {
    edWin.textEdit->setText("");
}

void TestEditor::structureComplete_data() {
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");
    QTest::addColumn<int>("completes");

    QTest::newRow("if statement") << "if bob then\n" << "if bob then\nend if\n" << 1;
    QTest::newRow("procedure") << "proc Yay(bill:int)\n" << "proc Yay(bill:int)\nend Yay\n" << 1;
    QTest::newRow("class") << "class Hi\nproc B\nend B\n"
                           << "class Hi\nproc B\nend B\nend Hi\n" << 1;
    QTest::newRow("multiple completions") << "class Hi\nproc B\n"
                           << "class Hi\nproc B\nend B\nend Hi\n" << 2;
}

void TestEditor::structureComplete() {
    QFETCH(QString, input);
    QFETCH(QString, result);
    QFETCH(int, completes);

    edWin.textEdit->setText(input);

    int curline = (edWin.textEdit->lines() - 1);
    int curpos = (edWin.textEdit->text(curline).length() - 1);
    edWin.textEdit->setCursorPosition(curline,curpos);

    // do the stuff!
    for(int i = 0; i < completes; ++i) {
        edWin.textEdit->completeStruct();
    }

    QCOMPARE(edWin.textEdit->text(), result);

    // verify it moved the cursor to the next line
    int newline,newpos;
    edWin.textEdit->getCursorPosition(&newline,&newpos);

    // notice the curline + completes
    // This is because multiple completes should move the cursor multiple times.
    QCOMPARE(curline + completes,newline);
}

void TestEditor::makeStack() {
    QStack<QPair<int,QString> > result;

    // validity should return an empty stack
    edWin.textEdit->setText("if bob\nput 'yay'\nend if");
    result = edWin.textEdit->makeStack();
    QVERIFY(result.isEmpty());

    // invalidity should return the incomplete structure
    edWin.textEdit->setText("if bob\nput 'yay'");
    result = edWin.textEdit->makeStack();
    QVERIFY(!result.isEmpty());
    QCOMPARE(result.top().second,QString("if"));
}

QTEST_MAIN(TestEditor)
