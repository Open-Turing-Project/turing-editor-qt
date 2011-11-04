/********************************************************************************
** Form generated from reading UI file 'findreplacedialog.ui'
**
** Created: Fri Nov 4 19:50:39 2011
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

    void setupUi(QWidget *FindReplaceDialog)
    {
        if (FindReplaceDialog->objectName().isEmpty())
            FindReplaceDialog->setObjectName(QString::fromUtf8("FindReplaceDialog"));
        FindReplaceDialog->resize(383, 178);
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
    } // retranslateUi

};

namespace Ui {
    class FindReplaceDialog: public Ui_FindReplaceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDREPLACEDIALOG_H
