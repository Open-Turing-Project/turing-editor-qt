#ifndef FINDREPLACETOOLBAR_H
#define FINDREPLACETOOLBAR_H

#include <QToolBar>
#include <QLineEdit>

class FindReplaceToolbar : public QToolBar
{
    Q_OBJECT
public:
    explicit FindReplaceToolbar(QWidget *parent = 0);

signals:
    void find(QString findText);
    void findNext();
public slots:
    void findNextPushed();
private:
    QLineEdit *findBox;
    QLineEdit *replaceBox;
};

#endif // FINDREPLACETOOLBAR_H
