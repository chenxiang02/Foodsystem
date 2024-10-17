#include "rightconfig.h"

RightConfig::RightConfig()
{
    this->flag = -1;
    this->rightSet = new QSettings("Right.ini",QSettings::IniFormat);

    QStringList arg;

    if(!this->rightSet->contains("0"))
    {
        arg<<"工作台"<<"数据统计"<<"订单管理";
        this->rightSet->setValue("0",arg);
    }
    if(!this->rightSet->contains("1"))
    {
        arg<<"菜品管理"<<"员工管理";
        this->rightSet->setValue("1",arg);
    }
    if(!this->rightSet->contains("2"))
    {
        arg<<"分类管理";
        this->rightSet->setValue("2",arg);
    }

    qDebug()<<Q_FUNC_INFO<<"right配置类构造";
}

RightConfig::~RightConfig()
{
   delete this->rightSet;

   qDebug()<<Q_FUNC_INFO<<"right配置类析构";
}

int RightConfig::getFlag() const
{
    return this->flag;
}

void RightConfig::setFlag(int value)
{
    this->flag = value;
    if(value>=0)
        emit btnNamesChanged();
    emit flagChanged();
}

QStringList RightConfig::getBtnNames() const
{
    QString right;
    right.append(QString::number(getFlag()));
    right.append("/");
    QStringList arg = this->rightSet->value(right,"NULL").toStringList();
    return arg;
}

void RightConfig::setBtnNames(const QStringList &value)
{
    if(value == this->btnNames)
        return;
    this->btnNames = value;
    emit btnNamesChanged();
}
