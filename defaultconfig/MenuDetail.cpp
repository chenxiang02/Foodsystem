#include "MenuDetail.h"

MenuDetail::MenuDetail(QObject *parent):QObject(parent)
{
    qDebug()<<Q_FUNC_INFO<<"MenuDetail类构造";
}

MenuDetail::~MenuDetail()
{
    qDebug()<<Q_FUNC_INFO<<"MenuDetail类析构";
}

QList<QStringList> MenuDetail::getMenu() const
{
    return menu;
}

void MenuDetail::setMenu(const QList<QStringList> &value)
{
    menu = value;
    emit menuChanged();
}

void MenuDetail::addList(const QStringList &value)
{
    menu.push_back(value);
}
