#include "account.h"

Account::Account()
{
    qDebug()<<Q_FUNC_INFO<<"Account类构造";
//    this->sqlPath = new QDir("/etc/sqlite");//上线时候请使用root权限操作 并解除注释代码
    this->sqlPath = new QDir("./");

    if(!this->sqlPath->exists(sqlPath->path()))//检查该目录是否存在
    {
         this->sqlPath->mkdir(sqlPath->path());//不存在则创建
    }

    //构建密钥
    this->HashSecretkey = new CodeHandler;

    //初始化
    this->SqlInit();
}

Account::~Account()
{
    this->ConnectSql.close();
    delete sqlPath;
    delete sqlexe;
    delete HashSecretkey;
    qDebug()<<Q_FUNC_INFO<<"Account类析沟";
}

void Account::SqlInit()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))//如果有默认连接
        this->ConnectSql = QSqlDatabase::database("qt_sql_default_connection");
    else
        this->ConnectSql = QSqlDatabase::addDatabase("QSQLITE");

    this->ConnectSql.setDatabaseName(this->sqlPath->path()+"FoodDate.db");

    this->ConnectSql.open();

    if(!this->ConnectSql.isOpen())
    {
        qDebug()<<Q_FUNC_INFO<<this->ConnectSql.isOpen();
    }

    this->sqlexe = new QSqlQuery(this->ConnectSql);

    //用户表不存在则创建
    this->sqlexe->exec("CREATE TABLE IF NOT EXISTS account("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "menu TEXT NOT NULL UNIQUE,"
                       "status TEXT NOT NULL,"
                       "selltime TEXT NOT NULL"
                       "totalvalue TEXT NOT NULL"
                       ");");
}

QString Account::getSpecificClassName()
{
    return "Account";
}

bool Account::InsertData(const int RightInsert, const QStringList InsertInfo)
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

    if(RightInsert == rowInsert)//这可以优化一下 难道表会固定5列数据吗 可以写出来更具有变化兼容性的插入
    {
        QString menu=InsertInfo.at(0),Status=InsertInfo.at(1),Count=InsertInfo.at(2);

        //加密数据
        QString EncryptFoodName = this->HashSecretkey->EncryptCode(menu);

        QString EncryptStatus = this->HashSecretkey->EncryptCode(Status);

        QString EncryptCreateTime = this->HashSecretkey->EncryptCode(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:MM:ss"));

        QString EncryptCount = this->HashSecretkey->EncryptCode(Count);

        //绑定
        this->sqlexe->bindValue(":menu",EncryptFoodName);
        this->sqlexe->bindValue(":status",EncryptStatus);
        this->sqlexe->bindValue(":selltime",EncryptCreateTime);
        this->sqlexe->bindValue(":totalvalue",EncryptCount);

        this->sqlexe->prepare("INSERT INFO account(menu,status,selltime,totalvalue)"
                              " VALUES ('"+EncryptFoodName+"','"+EncryptStatus+"','"+EncryptCreateTime+"','"+EncryptCount+"');");

        bool ret = this->sqlexe->exec();

        if(!ret)
        {
            qDebug()<<Q_FUNC_INFO<<"插入执行失败";
            printError.printLog("account表行插入执行失败");
            return ret;
        }

        this->sqlexe->clear();

        return ret; //返回执行结果
    }
    else if(RightInsert == columnInsert)
    {
        QString TableName = "users",ColumnName = InsertInfo.at(0),DataType = InsertInfo.at(1);

        //加密数据
        QString EncryptTableName = this->HashSecretkey->EncryptCode(TableName);

        QString EncryptColumnName = this->HashSecretkey->EncryptCode(ColumnName);

        QString EncryptDataType = this->HashSecretkey->EncryptCode(DataType);

        this->sqlexe->prepare("ALTER TABLE :TableName ADD COLUMN"
                              ":ColumnName :DataType");

        //绑定
        this->sqlexe->bindValue(":TableName",EncryptTableName);
        this->sqlexe->bindValue(":ColumnName",EncryptColumnName);
        this->sqlexe->bindValue(":DataType",EncryptDataType);

        bool ret = this->sqlexe->exec();

        this->sqlexe->clear();

        if(!ret)
        {
            qDebug()<<Q_FUNC_INFO<<"插入执行失败";
            printError.printLog("账单表列插入执行失败");
            return ret;
        }

        return ret; //返回执行结果
    }

    return false;
}

bool Account::DeleteData(const int RightDelete, const QStringList DeleteInfo)
{
    if(RightDelete <= IllegalityDelete || RightDelete >=MaxRightDelete)
    {
        qDebug()<<Q_FUNC_INFO<<"删除权限非法";
        return false;
    }

    qDebug()<<Q_FUNC_INFO<<"删除操作执行";

    if(RightDelete == EmptyDelete)//清空所有账单
    {
        this->sqlexe->prepare("DELETE FROM account;");

        bool ret = this->sqlexe->exec();

        this->sqlexe->clear();

        if(!ret)
        {
            qDebug()<<Q_FUNC_INFO<<"清空执行失败";
            printError.printLog("account表清空删除执行失败");
            return ret;
        }

        return ret;
    }
    else if(RightDelete == rowDelete)//删除指定账单
    {
        QString ColumnName = DeleteInfo.at(0),deleteValue = DeleteInfo.at(1);



        QString EncryptDeleteValue = this->HashSecretkey->EncryptCode(deleteValue);

        this->sqlexe->prepare("DELETE FROM account WHERE :ColumnName = '"+EncryptDeleteValue+"';");

        this->sqlexe->bindValue(":ColumnName",ColumnName);

        bool ret = this->sqlexe->exec();

        this->sqlexe->clear();

        if(!ret)
        {
            qDebug()<<Q_FUNC_INFO<<"删除执行失败";
            printError.printLog("account表删除行执行失败");
            return ret;
        }

        return ret;
    }

    return false;
}

bool Account::UpdateData(const int RightUpdate, const QStringList UpdateInfo)
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

        this->sqlexe->prepare("UPDATE account SET :AppointName = '"+EncryptAppointValue+"'"
                              " WHERE :Column = '"+EncryptUpdateValue+"'");

        this->sqlexe->bindValue(":AppointName",AppointName);
        this->sqlexe->bindValue(":Column",ColumnName);

        bool ret = this->sqlexe->exec();

        this->sqlexe->clear();

        if(!ret)
        {
            qDebug()<<Q_FUNC_INFO<<"更新执行失败";
            printError.printLog("account表更新失败");
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

        this->sqlexe->prepare("UPDATE food SET :UpdateOne = '"+EncryptUpdateOne+"',"
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
            printError.printLog("account表更新失败");
            return ret;
        }

        return ret;
    }

    return false;
}

QMap<int,QStringList> Account::FindData(const int RightFind, const QStringList FindInfo)
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
        this->sqlexe->prepare("SELECT * FROM account WHERE :Column = ':Value';");

        QString EncryptIndexValue = this->HashSecretkey->EncryptCode(IndexValue);

        this->sqlexe->bindValue(":Column",IndexName);
        this->sqlexe->bindValue(":Value",EncryptIndexValue);

        bool status = this->sqlexe->exec();

        if(!status)
        {
            qDebug()<<Q_FUNC_INFO<<"查询执行失败";
            printError.printLog("account表查询失败");
            ret.insert(0,QStringList("NULL"));
            return ret;
        }

        QString menu,Status,count;

        while(this->sqlexe->next())//将查询结果存储 并返回
        {
            QStringList arg;
            menu = this->HashSecretkey->DecryptCode(this->sqlexe->value(1).toString());
            Status = this->HashSecretkey->DecryptCode(this->sqlexe->value(2).toString());
            count = this->HashSecretkey->DecryptCode(this->sqlexe->value(3).toString());

            arg<<menu<<Status<<count;

            ret.insert(this->sqlexe->value(0).toInt(),arg);

            arg.clear();//因为是查找特定范围内容 清除即可 如果要获取全部内容则需要放在里面重复申请最好
        }

        this->sqlexe->clear();

        return ret;
    }
    else if(RightFind == AllFind)
    {
        this->sqlexe->prepare("SELECT * FROM food;");

        bool status = this->sqlexe->exec();
        if(!status)
        {
            qDebug()<<Q_FUNC_INFO<<"查询执行失败";
            printError.printLog("food用户表查询失败");
            return ret;
        }

        QString menu,Status,count;
        while(this->sqlexe->next())//将查询结果存储 并返回
        {
            QStringList arg;//申请栈空间比放在外面申请清除速度要快(实际运行可能会有查询内容过多而造成效率问题,后期要考虑分库分表,redis缓存)

            menu = this->HashSecretkey->DecryptCode(this->sqlexe->value(1).toString());
            Status = this->HashSecretkey->DecryptCode(this->sqlexe->value(2).toString());
            count = this->HashSecretkey->DecryptCode(this->sqlexe->value(3).toString());

            arg<<menu<<Status<<count;

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

QString Account::PackageMenuData(QString data)//先预留
{
    QString PackageData;
    int Length = data.length();//获取拆封数据长度
    for(int i = 0;i < Length;i++)//按照默认格式进行
    {

    }

}

QMap<int,QString> Account::SeparateMenuData(QString data)
{

}
