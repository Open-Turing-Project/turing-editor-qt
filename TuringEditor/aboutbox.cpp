#include "aboutbox.h"
#include "ui_aboutbox.h"

AboutBox::AboutBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutBox)
{
    ui->setupUi(this);

    QString templ = tr("<font color='white'>Version %1</font>");
    ui->versionLabel->setText(templ.arg(VERSION_STRING));
}

AboutBox::~AboutBox()
{
    delete ui;
}



void AboutBox::on_pushButton_clicked()
{
    QWidget::close();
}
