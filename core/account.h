#ifndef _ACCOUNT_H
#define _ACCOUNT_H
#include "SqlSystem.h"
#include "CodeHandler.h"
#include "systemlog/fault.h"

class Account : public SqlSystem
{
public:
    Account();
    ~Account();

    enum PayStatus{
        HavePaid = 0,
        CancelOrder,
    };

    void SqlInit() override;//初始化Sql

    QString getSpecificClassName() override;

    bool InsertData(const int RightInsert, const QStringList InsertInfo) override;

    bool DeleteData(const int RightDelete, const QStringList DeleteInfo) override;

    bool UpdateData(const int RightUpdate, const QStringList UpdateInfo) override;

    QMap<int,QStringList> FindData(const int RightFind, const QStringList FindInfo) override;

    QString PackageMenuData(QString data); //封装菜单记录
    QMap<int,QString> SeparateMenuData(QString data);//拆封菜单记录
private:
    QSqlDatabase ConnectSql;//sql操作

    QSqlQuery * sqlexe;//sql执行语句

    QDir * sqlPath;//默认sql文件路径获取

    CodeHandler * HashSecretkey;//加密解密功能类

    Fault printError;
};

#endif
