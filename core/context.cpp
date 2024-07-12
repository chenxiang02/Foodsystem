#include "context.h"


Context::Context(SqlSystem * DefineOperation,QObject *parent):QObject(parent),DefineOperate(DefineOperation)
{
    qDebug()<<Q_FUNC_INFO<<"Context类操作,带传参构造";
    qDebug()<<Q_FUNC_INFO<<this->DefineOperate->getSpecificClassName()+"操作";
}

Context::Context(QObject *parent):QObject(parent)
{
    qDebug()<<Q_FUNC_INFO<<"Context类操作,无传参构造";
}

Context::~Context()
{
    qDebug()<<Q_FUNC_INFO<<"Contex类析构";
}

bool Context::applyInsert(const int RightInsert, const QStringList InsertInfo)
{
    return this->DefineOperate->InsertData(RightInsert,InsertInfo);
}

bool Context::applyDeleteData(const int RightDelete, const QStringList DeleteInfo)
{
    return this->DefineOperate->DeleteData(RightDelete,DeleteInfo);
}

QMap<int, QStringList> Context::applyFindData(const int RightFind, const QStringList FindInfo)
{
    return this->DefineOperate->FindData(RightFind,FindInfo);
}

bool Context::applyUpdateData(const int RightUpdate, const QStringList UpdateInfo)
{
    return this->DefineOperate->UpdateData(RightUpdate,UpdateInfo);
}

void Context::setMethod(QString className)
{
    if(this->DefineOperate)
    {
       delete this->DefineOperate;
    }
    if(className == "User")
    {
        this->DefineOperate = new User;
    }
    else if(className == "Food")
    {
        this->DefineOperate = new Food;
    }
    else if(className == "Account")
    {
        this->DefineOperate = new Account;
    }
}
