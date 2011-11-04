#include "findreplacetoolbar.h"
#include <QPushButton>

FindReplaceToolbar::FindReplaceToolbar(QWidget *parent) :
    QToolBar(parent)
{
    findBox = new QLineEdit(this);
    findBox->setPlaceholderText("Find");
    addWidget(findBox);

    replaceBox = new QLineEdit(this);
    replaceBox->setPlaceholderText("Replace");
    addWidget(findBox);

    QPushButton *nextButton = new QPushButton("Find &Next",this);
    connect(nextButton,SIGNAL(clicked()),this,SLOT(findNextPushed()));
    addWidget(nextButton);
}
void FindReplaceToolbar::findNextPushed() {
    emit findNext();
}
