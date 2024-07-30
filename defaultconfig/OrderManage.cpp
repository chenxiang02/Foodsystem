#include "OrderManage.h"


QStringList Unpack(QString data)
{
    int length = data.length();
    QStringList RetData;
    QString Data;
    for(int i = 0;i < length;i++)
    {

        if(data.at(i)=='|' || data.at(i) == "/")
        {
            RetData<<Data;
            Data.clear();
            continue;
        }
        Data+=data.at(i);
    }
    RetData<<Data;
    return RetData;
}

QStringList UpdateFind(int flag,QStringList arg,QStringList hash)
{
   int length = arg.size();
   QStringList ret;
   if(flag == 0)
   {
        int currentIndex;
        for(int i = 0;i < length;i++)
        {
            currentIndex = hash.indexOf(arg.at(i));
            ret<<hash.at(currentIndex)<<hash.at(currentIndex+1)<<hash.at(currentIndex+2)<<hash.at(currentIndex+3);
        }
   }
   else if(flag == 1)
   {
       int currentIndex;
       for(int i = 0;i < length;i++)
       {
           currentIndex = hash.indexOf(arg.at(i));
           ret<<hash.at(currentIndex - 1)<<hash.at(currentIndex)<<hash.at(currentIndex+1)<<hash.at(currentIndex+2);
       }
   }
   else if(flag == 2)
   {
       int currentIndex;
       for(int i = 0;i < length;i++)
       {
           currentIndex = hash.indexOf(arg.at(i));
           ret<<hash.at(currentIndex - 2)<<hash.at(currentIndex - 1)<<hash.at(currentIndex)<<hash.at(currentIndex+1);
       }
   }
   else if(flag == 3)
   {
       int currentIndex;
       for(int i = 0;i < length;i++)
       {
           currentIndex = hash.indexOf(arg.at(i));
           ret<<hash.at(currentIndex - 3)<<hash.at(currentIndex -2)<<hash.at(currentIndex - 1)<<hash.at(currentIndex);
       }
   }
   return ret;
}

OrderManage::OrderManage(QObject *parent)
    : QObject(parent)
{
    this->sql = new Account;
    this->isCurrent = false;
    this->isFind =false;
    getHistotyAccount();
    qDebug()<<Q_FUNC_INFO<<"OrderManage类构造";
}

OrderManage::~OrderManage()
{
    qDebug()<<Q_FUNC_INFO<<"OrderManage类析构";
}



void OrderManage::setMenu(const QStringList value)
{
    if(this->isCurrent)
        menu = WorkConfig::menuList;
    else
        menu = value;
    emit menuChanged();
}

QStringList OrderManage::getMenu()
{
    if(isFind)
    {
        isFind = false;
        setMenu(oldMenu);
        oldMenu.clear();
    }
    if(this->isCurrent)
        return WorkConfig::menuList;
    else
        return menu;
}

void OrderManage::getHistotyAccount()
{
    QString selectStatement = "select * from account;";
    this->sql->getSqlOperater()->exec(selectStatement);
    QStringList storeList;
    QString SellTime,OrderNum,TotalValue,menu;


    while(this->sql->getSqlOperater()->next())
    {
        SellTime = this->sql->getSqlOperater()->value(3).toString();

        QDateTime Date = QDateTime::fromString(SellTime,"yyyy-MM-dd HH:mm:ss");
        OrderNum = OrderNum.setNum(Date.toTime_t());

        menu =this->sql->getPasOperater()->DecryptCode(this->sql->getSqlOperater()->value(1).toString());

        TotalValue = this->sql->getPasOperater()->DecryptCode(this->sql->getSqlOperater()->value(4).toString());

        storeList<<OrderNum<<SellTime<<menu<<TotalValue;

        OrderNum.clear();
    }
    setMenu(storeList);
}

void OrderManage::getCurrentAccount()
{
    emit menuChanged();
}

void OrderManage::getInformation(QString data)
{
    setShowMenu(Unpack(data));
}

void OrderManage::cancelEvent(QString data,QString value)
{
    QString encodeValue = this->sql->getPasOperater()->EncryptCode(value);
    qDebug()<<this->sql->getSqlOperater()->exec("delete from account where selltime = '"+data+"' and totalvalue = '"+encodeValue+"';");
    int localIndex = WorkConfig::menuList.indexOf(data);
    QString delOne = WorkConfig::menuList.at(localIndex - 1);
    QString delTwo = WorkConfig::menuList.at(localIndex + 1);
    QString delThere = WorkConfig::menuList.at(localIndex + 2);

    WorkConfig::menuList.removeAt(localIndex);
    WorkConfig::menuList.removeAt(WorkConfig::menuList.indexOf(delOne));
    WorkConfig::menuList.removeAt(WorkConfig::menuList.indexOf(delTwo));
    WorkConfig::menuList.removeAt(WorkConfig::menuList.indexOf(delThere));
    emit menuChanged();
}

void OrderManage::confirmMenu(QString data)
{
    int localIndex = WorkConfig::menuList.indexOf(data);
    QString delOne = WorkConfig::menuList.at(localIndex - 1);
    QString delTwo = WorkConfig::menuList.at(localIndex + 1);
    QString delThere = WorkConfig::menuList.at(localIndex + 2);

    WorkConfig::menuList.removeAt(localIndex);
    WorkConfig::menuList.removeAt(WorkConfig::menuList.indexOf(delOne));
    WorkConfig::menuList.removeAt(WorkConfig::menuList.indexOf(delTwo));
    WorkConfig::menuList.removeAt(WorkConfig::menuList.indexOf(delThere));
    emit menuChanged();
}

void OrderManage::findNode(QString data)
{
     oldMenu = getMenu();
     QString findData;
     QStringList arg;
     QStringList updateArg;

     int length = oldMenu.size();
     for(int i = 0;i < length;i++)
     {
        findData = oldMenu.at(i);
        if(findData.contains(data))
         {
            qDebug()<<findData;
            arg<<findData;
         }
     }
     length = arg.size();
     if(length == 0)//如果没有找到指定值
     {
        setMenu(arg);
        return;
     }
     int flag = oldMenu.indexOf(arg.at(0)) % 4;
     qDebug()<<"----:"<<flag;
     setMenu(UpdateFind(flag,arg,oldMenu));
     isFind = true;
}

bool OrderManage::getIsCurrent() const
{
    return isCurrent;
}

void OrderManage::setIsCurrent(bool value)
{
    isCurrent = value;
    emit isCurrentChanged();
}

QStringList OrderManage::getShowMenu() const
{
    return showMenu;
}

void OrderManage::setShowMenu(const QStringList &value)
{
    showMenu = value;
    emit showMenuChanged();
}
