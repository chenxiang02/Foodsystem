#ifndef _ORDER_MANAGE_H
#define _ORDER_MANAGE_H

#include <QObject>
#include <QDebug>
#include <QStringList>
#include "core/account.h"
#include "workconfig.h"

class OrderManage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList menu READ getMenu WRITE setMenu NOTIFY menuChanged)
    Q_PROPERTY(bool isCurrent READ getIsCurrent WRITE setIsCurrent NOTIFY isCurrentChanged)
    Q_PROPERTY(QStringList showMenu READ getShowMenu WRITE setShowMenu NOTIFY showMenuChanged)
public:
    OrderManage(QObject * parent = nullptr);
    ~OrderManage();

    QStringList getMenu();
    void setMenu(const QStringList value);
    Q_INVOKABLE void getHistotyAccount();
    Q_INVOKABLE void getCurrentAccount();
    Q_INVOKABLE void getInformation(QString data);
    Q_INVOKABLE void cancelEvent(QString data,QString value);
    Q_INVOKABLE void confirmMenu(QString data);
    Q_INVOKABLE void findNode(QString data);

    bool getIsCurrent() const;
    void setIsCurrent(bool value);

    QStringList getShowMenu() const;
    void setShowMenu(const QStringList &value);

signals:
    void menuChanged();
    void isCurrentChanged();
    void showMenuChanged();
private:
    QStringList oldMenu;
    QStringList menu;
    bool isCurrent;
    bool isFind;
    Account * sql;
    QStringList showMenu;
};

#endif
