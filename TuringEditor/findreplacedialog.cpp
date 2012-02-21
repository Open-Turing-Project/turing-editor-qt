#include "findreplacedialog.h"
#include "ui_findreplacedialog.h"

FindReplaceDialog::FindReplaceDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindReplaceDialog)
{
    ui->setupUi(this);
    connect(ui->findButton,SIGNAL(clicked()),this,SLOT(findAllPushed()));
    connect(ui->findNext,SIGNAL(clicked()),this,SLOT(findNextPushed()));
    connect(ui->replaceButton,SIGNAL(clicked()),this,SLOT(replacePushed()));
    connect(ui->replaceAll,SIGNAL(clicked()),this,SLOT(replaceAllPushed()));


    lastSearch = "";
}

void FindReplaceDialog::activate() {
    show();
    activateWindow();
    raise();
    //ui->findText->grabKeyboard();
}

void FindReplaceDialog::findAllPushed() {
    emit findAll(ui->findText->text());
}
void FindReplaceDialog::replacePushed() {
    if (ui->replaceText->text() != "" && ui->findText->text() != "" )
    {
        emit replace(ui->replaceText->text());
    }
}
void FindReplaceDialog::replaceAllPushed() {
    emit replaceAll(ui->findText->text(),ui->replaceText->text(),(ui->regexBox->checkState() == Qt::Checked),(ui->greedyRegex->checkState() == Qt::Checked));
}
void FindReplaceDialog::findNextPushed() {
    if(ui->findText->text() == lastSearch){
        emit findNext();
    } else {
        emit find(ui->findText->text(),(ui->caseSensitive->checkState() == Qt::Checked),(ui->regexBox->checkState() == Qt::Checked),(ui->wholeWord->checkState() == Qt::Checked));
    }
}

FindReplaceDialog::~FindReplaceDialog()
{
    delete ui;
}
