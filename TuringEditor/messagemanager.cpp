#include "messagemanager.h"

#include <QStandardItem>
#include <QFileInfo>
#include <QStringList>

MessageManager::MessageManager(QObject *parent) :
    QStandardItemModel(parent), errorIcon(":/images/exclamation2.png"),fileIcon(":/images/page_error.png")
{
    QStringList columns("Message");
    setHorizontalHeaderLabels(columns);
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
    item->setData(filePath,Qt::StatusTipRole);
    item->setData(filePath,MessageManager::FilePathRole);
    appendRow(item);
    return item;
}
QStandardItem *MessageManager::createMessageItem(QStandardItem *parent, int line, QString msg, int from, int to) {
    QStandardItem *item = new QStandardItem(errorIcon,msg);
    item->setData(from,MessageManager::FromColRole);
    item->setData(to,MessageManager::ToColRole);
    item->setData(line,MessageManager::LineNumberRole);
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
}
