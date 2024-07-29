#ifndef _SQL_SYSTEM_H
#define _SQL_SYSTEM_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QMap>
#include <QPair>
#include <QCryptographicHash>
#include <QDebug>
#include <QDateTime>

enum InsertMethod //插入权限
{
    IllegalityInsert=0,
    rowInsert,
    columnInsert,
    MaxRightInsert
};

enum DeleteMethod //删除权限
{
    IllegalityDelete=0,
    EmptyDelete,
    rowDelete,
    MaxRightDelete
};

enum UpdateMethod//更新权限
{
    IllegalityUpdate=0,
    AppointUpdate,
    AllUpdate,
    MaxRightUpdate
};

enum FindMethod//查找权限
{
   IllegalityFind=0,
   AppointFind,
   AllFind,
   MaxRightFind
};

class  SqlSystem
{
public:
    SqlSystem();
    virtual ~SqlSystem();

    void virtual SqlInit()=0;//数据库初始化接口

    QString virtual getSpecificClassName() = 0;

    //为啥不用引用传值 虽然快 但是可能会出现不可预料错误
    bool virtual InsertData(const int RightInsert,const QStringList InsertInfo)=0;//数据库插入信息接口
    bool virtual DeleteData(const int RightDelete,const QStringList DeleteInfo)=0;//数据库删除信息接口
    QMap<int,QStringList> virtual FindData(const int RightFind,const QStringList FindInfo)=0;//数据库查找信息接口
    bool virtual UpdateData(const int RightUpdate,const QStringList UpdateInfo)=0;//数据库更新接口

    virtual QSqlQuery * getSqlOperater()=0;

};

#endif
