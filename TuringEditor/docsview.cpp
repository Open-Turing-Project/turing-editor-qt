#include "docsview.h"
#include <QDebug>
#include "osinterop.h"

DocsView::DocsView(QWidget *parent) :
    QWebView(parent)
{
    setMinimumHeight(170);
    setMinimumWidth(300);
}

QSize DocsView::sizeHint() const {
    return QSize(350,660);
}

void DocsView::showDocs(QString page) {
    QDir docsDir = OSInterop::getExecutableDirectory();
    docsDir.cd("docs/html");
    QString loc = docsDir.absolutePath() + "/" + page.replace('.',"_").toLower() + ".html";
    if(QFileInfo(loc).exists()) {
        qDebug() << "Fetching docs at " << loc;
        load(QUrl::fromLocalFile(loc));
    }
}
