#ifndef _SQL_SYSTEM_H
#define _SQL_SYSTEM_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QCryptographicHash>

class  SqlSystem
{
public:
    virtual ~SqlSystem();

    void virtual SqlInit()=0;//数据库初始化接口

    //为啥不用引用传值 虽然快 但是可能会出现不可预料错误
    bool virtual InsertData(const int RightInsert,const QString InsertInfo)=0;//数据库插入信息接口
    bool virtual DeleteData(const int RightDelete,const QString DeleteInfo)=0;//数据库删除信息接口
    void virtual FindData(const int RightFind,const QString FindInfo)=0;//数据库查找信息接口
    void virtual UpdateData(const int RightUpdate,const QString UpdateInfo)=0;//数据库更新接口

};

#endif
