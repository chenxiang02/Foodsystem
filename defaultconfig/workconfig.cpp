#include "workconfig.h"

QStringList WorkConfig::menuList;//全局共享数据

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
        return arg;
    }
};

WorkConfig::WorkConfig(QObject * parent):QObject(parent)
{
    this->workConfig = new QSettings("Work.ini",QSettings::IniFormat);

    this->queue = new SourceQueue;

    this->sql = new Context;

    this->sql->setMethod("Food");

    CodeHandler a;

    this->sql->applySqlOperator()->exec("select count(*) from food where status = '"+a.EncryptCode("0")+"';");

    this->sql->applySqlOperator()->next();

    setStartSell(this->sql->applySqlOperator()->value(0).toString());

    this->sql->applySqlOperator()->clear();

    this->sql->applySqlOperator()->exec("select count(*) from food where status = '"+a.EncryptCode("1")+"';");

    this->sql->applySqlOperator()->next();

    setStopSell(this->sql->applySqlOperator()->value(0).toString());

    this->sql->setMethod("Account");

    this->time = new QTimer(this);//绑定对象树

    this->time->setInterval(500);

    this->time->start();//开启定时器

    this->mutex = new QMutex;

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
    mutex->lock();
    QString Data;
    if(SourceQueue::getCount() >0)//有数据才允许去读
        Data = this->queue->receiveMsg();
    else{
        mutex->unlock();//如果没有数据 立马解锁
        return;
    }
    QStringList menuList = WorkPack::handlerMenuList(Data);

    int turnover = getTurnOver().toInt() + QString(menuList.at(menuList.size() - 1)).toInt();
    setTurnOver(QString::number(turnover));

    int order = getOrderCount().toInt() + 1;
    setOrderCount(QString::number(order));

    int tocomplete = getToBeComplete().toInt() + 1;
    setToBeComplete(QString::number(tocomplete));

    int all = getAllOrder().toInt() + 1;
    setAllOrder(QString::number(all));

    double completeRate = (getAllOrder().toDouble() - getOrderCancel().toDouble()) / getAllOrder().toDouble() ;
    setOrderComplete(QString::number(completeRate * 100));

    double averageValue = getTurnOver().toDouble() / getAllOrder().toDouble();
    setAveragePrice(QString::number(averageValue));

    QStringList arg;
    QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    int removeLength = Data.lastIndexOf("/");
    Data.remove(removeLength,Data.length() - removeLength);
    arg<<Data<<"0"<<menuList.at(menuList.size()-1)<<date;
    QStringList menu;

    QDateTime receDate = QDateTime::fromString(date,"yyyy-MM-dd hh:mm:ss");
    QString timeDate;
    timeDate = timeDate.setNum(receDate.toTime_t());

    menu<<timeDate<<date<<Data<<menuList.at(menuList.size()-1);
    WorkConfig::menuList<<menu;
    sql->applyInsert(1,arg);
    mutex->unlock();
}

QString WorkConfig::getStartSell() const
{
    return startSell;
}

void WorkConfig::setStartSell(const QString &value)
{
    startSell = value;
    emit startSellChanged();
}

QString WorkConfig::getStopSell() const
{
    return stopSell;
}

void WorkConfig::setStopSell(const QString &value)
{
    stopSell = value;
    emit stopSellChanged();
}
