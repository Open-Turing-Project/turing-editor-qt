#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <QStandardItemModel>

class MessageManager : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit MessageManager(QObject *parent = 0);
    // Custom data roles
    static const Qt::ItemDataRole FilePathRole = (Qt::ItemDataRole)(Qt::UserRole + 1); // QString
    static const Qt::ItemDataRole FromColRole = (Qt::ItemDataRole)(Qt::UserRole + 2); // int
    static const Qt::ItemDataRole ToColRole = (Qt::ItemDataRole)(Qt::UserRole + 3); // int
    static const Qt::ItemDataRole LineNumberRole = (Qt::ItemDataRole)(Qt::UserRole + 4); // int

    QStandardItem *getFileItem(QString filePath);

    void removeMessage(const QString &filePath, int line);
    void removeMessage(QStandardItem *message);
signals:
    void fileMessagesChanged(QString filePath);
public slots:
    void handleMessageFile(int line,QString errMsg, QString file, int from, int to);
    void clearMessages();
    void clearMessagesFile(QString filePath);
private:
    QStandardItem *createFileItem(QString filePath);
    QStandardItem *createMessageItem(QStandardItem *parent, int line, QString msg, int from, int to);

    QIcon errorIcon;
    QIcon fileIcon;
};

#endif // MESSAGEMANAGER_H
