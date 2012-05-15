#include "messagemanager.h"

#include <QStandardItem>
#include <QFileInfo>
#include <QStringList>
#include <QList>

MessageManager::MessageManager(QObject *parent) :
    QStandardItemModel(parent), errorIcon(":/images/exclamation2.png"),fileIcon(":/images/page_error.png")
{
    QStringList columns("Message");
    setHorizontalHeaderLabels(columns);
}

void MessageManager::clearMessages() {
    QStandardItem *root = invisibleRootItem();

    QStandardItem *file;
    QList<QString> toSignal;
    // build up a list of files. All these files will be signaled as changed when removed
    for(int i = 0; i < root->rowCount();++i) {
        file = root->child(i);
        toSignal << file->data(MessageManager::FilePathRole).toString();
    }
    // clear all the data
    clear();
    // now we emit signals for all the files removed
    foreach(QString file, toSignal) {
        emit fileMessagesChanged(file);
    }
}

void MessageManager::clearMessagesFile(QString filePath) {
    QStandardItem *file = getFileItem(filePath);
    if(file == NULL) return;

    QStandardItem *message;
    QList<QStandardItem*> toRemove;
    // build up a list of items to remove because removing them in the middle of the loop
    // would throw off the indexing.
    for(int i = 0; i < file->rowCount();++i) {
        message = file->child(i);
        toRemove << message;
    }
    // now we remove them with iteration over a pointer list
    foreach(QStandardItem *m, toRemove) {
        removeMessage(m);
    }
}

void MessageManager::removeMessage(const QString &filePath, int line) {
    QStandardItem *file = getFileItem(filePath);
    if(file == NULL) return;

    QStandardItem *message;
    QList<QStandardItem*> toRemove;
    // build up a list of items to remove because removing them in the middle of the loop
    // would throw off the indexing.
    for(int i = 0; i < file->rowCount();++i) {
        message = file->child(i);
        if(message->data(MessageManager::LineNumberRole).toInt() == line) {
            toRemove << message;
        }
    }
    // now we remove them with iteration over a pointer list
    foreach(QStandardItem *m, toRemove) {
        removeMessage(m);
    }
}

void MessageManager::removeMessage(QStandardItem *message) {
    QStandardItem *file = message->parent();
    int row = message->row();
    file->removeRow(row);

    QString filePath = file->data(MessageManager::FilePathRole).toString(); // cache this since we might delete it
    if(file->rowCount() == 0) { // no more errors, remove the file item
        invisibleRootItem()->removeRow(file->row());
    }

    emit fileMessagesChanged(filePath);
}

QStandardItem *MessageManager::getFileItem(QString filePath) {
    QStandardItem *parentItem = invisibleRootItem();
    // find the file row
    QStandardItem *fileItem = NULL;
    for(int i = 0, e = parentItem->rowCount(); i < e;++i) {
        fileItem = parentItem->child(i);
        // the status tip contains the full file path
        if(fileItem->data(MessageManager::FilePathRole).toString() == filePath) {
            return fileItem;
        }
    }
    return NULL;
}
QStandardItem *MessageManager::createFileItem(QString filePath) {
    QStandardItem *item = new QStandardItem(fileIcon,QFileInfo(filePath).fileName());
    item->setData(filePath,Qt::ToolTipRole);
    item->setData(filePath,MessageManager::FilePathRole);
    item->setEditable(false);
    appendRow(item);
    return item;
}
QStandardItem *MessageManager::createMessageItem(QStandardItem *parent, int line, QString msg, int from, int to) {
    QStandardItem *item = new QStandardItem(errorIcon,msg);
    item->setData(tr("line %0").arg(line),Qt::ToolTipRole);
    item->setData(from,MessageManager::FromColRole);
    item->setData(to,MessageManager::ToColRole);
    item->setData(line,MessageManager::LineNumberRole);
    item->setEditable(false);
    parent->appendRow(item);
    return item;
}
void MessageManager::handleMessageFile(int line,QString msg, QString filePath, int from, int to) {
    // find the file row
    QStandardItem *fileItem = getFileItem(filePath);
    if(fileItem == NULL) {
        fileItem = createFileItem(filePath);
    }
    // add the error to it
    createMessageItem(fileItem,line,msg,from,to);
    emit fileMessagesChanged(filePath);
}
