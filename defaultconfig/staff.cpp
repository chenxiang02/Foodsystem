#include "staff.h"

Staff::Staff(QObject *parent)
    :QObject(parent)
{
    this->sql = new User;
    this->flag = -1;
    qDebug()<<Q_FUNC_INFO<<"Staff类构造";
}

Staff::~Staff()
{
    qDebug()<<Q_FUNC_INFO<<"Staff类析构";
}

void Staff::getUsers()
{
    if(flag <1 )
        return; //QStringList("NULL");
    QString SQLstatement;
    if(flag==2)
    {
        SQLstatement = "select * from users where role = '";
        SQLstatement.append(this->sql->getSQLPas()->EncryptCode("1"));
        SQLstatement.append("' or ");
        SQLstatement.append("role = '");
        SQLstatement.append(this->sql->getSQLPas()->EncryptCode("0"));
        SQLstatement.append("';");
    }
    if(flag == 1)
    {
        SQLstatement = "select * from users where role = '";
        SQLstatement.append(this->sql->getSQLPas()->EncryptCode("0"));
        SQLstatement.append("';");
    }
    this->sql->getSqlOperater()->exec(SQLstatement);
    QStringList arg;
    while(this->sql->getSqlOperater()->next())
    {
        arg<<this->sql->getSQLPas()->DecryptCode(this->sql->getSqlOperater()->value(1).toString());
        arg<<this->sql->getSQLPas()->DecryptCode(this->sql->getSqlOperater()->value(2).toString());
        arg<<this->sql->getSQLPas()->DecryptCode(this->sql->getSqlOperater()->value(3).toString());
    }
    setUser(arg);
    this->sql->getSqlOperater()->clear();
}

void Staff::setPassWord(QStringList arg)
{
    QString updateString = "UPDATE users SET password ='";
    updateString.append(this->sql->getSQLPas()->EncryptCode(arg.at(1)));
    updateString.append("' WHERE username = '");
    updateString.append(this->sql->getSQLPas()->EncryptCode(arg.at(0)));
    updateString.append("';");
    this->sql->getSqlOperater()->exec(updateString);
    this->sql->getSqlOperater()->clear();
    getUsers();
}

void Staff::deleteUser(QString data)
{
    QString deleteStr = "DELETE FROM users WHERE username = '";
    deleteStr.append(this->sql->getSQLPas()->EncryptCode(data));
    deleteStr.append("';");
    this->sql->getSqlOperater()->exec(deleteStr);
    this->sql->getSqlOperater()->clear();
    getUsers();
}

void Staff::addUser(QStringList data)
{
    if(this->flag == 1)
    {
        QString insertStatement = "insert into users(username,password,role) values ('";
        insertStatement.append(this->sql->getSQLPas()->EncryptCode(data.at(0)));
        insertStatement.append("','");
        insertStatement.append(this->sql->getSQLPas()->EncryptCode(data.at(1)));
        insertStatement.append("','");
        insertStatement.append(this->sql->getSQLPas()->EncryptCode("0"));
        insertStatement.append("');");
        this->sql->getSqlOperater()->exec(insertStatement);
    }
    else if(this->flag == 2)
    {
        QString insertStatement = "insert into users(username,password,role) values('";
        insertStatement.append(this->sql->getSQLPas()->EncryptCode(data.at(0)));
        insertStatement.append("','");
        insertStatement.append(this->sql->getSQLPas()->EncryptCode(data.at(1)));
        insertStatement.append("','");
        insertStatement.append(this->sql->getSQLPas()->EncryptCode(data.at(2)));
        insertStatement.append("');");
        this->sql->getSqlOperater()->exec(insertStatement);
    }
    getUsers();
}

int Staff::getFlag() const
{
    return flag;
}

void Staff::setFlag(int value)
{
    this->flag = value;
    emit flagChanged();
}

QStringList Staff::getUser()
{
    return user;
}

void Staff::setUser(const QStringList &value)
{
    user = value;
    emit userChanged();
}

QString Staff::getAccountText() const
{
    return accountText;
}

void Staff::setAccountText(const QString &value)
{
    accountText = value;
    emit accountChanged();
}
