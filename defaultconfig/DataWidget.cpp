#include "DataWidget.h"

DataWidget::DataWidget(QObject *parent) :QObject(parent)
{
    this->sql = new Account;
    setChartUpdate(3);
    qDebug()<<Q_FUNC_INFO<<"DataWidget类构造";
}

DataWidget::~DataWidget()
{
    qDebug()<<Q_FUNC_INFO<<"DataWidget类析构";
}

QString DataWidget::DateMapping(int offset)
{
    QDate currentDate = QDate::currentDate();
    QDate futureDate = currentDate.addDays(offset);
    return futureDate.toString("yyyy-MM-dd");
}

int DataWidget::ceilNum(int value)
{
    int i = 10;

    while (i < value && i*10 < value)//获取alue最高位(例如获取千位万位等)
       i*=10;

//以1.4倍指数增长
//如(假设传进9999 只需要六次就能取得它更高的整数 指数选择越高循环查找次数越少)
    while (i < value)
        i*=1.4;

    qDebug()<<"返回值"<<i;
    return i;
}

void DataWidget::setChartUpdate(int offset)
{
    QList<int> pointReceive;
    int sellValue = 0;
    int MaxValue = 0;
    QString selectDate;
    for(int i = 0;i < offset; i++)
    {
        selectDate = "select * from account where selltime like '"+DateMapping(-i)+"%';";
        this->sql->getSqlOperater()->exec(selectDate);
        while(this->sql->getSqlOperater()->next())
        {
            sellValue+=this->sql->getPasOperater()->DecryptCode(this->sql->getSqlOperater()->value(4).toString()).toInt();
        }
        pointReceive.push_back(sellValue);
        MaxValue = MaxValue > sellValue ? MaxValue : sellValue;
        sellValue = 0;
    }
    setXmax(pointReceive.size());
    setYmax(ceilNum(MaxValue));
    setPointValue(pointReceive);
    qDebug()<<MaxValue;
}

QList<int> DataWidget::getPointValue() const
{
    return pointValue;
}

void DataWidget::setPointValue(const QList<int> &value)
{
    pointValue = value;
    emit pointValueChanged();
}

int DataWidget::getXmax() const
{
    return Xmax;
}

void DataWidget::setXmax(int value)
{
    Xmax = value;
    emit XmaxChanged();
}

int DataWidget::getYmax() const
{
    return Ymax;
}

void DataWidget::setYmax(int value)
{
    Ymax = value;
    emit YmaxChanged();
}
