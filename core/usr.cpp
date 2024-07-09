#include "usr.h"

User::User()
{
   qDebug()<<Q_FUNC_INFO<<"User类构造";
   this->sqlPath = new QDir("/etc/sqlite");

   if(!this->sqlPath->exists(sqlPath->path()))//检查该目录是否存在
   {
        this->sqlPath->mkdir(sqlPath->path());//不存在则创建
   }
}

User::~User()
{
    qDebug()<<Q_FUNC_INFO<<"User类析沟";
}

void User::SqlInit()
{
    this->ConnectSql = QSqlDatabase::addDatabase("QSQLITE");

    this->ConnectSql.setDatabaseName(this->sqlPath->path()+"FoodDate.db");

    this->ConnectSql.open();

    if(!this->ConnectSql.isOpen())
    {
        qDebug()<<Q_FUNC_INFO<<this->ConnectSql.isOpen();
    }

    this->sqlexe = new QSqlQuery(this->ConnectSql);

    //用户表不存在则创建
    this->sqlexe->exec("CREATE TABLE IF NOT EXISTS users("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "username TEXT NOT NULL UNIQUE,"
                       "password TEXT NOT NULL,"
                       "role TEXT NOT NULL"
                       ");");
}

bool User::InsertData(const int RightInsert, const QString InsertInfo)
{

}

bool User::DeleteData(const int RightDelete, const QString DeleteInfo)
{

}

void User::UpdateData(const int RightUpdate, const QString UpdateInfo)
{

}

void User::FindData(const int RightFind, const QString FindInfo)
{

}


