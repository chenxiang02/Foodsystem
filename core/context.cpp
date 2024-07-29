#include "context.h"
#include <QPair>
#include <QMap>

Context::Context(SqlSystem * DefineOperation,QObject *parent):QObject(parent),DefineOperate(DefineOperation)
{
    isDelete = false;
    qDebug()<<Q_FUNC_INFO<<"Context类操作,带传参构造";
    qDebug()<<Q_FUNC_INFO<<this->DefineOperate->getSpecificClassName()+"操作";
}

Context::Context(QObject *parent):QObject(parent)
{
    isDelete = false;
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
    qDebug()<<Q_FUNC_INFO<<className<<"已完成赋值";

    if(isDelete)
    {
        delete  this->DefineOperate;
        isDelete = false;
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
    this->isDelete = true;
}

int Context::loginVerity(QStringList info)
{
    qDebug()<<Q_FUNC_INFO;
    QString account= info.at(1),pas=info.at(2);
    QMap<int,QStringList> arg = this->applyFindData(1,info);

    QList<int> argIndex = arg.keys();

    QStringList userValue;
    QString arg1,arg2,right;

    for(int i = 0;i < argIndex.size();i++)
    {
       userValue =  arg[argIndex.at(i)];
       arg1 = userValue.at(0);
       arg2 = userValue.at(1);
       right = userValue.at(2);

       if(arg1 == account && arg2 == pas)//符合条件则返回权限
           return right.toInt();

    }

    return -1;
}

void Context::clearSqlObject()
{
    delete this->DefineOperate;
}

QSqlQuery *Context::applySqlOperator()//非必要请勿使用此方法被
{
    return this->DefineOperate->getSqlOperater();
}
