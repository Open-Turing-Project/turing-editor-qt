#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#include <QDialog>

namespace Ui {
    class AboutBox;
}

class AboutBox : public QWidget
{
    Q_OBJECT

public:
    explicit AboutBox(QWidget *parent = 0);
    ~AboutBox();

private:
    Ui::AboutBox *ui;
};

#endif // ABOUTBOX_H
