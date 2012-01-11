#include "testeditor.h"

#include "turingeditorwidget.h"

void TestEditor::initTestCase() {
}

void TestEditor::init() {
    editor.setText("");
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
    QTest::newRow("cursor on decl") << "proc Yay(bill:int)"
                                    << "proc Yay(bill:int)\n    \nend Yay\n" << 1;
}

void TestEditor::structureComplete() {
    QFETCH(QString, input);
    QFETCH(QString, result);
    QFETCH(int, completes);

    editor.setText(input);

    int curline = (editor.lines() - 1);
    int curpos = (editor.text(curline).length() - 1);
    editor.setCursorPosition(curline,curpos);

    // do the stuff!
    for(int i = 0; i < completes; ++i) {
        editor.completeStruct();
    }

    QCOMPARE(editor.text(), result);

    // verify it moved the cursor to the next line
    int newline,newpos;
    editor.getCursorPosition(&newline,&newpos);

    // notice the curline + completes
    // This is because multiple completes should move the cursor multiple times.
    QCOMPARE(curline + completes,newline);
}

void TestEditor::makeStack() {
    QStack<QPair<int,QString> > result;

    // validity should return an empty stack
    editor.setText("if bob\nput 'yay'\nend if");
    result = editor.makeStack(-1);
    QVERIFY(result.isEmpty());

    // invalidity should return the incomplete structure
    editor.setText("if bob\nput 'yay'");
    result = editor.makeStack(-1);
    QVERIFY(!result.isEmpty());
    QCOMPARE(result.top().second,QString("if"));
}

void TestEditor::findPOIs() {
    QList<TuringEditorWidget::POILine *> pois;

    editor.setText("proc Yo\nend Yo\n    if bob then\n\tend if");
    pois = editor.findPOIs();
    QCOMPARE(pois.size(),4); // begin and end

    QCOMPARE(pois[0]->line,0);QCOMPARE(pois[3]->line,3);

    QCOMPARE(QString(pois[0]->id), QString("Yo"));
    QCOMPARE(QString(pois[0]->type),QString("proc"));

    QCOMPARE(QString(pois[1]->id), QString("Yo"));
    QCOMPARE(QString(pois[1]->type),QString("end"));
    // end is connected to begin
    QVERIFY(pois[0]->other == pois[1]); QVERIFY(pois[1]->other == pois[0]);

    QCOMPARE(pois[2]->indent,4); QCOMPARE(pois[3]->indent,4);

    QCOMPARE(QString(pois[2]->id), QString(""));
    QCOMPARE(QString(pois[2]->type),QString("if"));

    QCOMPARE(QString(pois[3]->id), QString("if"));
    QCOMPARE(QString(pois[3]->type),QString("end"));
    // end is connected to begin
    QVERIFY(pois[2]->other == pois[3]); QVERIFY(pois[3]->other == pois[2]);

    // CASE 2 ========

    editor.setText("pervasive module Yo(lol : string)\nend Yotel");
    pois = editor.findPOIs();
    QCOMPARE(pois.size(),2); // begin and end

    QCOMPARE(QString(pois[0]->id), QString("Yo"));
    QCOMPARE(QString(pois[0]->type),QString("module"));

    QCOMPARE(QString(pois[1]->id), QString("Yotel"));
    QCOMPARE(QString(pois[1]->type),QString("end"));
    // end is not connected to begin
    QVERIFY(pois[0]->other == NULL); QVERIFY(pois[1]->other == NULL);

    // CASE 3 - nesting =========

    editor.setText("class Hi\nproc B\n\nend B\nend Hi");
    pois = editor.findPOIs();
    QCOMPARE(pois.size(),4); // begin and end

    QCOMPARE(QString(pois[0]->id), QString("Hi"));
    QCOMPARE(QString(pois[0]->type),QString("class"));
    QVERIFY(pois[3]->other == pois[0]); QVERIFY(pois[0]->other == pois[3]);

    QCOMPARE(QString(pois[1]->id), QString("B"));
    QCOMPARE(QString(pois[1]->type),QString("proc"));
    QVERIFY(pois[1]->other == pois[2]); QVERIFY(pois[2]->other == pois[1]);


}

void TestEditor::autoIndentAll_data() {
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");

    QTest::newRow("no body") << "if bob then\nend if\n" << "if bob then\nend if\n";
    QTest::newRow("mult-line body") << "loop\n h\n h\n h\nend loop"
                                    << "loop\n    h\n    h\n    h\nend loop";
    QTest::newRow("nesting") << "class Hi\nproc B\nend B\nend Hi\n"
                             << "class Hi\n    proc B\n    end B\nend Hi\n";
    QTest::newRow("tabs->soft tabs") << "if bob then\n\tHI!\nend if\n"
                                     << "if bob then\n    HI!\nend if\n";
}

void TestEditor::autoIndentAll() {
    QFETCH(QString,input);
    QFETCH(QString,result);

    editor.setText(input);
    editor.autoIndentAll();
    QCOMPARE(editor.text(),result);

}

QTEST_MAIN(TestEditor)
