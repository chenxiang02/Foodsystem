#include "rightconfig.h"

RightConfig::RightConfig()
{
    this->flag = -1;
    this->rightSet = new QSettings("Right.ini",QSettings::IniFormat);

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
    emit flagChanged();
}

QStringList RightConfig::getBtnNames() const
{
    QString right;
    right.append(QString::number(2));
    right.append("/");
    return this->rightSet->value(right,"NULL").toStringList();
}

void RightConfig::setBtnNames(const QStringList &value)
{
    if(value == this->btnNames)
        return;
    this->btnNames = value;
    emit btnNamesChanged();
}
