#ifndef _WORK_CONFIG_H
#define _WORK_CONFIG_H

#include <QDebug>
#include <QSettings>
#include <QObject>
#include <QDateTime>
#include "sourcepool/sourceQueue.h"
#include <QTimer>


class WorkConfig:public QObject
{
    Q_OBJECT

    //work界面第一排动态数据
    Q_PROPERTY(QString NowDate READ getNowDate WRITE setNowDate NOTIFY nowDateChanged)
    Q_PROPERTY(QString TurnOver READ getTurnOver WRITE setTurnOver NOTIFY turnOverChanged)
    Q_PROPERTY(QString OrderCount READ getOrderCount WRITE setOrderCount NOTIFY orderCountChanged)
    Q_PROPERTY(QString AveragePrice READ getAveragePrice WRITE setAveragePrice NOTIFY averagePriceChanged)
    Q_PROPERTY(QString OrderComplete READ getOrderComplete WRITE setOrderComplete NOTIFY orderCompleteChanged)

    //work界面第二排动态数据
    Q_PROPERTY(QString ToBeComplete READ getToBeComplete WRITE setToBeComplete NOTIFY toBeCompleteChanged)
    Q_PROPERTY(QString FinishOrder READ getFinishOrder WRITE setFinishOrder NOTIFY finishOrderChanged)
    Q_PROPERTY(QString OrderCancel READ getOrderCancel WRITE setOrderCancel NOTIFY orderCancelChanged)
    Q_PROPERTY(QString AllOrder READ getAllOrder WRITE setAllOrder NOTIFY allOrderChanged)


public:
    WorkConfig(QObject * parent = nullptr);
    ~WorkConfig();

    //时间比对函数
    QString getNowDate() const;
    void setNowDate(const QString &value);

    //额度获取函数
    QString getTurnOver() const;
    void setTurnOver(QString value);

    //订单数
    QString getOrderCount() const;
    void setOrderCount(const QString &value);

    //平均价
    QString getAveragePrice() const;
    void setAveragePrice(const QString &value);

    QString getOrderComplete() const;
    void setOrderComplete(const QString &value);

    QString getToBeComplete() const;
    void setToBeComplete(const QString &value);

    QString getFinishOrder() const;
    void setFinishOrder(const QString &value);

    QString getOrderCancel() const;
    void setOrderCancel(const QString &value);

    QString getAllOrder() const;
    void setAllOrder(const QString &value);

signals:
    void nowDateChanged();

    void turnOverChanged();
    void orderCountChanged();
    void averagePriceChanged();
    void orderCompleteChanged();

    void toBeCompleteChanged();
    void finishOrderChanged();
    void orderCancelChanged();
    void allOrderChanged();

public:
    void handlerLoacl(QString data);

private:
    QString NowDate;

    QString TurnOver;
    QString OrderCount;
    QString OrderComplete;
    QString AveragePrice;

    QString ToBeComplete;
    QString FinishOrder;
    QString OrderCancel;
    QString AllOrder;

    QSettings * workConfig;
    SourceQueue * queue;
    QTimer *time;
};

#endif
