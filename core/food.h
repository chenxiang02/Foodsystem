#ifndef _FOOD_H
#define _FOOD_H
#include "SqlSystem.h"
#include "CodeHandler.h"
#include "systemlog/fault.h"


class Food : public SqlSystem
{
public:
    Food();
    ~Food();
    enum StatusShop//商品状态
    {
        StartSell=0,//启售
        StopSell,//停止售卖
        Empty,//商品为空
        Full//商品有余
    };

    enum FoodType{
        Soup = 0,
        Meat,
        Vegetable
    };

    void SqlInit() override;//初始化Sql

    QString getSpecificClassName() override;

    QSqlQuery * getSqlOperater() override;

    bool InsertData(const int RightInsert, const QStringList InsertInfo) override;

    bool DeleteData(const int RightDelete, const QStringList DeleteInfo) override;

    bool UpdateData(const int RightUpdate, const QStringList UpdateInfo) override;

    QMap<int,QStringList> FindData(const int RightFind, const QStringList FindInfo) override;
private:
    QSqlDatabase ConnectSql;//sql操作

    QSqlQuery * sqlexe;//sql执行语句

    QDir * sqlPath;//默认sql文件路径获取

    CodeHandler * HashSecretkey;//加密解密功能类

    Fault printError;
};

#endif
