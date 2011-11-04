#include "findreplacedialog.h"
#include "ui_findreplacedialog.h"

FindReplaceDialog::FindReplaceDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindReplaceDialog)
{
    ui->setupUi(this);
    connect(ui->findButton,SIGNAL(clicked()),this,SLOT(findAllPushed()));
    connect(ui->findNext,SIGNAL(clicked()),this,SLOT(findNextPushed()));


    lastSearch = "";
}

void FindReplaceDialog::findAllPushed() {
    emit findAll(ui->findText->text());
}
void FindReplaceDialog::findNextPushed() {
    if(ui->findText->text() == lastSearch){
        emit findNext();
    } else {
        emit find(ui->findText->text(),(ui->caseSensitive->checkState() == Qt::Checked));
    }
}

FindReplaceDialog::~FindReplaceDialog()
{
    delete ui;
}
