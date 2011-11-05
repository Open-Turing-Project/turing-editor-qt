/********************************************************************************
** Form generated from reading UI file 'findreplacedialog.ui'
**
** Created: Sat Nov 5 09:13:14 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDREPLACEDIALOG_H
#define UI_FINDREPLACEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FindReplaceDialog
{
public:
    QLineEdit *findText;
    QLabel *findLabel;
    QLabel *replaceLabel;
    QLineEdit *replaceText;
    QPushButton *findButton;
    QCheckBox *caseSensitive;
    QPushButton *replaceButton;
    QPushButton *replaceAll;
    QPushButton *findNext;
    QCheckBox *regexBox;
    QCheckBox *wholeWord;
    QCheckBox *greedyRegex;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *FindReplaceDialog)
    {
        if (FindReplaceDialog->objectName().isEmpty())
            FindReplaceDialog->setObjectName(QString::fromUtf8("FindReplaceDialog"));
        FindReplaceDialog->resize(383, 266);
        findText = new QLineEdit(FindReplaceDialog);
        findText->setObjectName(QString::fromUtf8("findText"));
        findText->setGeometry(QRect(80, 10, 281, 22));
        findLabel = new QLabel(FindReplaceDialog);
        findLabel->setObjectName(QString::fromUtf8("findLabel"));
        findLabel->setGeometry(QRect(20, 10, 62, 16));
        replaceLabel = new QLabel(FindReplaceDialog);
        replaceLabel->setObjectName(QString::fromUtf8("replaceLabel"));
        replaceLabel->setGeometry(QRect(20, 80, 62, 16));
        replaceText = new QLineEdit(FindReplaceDialog);
        replaceText->setObjectName(QString::fromUtf8("replaceText"));
        replaceText->setGeometry(QRect(80, 80, 281, 22));
        findButton = new QPushButton(FindReplaceDialog);
        findButton->setObjectName(QString::fromUtf8("findButton"));
        findButton->setGeometry(QRect(210, 40, 101, 31));
        caseSensitive = new QCheckBox(FindReplaceDialog);
        caseSensitive->setObjectName(QString::fromUtf8("caseSensitive"));
        caseSensitive->setGeometry(QRect(80, 150, 111, 20));
        replaceButton = new QPushButton(FindReplaceDialog);
        replaceButton->setObjectName(QString::fromUtf8("replaceButton"));
        replaceButton->setGeometry(QRect(80, 110, 101, 31));
        replaceAll = new QPushButton(FindReplaceDialog);
        replaceAll->setObjectName(QString::fromUtf8("replaceAll"));
        replaceAll->setGeometry(QRect(210, 110, 101, 31));
        findNext = new QPushButton(FindReplaceDialog);
        findNext->setObjectName(QString::fromUtf8("findNext"));
        findNext->setGeometry(QRect(80, 40, 101, 31));
        regexBox = new QCheckBox(FindReplaceDialog);
        regexBox->setObjectName(QString::fromUtf8("regexBox"));
        regexBox->setGeometry(QRect(80, 200, 151, 20));
        wholeWord = new QCheckBox(FindReplaceDialog);
        wholeWord->setObjectName(QString::fromUtf8("wholeWord"));
        wholeWord->setGeometry(QRect(230, 150, 101, 20));
        greedyRegex = new QCheckBox(FindReplaceDialog);
        greedyRegex->setObjectName(QString::fromUtf8("greedyRegex"));
        greedyRegex->setGeometry(QRect(230, 200, 121, 20));
        greedyRegex->setChecked(true);
        label = new QLabel(FindReplaceDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(250, 220, 91, 16));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label_2 = new QLabel(FindReplaceDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(250, 170, 91, 16));
        label_2->setFont(font);
        label_3 = new QLabel(FindReplaceDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 240, 291, 16));
        QFont font1;
        font1.setPointSize(11);
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setWordWrap(true);
        label_3->setOpenExternalLinks(true);

        retranslateUi(FindReplaceDialog);

        QMetaObject::connectSlotsByName(FindReplaceDialog);
    } // setupUi

    void retranslateUi(QWidget *FindReplaceDialog)
    {
        FindReplaceDialog->setWindowTitle(QApplication::translate("FindReplaceDialog", "Find and Replace", 0, QApplication::UnicodeUTF8));
        findLabel->setText(QApplication::translate("FindReplaceDialog", "Find:", 0, QApplication::UnicodeUTF8));
        replaceLabel->setText(QApplication::translate("FindReplaceDialog", "Replace:", 0, QApplication::UnicodeUTF8));
        findButton->setText(QApplication::translate("FindReplaceDialog", "Find All", 0, QApplication::UnicodeUTF8));
        caseSensitive->setText(QApplication::translate("FindReplaceDialog", "Case Sensitive", 0, QApplication::UnicodeUTF8));
        replaceButton->setText(QApplication::translate("FindReplaceDialog", "Replace", 0, QApplication::UnicodeUTF8));
        replaceAll->setText(QApplication::translate("FindReplaceDialog", "Replace All", 0, QApplication::UnicodeUTF8));
        findNext->setText(QApplication::translate("FindReplaceDialog", "Find Next", 0, QApplication::UnicodeUTF8));
        regexBox->setText(QApplication::translate("FindReplaceDialog", "Regular Expression", 0, QApplication::UnicodeUTF8));
        wholeWord->setText(QApplication::translate("FindReplaceDialog", "Whole Word", 0, QApplication::UnicodeUTF8));
        greedyRegex->setText(QApplication::translate("FindReplaceDialog", "Greedy Regex", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FindReplaceDialog", "(Replace All Only)", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FindReplaceDialog", "(Find Next Only)", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FindReplaceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Lucida Grande'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"http://regular-expressions.info\"><span style=\" text-decoration: underline; color:#0000ff;\">Click here</span></a> to learn more about regular expressions.</p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FindReplaceDialog: public Ui_FindReplaceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDREPLACEDIALOG_H
