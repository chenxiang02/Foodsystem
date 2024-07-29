#ifndef _CONTEXT_H
#define _CONTEXT_H

#include <QObject>
#include "SqlSystem.h"
#include "usr.h"
#include "account.h"
#include "food.h"
#include "network/CirThread.h"

class Context : public QObject
{
    Q_OBJECT
    SqlSystem * DefineOperate;
public:
    Context(SqlSystem * DefineOperation,QObject *parent= nullptr);
    Context(QObject *parent= nullptr);
    ~Context();

    Q_INVOKABLE bool applyInsert(const int RightInsert,const QStringList InsertInfo);
    Q_INVOKABLE bool applyDeleteData(const int RightDelete,const QStringList DeleteInfo);
    Q_INVOKABLE QMap<int,QStringList> applyFindData(const int RightFind,const QStringList FindInfo);
    Q_INVOKABLE bool applyUpdateData(const int RightUpdate,const QStringList UpdateInfo);
    Q_INVOKABLE void setMethod(QString className);

    Q_INVOKABLE int loginVerity(QStringList info);

    Q_INVOKABLE void clearSqlObject();

    QSqlQuery * applySqlOperator();
private:
    bool isDelete;

};

#endif
