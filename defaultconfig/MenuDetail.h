#ifndef _MENU_DETAIL_H
#define _MENU_DETAIL_H

#include <QObject>
#include <QDebug>

class MenuDetail : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QStringList> menu READ getMenu WRITE setMenu NOTIFY menuChanged)
public:
    MenuDetail(QObject * parent = nullptr);
    ~MenuDetail();

    QList<QStringList> getMenu() const;
    void setMenu(const QList<QStringList> &value);
    Q_INVOKABLE void addList(const QStringList &value);

signals:
    void menuChanged();

private:
    QList<QStringList> menu;
};

#endif
