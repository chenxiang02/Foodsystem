#include "TypeMenu.h"

QString TypeMap(int type)
{
    switch (type)
    {
        case 0:
        return "汤类";
        case 1:
        return "肉类";
        case 2:
        return "蔬菜";
    }

}


TypeMenu::TypeMenu(QObject *parent)
    : QObject(parent)
{
    this->sql = new Food;
    qDebug()<<Q_FUNC_INFO<<"TypeMenu类构造成功";
}

TypeMenu::~TypeMenu()
{
    qDebug()<<Q_FUNC_INFO<<"TypeMenu类析构成功";
}

void TypeMenu::getFoods()
{
    QString selectStatement = "select foodname,foodtype,price from food;";
    this->sql->getSqlOperater()->exec(selectStatement);

    QStringList arg;
    QStringList type;

    while (this->sql->getSqlOperater()->next())
    {
        arg<<this->sql->getPasOperater()->DecryptCode(this->sql->getSqlOperater()->value(0).toString());
        arg<<TypeMap(this->sql->getPasOperater()->DecryptCode(this->sql->getSqlOperater()->value(1).toString()).toInt());
        if(!type.contains(TypeMap(this->sql->getPasOperater()->DecryptCode(this->sql->getSqlOperater()->value(1).toString()).toInt())))
            type<<TypeMap(this->sql->getPasOperater()->DecryptCode(this->sql->getSqlOperater()->value(1).toString()).toInt());
        arg<<this->sql->getPasOperater()->DecryptCode(this->sql->getSqlOperater()->value(2).toString());
    }

    setFood(arg);
    setTypeList(type);
}

void TypeMenu::findFood(QString data)
{
    QStringList arg = getFood();

    if(this->oldFood.isEmpty())//避免过度拷贝浪费时间
        this->oldFood =arg;

    QStringList findData;
    QStringList setList;
    int length = arg.length();

    for(int i = 0;i < length;i+=3)
    {
         if(arg.at(i).contains(data))
         {
             findData<<arg.at(i);
         }
    }

    length = findData.length();
    int localIndex;
    for(int i = 0;i < length;i++)
    {
        localIndex = arg.indexOf(findData.at(i));
        setList<<arg.at(localIndex);
        setList<<arg.at(localIndex+1);
        setList<<arg.at(localIndex+2);
    }
    setFood(setList);
}

void TypeMenu::showAll()
{
    if(this->oldFood.isEmpty())//避免从磁盘读取数据浪费时间
    {
        getFoods();
        return;
    }
    else
    {
        setFood(this->oldFood);
    }
}

void TypeMenu::addFood(QStringList data)
{
    QString createtime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:MM:ss");

    QString insertStatement = "INSERT INTO food(foodname,status,foodtype,price,createtime,count) VALUES ('";
    insertStatement.append(this->sql->getPasOperater()->EncryptCode(data.at(0)));
    insertStatement.append("','");
    insertStatement.append(this->sql->getPasOperater()->EncryptCode("0"));
    insertStatement.append("','");
    insertStatement.append(this->sql->getPasOperater()->EncryptCode(QString::number(decyTypeMap(data.at(1)))));
    insertStatement.append("','");
    insertStatement.append(this->sql->getPasOperater()->EncryptCode(data.at(2)));
    insertStatement.append("','");
    insertStatement.append(this->sql->getPasOperater()->EncryptCode(createtime));
    insertStatement.append("','");
    insertStatement.append(this->sql->getPasOperater()->EncryptCode("99"));
    insertStatement.append("');");

    this->sql->getSqlOperater()->exec(insertStatement);
    if(this->oldFood.isEmpty())
    {
        this->food<<data.at(0)<<data.at(1)<<data.at(2);
        emit foodChanged();
    }
    else
    {
        this->oldFood<<data.at(0)<<data.at(1)<<data.at(2);
        setFood(oldFood);
    }
}

void TypeMenu::deleteFood(QString data)
{
    QString deleteStatement = "delete from food where foodname = '";
    deleteStatement.append(this->sql->getPasOperater()->EncryptCode(data));
    deleteStatement.append("';");
    this->sql->getSqlOperater()->exec(deleteStatement);
    getFoods();
}

void TypeMenu::modifyFood(QStringList data)
{

}

int TypeMenu::decyTypeMap(QString data)
{
    return this->TypeList.indexOf(data);
}

QStringList TypeMenu::getFood() const
{
    return food;
}

void TypeMenu::setFood(const QStringList &value)
{
    food = value;
    emit foodChanged();
}

QStringList TypeMenu::getTypeList() const
{
    return TypeList;
}

void TypeMenu::setTypeList(const QStringList &value)
{
    TypeList = value;
    emit typeListChanged();
}
