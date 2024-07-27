#include "workconfig.h"


namespace WorkPack{
    QStringList handlerMenuList(QString Data)
    {
        int length = Data.length();
        QStringList arg;
        QString strMid;

        for(int i = 0;i < length;i++)
        {
            if(Data.at(i)=='|' || Data.at(i) == '+' || Data.at(i) == '/')
            {
                arg<<strMid;
                strMid.clear();
                continue;
            }
            strMid.append(Data.at(i));
        }
        qDebug()<<arg;
        return arg;
    }
};

WorkConfig::WorkConfig(QObject * parent):QObject(parent)
{
    this->workConfig = new QSettings("Work.ini",QSettings::IniFormat);

    this->queue = new SourceQueue;

    this->time = new QTimer(this);//绑定对象树

    this->time->setInterval(1000);

    this->time->start();//开启定时器

    connect(time,&QTimer::timeout,this,&WorkConfig::handlerData);

    qDebug()<<Q_FUNC_INFO<<"WorkConfig类构造";
}

WorkConfig::~WorkConfig()
{
    qDebug()<<Q_FUNC_INFO<<"WorkConfig类析构";
}

QString WorkConfig::getNowDate() const
{
    return this->workConfig->
    value("Date/",QDateTime::currentDateTime().toString("yyyy-MM-dd"))
    .toString();//返回配置文件当前时间信息 如果为空则默认为当前时间
}

void WorkConfig::setNowDate(const QString &value)
{
    if(value == NowDate)
        return;

    NowDate = value;

    this->workConfig->setValue("Date/",NowDate);//更新为当前时间
    emit nowDateChanged();
}

QString WorkConfig::getTurnOver() const
{
    if(TurnOver.isEmpty())
        return "0";
    return TurnOver;
}

void WorkConfig::setTurnOver(QString value)
{
    TurnOver = value;
    emit turnOverChanged();
}

QString WorkConfig::getOrderCount() const
{
    if(OrderCount.isEmpty())
        return "0";
    return OrderCount;
}

void WorkConfig::setOrderCount(const QString &value)
{
    OrderCount = value;
    emit orderCountChanged();
}

QString WorkConfig::getAveragePrice() const
{
    if(AveragePrice.isEmpty())
        return "0";
    return AveragePrice;
}

void WorkConfig::setAveragePrice(const QString &value)
{
    AveragePrice = value;
    emit averagePriceChanged();
}

QString WorkConfig::getOrderComplete() const
{
    if(OrderComplete.isEmpty())
        return "0";
    return OrderComplete;
}

void WorkConfig::setOrderComplete(const QString &value)
{
    OrderComplete = value;
    emit orderCompleteChanged();
}

QString WorkConfig::getToBeComplete() const
{
    if(ToBeComplete.isEmpty())
        return "0";
    return ToBeComplete;
}

void WorkConfig::setToBeComplete(const QString &value)
{
    ToBeComplete = value;
    emit toBeCompleteChanged();
}

QString WorkConfig::getFinishOrder() const
{
    if(FinishOrder.isEmpty())
        return "0";
    return FinishOrder;
}

void WorkConfig::setFinishOrder(const QString &value)
{
    FinishOrder = value;
    emit finishOrderChanged();
}

QString WorkConfig::getOrderCancel() const
{
    if(OrderCancel.isEmpty())
        return "0";
    return OrderCancel;
}

void WorkConfig::setOrderCancel(const QString &value)
{
    OrderCancel = value;
    emit orderCancelChanged();
}

QString WorkConfig::getAllOrder() const
{
    if(AllOrder.isEmpty())
        return "0";
    return AllOrder;
}

void WorkConfig::setAllOrder(const QString &value)
{
    AllOrder = value;
    emit allOrderChanged();
}

void WorkConfig::handlerData()
{
    QString Data;
    if(SourceQueue::getCount() >0)//有数据才允许去读
        Data = this->queue->receiveMsg();
    else
    {
        qDebug()<<"没有数据";
        return;
    }
    QStringList menuList = WorkPack::handlerMenuList(Data);

    int turnover = getTurnOver().toInt() + QString(menuList.at(menuList.size() - 1)).toInt();
    setTurnOver(QString::number(turnover));

    int order = getOrderCount().toInt() + 1;
    setOrderCount(QString::number(order));
}

