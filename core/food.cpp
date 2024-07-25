#include "food.h"

Food::Food()
{
    qDebug()<<Q_FUNC_INFO<<"Food类构造";
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

Food::~Food()
{
    this->ConnectSql.close();
    delete sqlPath;
    delete sqlexe;
    delete HashSecretkey;
    qDebug()<<Q_FUNC_INFO<<"Food类析沟";
}

void Food::SqlInit()
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
    this->sqlexe->exec("CREATE TABLE IF NOT EXISTS food("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "foodname TEXT NOT NULL UNIQUE,"
                       "status TEXT NOT NULL,"
                       "foodtype TEXT NOT NULL,"
                       "price TEXT NOT NULL,"
                       "createtime TEXT NOT NULL,"
                       "count TEXT NOT NULL"
                       ");");
}

QString Food::getSpecificClassName()
{
    return "Food";
}

bool Food::InsertData(const int RightInsert, const QStringList InsertInfo)
{
    if(RightInsert <= IllegalityInsert || RightInsert >= MaxRightInsert) //非法操作
     {
        qDebug()<<Q_FUNC_INFO<<"操作权限非法";
        return false; //后期优化可以考虑用错误集来代替 方便排错
     }


    //提示信息
    qDebug()<<Q_FUNC_INFO<<"插入操作执行";

    if(RightInsert == rowInsert)//这可以优化一下 难道表会固定5列数据吗 可以写出来更具有变化兼容性的插入
    {
        QString FoodName=InsertInfo.at(0),Status=InsertInfo.at(1),Type = InsertInfo.at(2)
                ,Price = InsertInfo.at(3),Count=InsertInfo.at(4);

        //加密数据
        QString EncryptFoodName = this->HashSecretkey->EncryptCode(FoodName);

        QString EncryptStatus = this->HashSecretkey->EncryptCode(Status);

        QString EncryptType = this->HashSecretkey->EncryptCode(Type);

        QString EncryptPrice = this->HashSecretkey->EncryptCode(Price);

        QString EncryptCreateTime = this->HashSecretkey->EncryptCode(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:MM:ss"));

        QString EncryptCount = this->HashSecretkey->EncryptCode(Count);

        QString SQLdate = "INSERT INTO food(foodname,status,foodtype,price,createtime,count) VALUES"
                          " ('"+EncryptFoodName+"','"+EncryptStatus+"','"+EncryptType+"','"
                               +EncryptPrice+"','"+EncryptCreateTime+"','"+EncryptCount+"');";

        bool ret = this->sqlexe->exec(SQLdate);
        if(!ret)
        {
            qDebug()<<Q_FUNC_INFO<<"插入执行失败";
            qDebug()<<Q_FUNC_INFO<<this->sqlexe->lastError().text();
            printError.printLog("food表行插入执行失败");
            return ret;
        }

        this->sqlexe->clear();

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
            printError.printLog("food表列插入执行失败");
            return ret;
        }

        return ret; //返回执行结果
    }

    return false;
}

bool Food::DeleteData(const int RightDelete, const QStringList DeleteInfo)
{
    if(RightDelete <= IllegalityDelete || RightDelete >=MaxRightDelete)
    {
        qDebug()<<Q_FUNC_INFO<<"删除权限非法";
        return false;
    }

    qDebug()<<Q_FUNC_INFO<<"删除操作执行";

    if(RightDelete == EmptyDelete)//清空所有菜品
    {
        this->sqlexe->prepare("DELETE FROM food;");

        bool ret = this->sqlexe->exec();

        this->sqlexe->clear();

        if(!ret)
        {
            qDebug()<<Q_FUNC_INFO<<"清空执行失败";
            printError.printLog("food表清空删除执行失败");
            return ret;
        }

        return ret;
    }
    else if(RightDelete == rowDelete)//删除指定菜品
    {
        QString ColumnName = DeleteInfo.at(0),deleteValue = DeleteInfo.at(1);

        QString EncryptDeleteValue = this->HashSecretkey->EncryptCode(deleteValue);

        this->sqlexe->prepare("DELETE FROM food WHERE :ColumnName = '"+EncryptDeleteValue+"';");

        this->sqlexe->bindValue(":ColumnName",ColumnName);

        bool ret = this->sqlexe->exec();

        this->sqlexe->clear();

        if(!ret)
        {
            qDebug()<<Q_FUNC_INFO<<"删除执行失败";
            printError.printLog("food表删除行执行失败");
            return ret;
        }

        return ret;
    }

    return false;
}

bool Food::UpdateData(const int RightUpdate, const QStringList UpdateInfo)
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

        this->sqlexe->prepare("UPDATE food SET :AppointName = '"+EncryptAppointValue+"'"
                              " WHERE :Column = '"+EncryptUpdateValue+"'");

        this->sqlexe->bindValue(":AppointName",AppointName);
        this->sqlexe->bindValue(":Column",ColumnName);

        bool ret = this->sqlexe->exec();

        this->sqlexe->clear();

        if(!ret)
        {
            qDebug()<<Q_FUNC_INFO<<"更新执行失败";
            printError.printLog("food用户表更新失败");
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
            printError.printLog("users用户表更新失败");
            return ret;
        }

        return ret;
    }

    return false;
}

QMap<int,QStringList> Food::FindData(const int RightFind, const QStringList FindInfo)
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

        this->sqlexe->prepare("SELECT * FROM food WHERE :Column = '"+EncryptIndexValue+"';");

        this->sqlexe->bindValue(":Column",IndexName);


        bool status = this->sqlexe->exec();

        if(!status)
        {
            qDebug()<<Q_FUNC_INFO<<"查询执行失败";
            printError.printLog("food表查询失败");
            ret.insert(0,QStringList("NULL"));
            return ret;
        }

        QString foodname,Status,count;

        while(this->sqlexe->next())//将查询结果存储 并返回
        {
            QStringList arg;
            foodname = this->HashSecretkey->DecryptCode(this->sqlexe->value(1).toString());
            Status = this->HashSecretkey->DecryptCode(this->sqlexe->value(2).toString());
            count = this->HashSecretkey->DecryptCode(this->sqlexe->value(3).toString());

            arg<<foodname<<Status<<count;

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
        QString foodname,Status,type,birtime,count;
        QStringList arg;//(实际运行可能会有查询内容过多而造成效率问题,后期要考虑分库分表,redis缓存)
        while(this->sqlexe->next())//将查询结果存储 并返回
        {
            foodname = this->HashSecretkey->DecryptCode(this->sqlexe->value(1).toString());
            Status = this->HashSecretkey->DecryptCode(this->sqlexe->value(2).toString());
            type = this->HashSecretkey->DecryptCode(this->sqlexe->value(3).toString());
            birtime = this->HashSecretkey->DecryptCode(this->sqlexe->value(4).toString());
            count = this->HashSecretkey->DecryptCode(this->sqlexe->value(5).toString());

            qDebug()<<Q_FUNC_INFO<<"test";

            arg<<foodname<<Status<<type<<birtime<<count;

            ret.insert(this->sqlexe->value(0).toInt(),arg);

            arg.clear();
        }

        this->sqlexe->clear();

        return ret;
    }

    QStringList arg;
    arg<<"null";
    ret.insert(0,arg);

    return ret;
}
