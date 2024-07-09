#ifndef _FOOD_H
#define _FOOD_H
#include "SqlSystem.h"


class Food : public SqlSystem
{
public:
    Food();
    ~Food();

    void SqlInit() override;//初始化Sql

    void InsertData(const int RightInsert, const QString InsertInfo) override;

    void DeleteData(const int RightDelete, const QString DeleteInfo) override;

    void UpdateData(const int RightUpdate, const QString UpdateInfo) override;

    void FindData(const int RightFind, const QString FindInfo) override;
private:
    QSqlDatabase ConnectSql;
    QSqlQuery * ExecuteSql;
    QDir * sqlPath;

};

#endif
