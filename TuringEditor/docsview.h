#ifndef DOCSVIEW_H
#define DOCSVIEW_H

#include <QWebView>

class DocsView : public QWebView
{
    Q_OBJECT
public:
    explicit DocsView(QWidget *parent = 0);
    virtual QSize sizeHint() const;
signals:

public slots:
    void showDocs(QString page);
};

#endif // DOCSVIEW_H
