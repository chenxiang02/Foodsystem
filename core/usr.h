#ifndef _USR_H
#define _USR_H

#include "SqlSystem.h"
#include "CodeHandler.h"
#include "systemlog/fault.h"


class User : public SqlSystem
{
public:
    User();
    ~User();

    enum UserRight //用户权限
    {
        NormalUser=0,
        PrivilegedUser,
        SupremeAuthority
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
