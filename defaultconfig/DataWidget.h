#ifndef _DATA_WIDGET_H
#define _DATA_WIDGET_H

#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QDate>
#include "core/account.h"

class DataWidget:public QObject{
    Q_OBJECT
    Q_PROPERTY(QList<int> pointValue READ getPointValue WRITE setPointValue NOTIFY pointValueChanged)
    Q_PROPERTY(int Xmax READ getXmax WRITE setXmax NOTIFY XmaxChanged)
    Q_PROPERTY(int Ymax READ getYmax WRITE setYmax NOTIFY YmaxChanged)

public:
    DataWidget(QObject *parent = nullptr);
    ~DataWidget();

    QString DateMapping(int offset);
    int ceilNum(int value);

    Q_INVOKABLE void setChartUpdate(int offset);

    QList<int> getPointValue() const;
    void setPointValue(const QList<int> &value);

    int getXmax() const;
    void setXmax(int value);

    int getYmax() const;
    void setYmax(int value);

signals:
    void XmaxChanged();
    void YmaxChanged();
    void pointValueChanged();

private:
    int Xmax;//x轴取值范围
    int Ymax;//y轴取值范围
    QList<int> pointValue;

    Account * sql;
};

#endif
