#ifndef _MIR_COMMUNCATION_H
#define _MIR_COMMUNCATION_H

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "QObject"

class MirCommunication : public QObject
{
public:
    MirCommunication();
    virtual ~MirCommunication();

    virtual bool PortInit() = 0;//初始化连接

    virtual void setModbusType(int index);//设置modbus通信 0:rtu,1:tcp

    virtual QList<QSerialPortInfo> getPortList() = 0;//获取当前连接设备列表
    virtual QSerialPortInfo getPort() = 0;//获取当前连接设备
    virtual void setPort(int index = 0) = 0;//设置当前连接设备
    virtual QString getError() = 0;//获取错误码
    virtual QString readInfo() = 0;//读操作
    virtual void writeInfo(QString data) = 0;//写操作
};


#endif
