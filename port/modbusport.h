#ifndef _MODBUS_PORT_H
#define _MODBUS_PORT_H

#include "mircommunication.h"
#include <QtSerialBus>
#include <QModbusRtuSerialMaster>
#include <QModbusRequest>
#include <QModbusResponse>

class ModbusPort : public MirCommunication
{
    Q_OBJECT
public:
    ModbusPort();
    ~ModbusPort();

    bool PortInit() override;

    QSerialPortInfo getPort() override;

    QList<QSerialPortInfo> getPortList() override;
    void setPort(int index = 0) override;

    QString getError() override;

    QString readInfo() override;
    void writeInfo(QString data) override;

public slots:

private:
    bool isUsed;
    QModbusRtuSerialMaster * modbs;
};

#endif
