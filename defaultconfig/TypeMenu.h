#ifndef _TYPE_MENU_H
#define _TYPE_MENU_H

#include <QObject>
#include <QDebug>
#include "core/food.h"

class TypeMenu : public QObject{
    Q_OBJECT
    Q_PROPERTY(QStringList food READ getFood WRITE setFood NOTIFY foodChanged)
    Q_PROPERTY(QStringList TypeList READ getTypeList WRITE setTypeList NOTIFY typeListChanged)

public:
    TypeMenu(QObject * parent = nullptr);
    ~TypeMenu();

    Q_INVOKABLE void getFoods();
    Q_INVOKABLE void findFood(QString data);//菜品 员工管理 订单管理 都有增删改查功能 后期用content去动态实例化复用统一
    Q_INVOKABLE void showAll();
    Q_INVOKABLE void addFood(QStringList data);
    Q_INVOKABLE void deleteFood(QString data);
    Q_INVOKABLE void modifyFood(QStringList data);
    Q_INVOKABLE QString typeMap(int type)
    {
        if(!TypeList.isEmpty())
            return TypeList.at(type);
        switch (type)
        {
            case 0:
            return "汤类";
            case 1:
            return "肉类";
            case 2:
            return "蔬菜";
        }

    }

    int decyTypeMap(QString data);

    QStringList getFood() const;
    void setFood(const QStringList &value);

    QStringList getTypeList() const;
    void setTypeList(const QStringList &value);

signals:
    void foodChanged();
    void typeListChanged();
private:
    QStringList food;
    QStringList oldFood;

    QStringList TypeList;

    Food * sql;
};

#endif
