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

public slots:
    void activate();

private slots:
    void findAllPushed();
    void replacePushed();
    void replaceAllPushed();
    void findNextPushed();
signals:
    void findAll(QString text);
    void find(QString text,bool caseSensitive,bool regex,bool wholeWord);
    void findNext();
    void replace(QString text);
    void replaceAll(QString findText,QString repText,bool regex,bool greedyRegex);

private:
    Ui::FindReplaceDialog *ui;

    QString lastSearch;
};

#endif // FINDREPLACEDIALOG_H
