#include "usr.h"

User::User()
{
   qDebug()<<Q_FUNC_INFO<<"User类构造";
   //    this->sqlPath = new QDir("/etc/sqlite");//上线时候请使用root权限操作 并解除注释代码
       this->sqlPath = new QDir("./");

   if(!this->sqlPath->exists(sqlPath->path()))//检查该目录是否存在
   {
        this->sqlPath->mkdir(sqlPath->path());//不存在则创建
   }

   //构建密钥
   this->HashSecretkey = new CodeHandler;

   //默认参数初始化
   this->SqlInit();
}

User::~User()
{
    this->ConnectSql.close();
    delete sqlPath;
    delete sqlexe;
    delete HashSecretkey;
    qDebug()<<Q_FUNC_INFO<<"User类析沟";
}

void User::SqlInit()
{
   if(QSqlDatabase::contains("qt_sql_default_connection"))//如果有默认连接
       this->ConnectSql = QSqlDatabase::database("qt_sql_default_connection");
   else
       this->ConnectSql = QSqlDatabase::addDatabase("QSQLITE");

    this->ConnectSql.setDatabaseName("FoodDate.db");

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

QString User::getSpecificClassName()
{
    return "User";
}

QSqlQuery *User::getSqlOperater()
{
    return this->sqlexe;
}

bool User::InsertData(const int RightInsert, const QStringList InsertInfo) //过多冗杂功能 后期优化可以考虑职责剥离
{
    if(RightInsert <= IllegalityInsert || RightInsert >= MaxRightInsert) //非法操作
     {
        qDebug()<<Q_FUNC_INFO<<"操作权限非法";
        return false; //后期优化可以考虑用错误集来代替 方便排错
     }

    if(InsertInfo.length() > 4 || InsertInfo.length() <= 0)
    {
        qDebug()<<Q_FUNC_INFO<<"插入无效数据";
        return false;
    }

    //提示信息
    qDebug()<<Q_FUNC_INFO<<"插入操作执行";

    if(RightInsert == rowInsert)
    {
        QString userName=InsertInfo.at(0),password=InsertInfo.at(1),role=InsertInfo.at(2);

        //加密数据
        QString EncryptUserName = this->HashSecretkey->EncryptCode(userName);

        QString EncryptPassWord = this->HashSecretkey->EncryptCode(password);

        QString EncryptRole = this->HashSecretkey->EncryptCode(role);

        bool ret = this->sqlexe->exec("INSERT INTO users(username,password,role)"
                                      " VALUES ('"+EncryptUserName+"','"+EncryptPassWord+"','"+EncryptRole+"');");

        this->sqlexe->clear();

        if(!ret)
        {
            qDebug()<<Q_FUNC_INFO<<"插入执行失败";
            printError.printLog("users用户表插入执行失败");
            return ret;
        }

        return ret; //返回执行结果
    }
    else if(RightInsert == columnInsert)
    {
        QString TableName = "users",ColumnName = InsertInfo.at(0),DataType = InsertInfo.at(1);
        this->sqlexe->prepare("ALTER TABLE :TableName ADD COLUMN"
                              ":ColumnName :DataType");

        //加密数据
        QString EncryptTableName = this->HashSecretkey->EncryptCode(TableName);

        QString EncryptColumnName = this->HashSecretkey->EncryptCode(ColumnName);

        QString EncryptDataType = this->HashSecretkey->EncryptCode(DataType);

        //绑定
        this->sqlexe->bindValue(":TableName",EncryptTableName);
        this->sqlexe->bindValue(":ColumnName",EncryptColumnName);
        this->sqlexe->bindValue(":DataType",EncryptDataType);


        bool ret = this->sqlexe->exec();

        this->sqlexe->clear();

        if(!ret)
        {
            qDebug()<<Q_FUNC_INFO<<"插入执行失败";
            printError.printLog("user用户表插入执行失败");
            return ret;
        }

        return ret; //返回执行结果
    }

    return false;
}

bool User::DeleteData(const int RightDelete, const QStringList DeleteInfo)
{
    if(RightDelete <= IllegalityDelete || RightDelete >=MaxRightDelete)
    {
        qDebug()<<Q_FUNC_INFO<<"删除权限非法";
        return false;
    }

    qDebug()<<Q_FUNC_INFO<<"删除操作执行";

    if(RightDelete == EmptyDelete)//清空所有非特权用户数据
    {
        QString RightUser = this->HashSecretkey->EncryptCode(QString::number(NormalUser));

        this->sqlexe->prepare("DELETE FROM users WHERE role = '"+RightUser+"';");

        bool ret = this->sqlexe->exec();

        this->sqlexe->clear();

        if(!ret)
        {
            qDebug()<<Q_FUNC_INFO<<"删除执行失败";
            printError.printLog("user用户表删除执行失败");
            return ret;
        }

        return ret;
    }
    else if(RightDelete == rowDelete)//删除指定的非特权用户 DeleteInfo格式: "username","xxx"
    {
        QString ColumnName = DeleteInfo.at(0),deleteValue = DeleteInfo.at(1);

        QString EncryptDeleteValue = this->HashSecretkey->EncryptCode(deleteValue);

        this->sqlexe->prepare("DELETE FROM users WHERE :ColumnName = '"+EncryptDeleteValue+"'"
                              " AND role == '0';");

        this->sqlexe->bindValue(":ColumnName",ColumnName);

        bool ret = this->sqlexe->exec();

        this->sqlexe->clear();

        if(!ret)
        {
            qDebug()<<Q_FUNC_INFO<<"删除执行失败";
            printError.printLog("user用户表删除执行失败");
            return ret;
        }

        return ret;
    }

    return false;

}

bool User::UpdateData(const int RightUpdate, const QStringList UpdateInfo)
{
     if(RightUpdate <= IllegalityUpdate || RightUpdate >= MaxRightUpdate)
     {
        qDebug()<<Q_FUNC_INFO<<"更新权限非法";
        return false;
     }

     if(UpdateInfo.length()%2 != 0)//传输信息丢失
     {
        qDebug()<<Q_FUNC_INFO<<"数据丢失";
        return false;
     }

     qDebug()<<Q_FUNC_INFO<<"更新操作执行";

     if(RightUpdate == AppointUpdate)//指定更新
     {
         QString AppointName = UpdateInfo.at(0),AppointValue = UpdateInfo.at(1),
                 ColumnName = UpdateInfo.at(2),UpdateValue = UpdateInfo.at(3);



         //加密
         QString EncryptAppointValue = this->HashSecretkey->EncryptCode(AppointValue);

         QString EncryptUpdateValue = this->HashSecretkey->EncryptCode(UpdateValue);

         this->sqlexe->prepare("UPDATE users SET :AppointName = '"+EncryptAppointValue+"'"
                               " WHERE :Column = '"+EncryptUpdateValue+"'");

         this->sqlexe->bindValue(":AppointName",AppointName);
         this->sqlexe->bindValue(":Column",ColumnName);

         bool ret = this->sqlexe->exec();

         this->sqlexe->clear();

         if(!ret)
         {
             qDebug()<<Q_FUNC_INFO<<"更新执行失败";
             printError.printLog("users用户表更新失败");
             return ret;
         }

         return ret;
     }
     else if(RightUpdate == AllUpdate)//全更新
     {

         QString UpdateOneC = UpdateInfo.at(2),UpdateOne = UpdateInfo.at(3),
                 UpdateTwoC = UpdateInfo.at(4),UpdateTwo = UpdateInfo.at(5),
                 UpdateThreeC = UpdateInfo.at(6),UpdateThree = UpdateInfo.at(7),
                 FindName = UpdateInfo.at(0),FindValue = UpdateInfo.at(1);

         //加密
         QString EncryptUpdateOne = this->HashSecretkey->EncryptCode(UpdateOne);

         QString EncryptUpdateTwo = this->HashSecretkey->EncryptCode(UpdateTwo);

         QString EncryptUpdateThree = this->HashSecretkey->EncryptCode(UpdateThree);

         QString EncryptFindValue = this->HashSecretkey->EncryptCode(FindValue);

         this->sqlexe->prepare("UPDATE users SET :UpdateOne = '"+EncryptUpdateOne+"',"
                               ":UpdateTwo = '"+EncryptUpdateTwo+"',"
                               ":UpdateThree = '"+EncryptUpdateThree+"' WHERE :FindName = '"+EncryptFindValue+"';");

         this->sqlexe->bindValue(":UpdateOne",UpdateOneC);
         this->sqlexe->bindValue(":UpdateTwo",UpdateTwoC);
         this->sqlexe->bindValue(":UpdateThree",UpdateThreeC);
         this->sqlexe->bindValue(":FindName",FindName);

         bool ret = this->sqlexe->exec();

         this->sqlexe->clear();

         if(!ret)
         {
             qDebug()<<Q_FUNC_INFO<<"更新执行失败";
             printError.printLog("users用户表更新失败");
             return ret;
         }

         return ret;
     }

     return false;
}

QMap<int,QStringList> User::FindData(const int RightFind, const QStringList FindInfo)
{
    QMap<int,QStringList> ret;
    if(RightFind <=IllegalityDelete || RightFind >= MaxRightFind)
    {
        qDebug()<<Q_FUNC_INFO<<"非法查找权限";
        QStringList arg;
        arg<<"null";
        ret.insert(0,arg);
        return ret;
    }

    if(RightFind == AppointFind)
    {
        QString IndexName = FindInfo.at(0),IndexValue = FindInfo.at(1);

        QString EncryptIndexValue = this->HashSecretkey->EncryptCode(IndexValue);

        bool status = this->sqlexe->exec("select * from users where "+IndexName+" = '"+EncryptIndexValue+"';");

        if(!status)//检查是否执行成功
        {
            qDebug()<<Q_FUNC_INFO<<"查询执行失败";
            printError.printLog("users用户表查询失败");
            ret.insert(0,QStringList("NULL"));
            return ret;
        }

        QString username,password,role;
        QStringList arg;

        while(this->sqlexe->next())//将查询结果存储 并返回
        {
            username = this->HashSecretkey->DecryptCode(this->sqlexe->value(1).toString());
            password = this->HashSecretkey->DecryptCode(this->sqlexe->value(2).toString());
            role = this->HashSecretkey->DecryptCode(this->sqlexe->value(3).toString());

            arg<<username<<password<<role;

            ret.insert(this->sqlexe->value(0).toInt(),arg);

            arg.clear();//这里其实能考虑一下是申请空间快 还是清除空间快
        }

        this->sqlexe->clear();

        return ret;
    }
    else if(RightFind == AllFind)
    {
        this->sqlexe->prepare("SELECT * FROM users;");

        bool status = this->sqlexe->exec();
        if(!status)
        {
            qDebug()<<Q_FUNC_INFO<<"查询执行失败";
            printError.printLog("users用户表查询失败");
            return ret;
        }

        while(this->sqlexe->next())//将查询结果存储 并返回
        {
            QStringList arg;//申请栈空间比放在外面申请清除速度要快(实际运行可能会有查询内容过多而造成效率问题,后期要考虑分库分表,redis缓存)
            QString username,password,role;

            username = this->HashSecretkey->DecryptCode(this->sqlexe->value(1).toString());
            password = this->HashSecretkey->DecryptCode(this->sqlexe->value(2).toString());
            role = this->HashSecretkey->DecryptCode(this->sqlexe->value(3).toString());

            arg<<username<<password<<role;

            ret.insert(this->sqlexe->value(0).toInt(),arg);
        }

        this->sqlexe->clear();

        return ret;
    }

    QStringList arg;
    arg<<"null";
    ret.insert(0,arg);

    return ret;
}
