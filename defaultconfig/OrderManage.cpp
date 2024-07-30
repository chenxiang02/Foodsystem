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

OrderManage::OrderManage(QObject *parent)
    : QObject(parent)
{
    this->sql = new Account;
    this->isCurrent = false;
    getHistotyAccount();
    qDebug()<<Q_FUNC_INFO<<"OrderManage类构造";
}

OrderManage::~OrderManage()
{
    qDebug()<<Q_FUNC_INFO<<"OrderManage类析构";
}

QStringList OrderManage::getMenu() const
{
    if(this->isCurrent)
        return WorkConfig::menuList;
    else
        return menu;
}

void OrderManage::setMenu(const QStringList value)
{
    if(this->isCurrent)
        menu = WorkConfig::menuList;
    else
        menu = value;
    emit menuChanged();
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
