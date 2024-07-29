#ifndef _ORDER_MANAGE_H
#define _ORDER_MANAGE_H

#include <QObject>
#include <QDebug>
#include "workconfig.h"

class OrderManage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QStringList> menu READ getMenu WRITE setMenu NOTIFY menuChanged)
public:
    OrderManage(QObject * parent = nullptr);
    ~OrderManage();

    QList<QStringList> getMenu() const;
    void setMenu(const QList<QStringList> &value);

signals:
    void menuChanged();
private:
    QList<QStringList> menu;
};

#endif
