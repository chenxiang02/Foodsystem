#include "OrderManage.h"

OrderManage::OrderManage(QObject *parent)
    : QObject(parent)
{
    qDebug()<<Q_FUNC_INFO<<"OrderManage类构造";
}

OrderManage::~OrderManage()
{
    qDebug()<<Q_FUNC_INFO<<"OrderManage类析构";
}

QList<QStringList> OrderManage::getMenu() const
{
    return menu;
}

void OrderManage::setMenu(const QList<QStringList> &value)
{
    menu = value;
}
