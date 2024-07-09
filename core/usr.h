#ifndef _USR_H
#define _USR_H

#include "SqlSystem.h"
#include <QDebug>

class User : public SqlSystem
{
public:
    User();
    ~User();

    void SqlInit() override;//初始化Sql

    bool InsertData(const int RightInsert, const QString InsertInfo) override;

    bool DeleteData(const int RightDelete, const QString DeleteInfo) override;

    void UpdateData(const int RightUpdate, const QString UpdateInfo) override;

    void FindData(const int RightFind, const QString FindInfo) override;
private:
    QSqlDatabase ConnectSql;
    QSqlQuery * sqlexe;
    QDir * sqlPath;
};

#endif
