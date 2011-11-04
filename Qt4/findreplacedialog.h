#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QWidget>

namespace Ui {
    class FindReplaceDialog;
}

class FindReplaceDialog : public QWidget
{
    Q_OBJECT

public:
    explicit FindReplaceDialog(QWidget *parent = 0);
    ~FindReplaceDialog();

private slots:
    void findAllPushed();
    void findNextPushed();
signals:
    void findAll(QString text);
    void find(QString text,bool caseSensitive);
    void findNext();

private:
    Ui::FindReplaceDialog *ui;

    QString lastSearch;
};

#endif // FINDREPLACEDIALOG_H
