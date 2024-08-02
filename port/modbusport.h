#ifndef _MODBUS_PORT_H
#define _MODBUS_PORT_H

#include "mircommunication.h"
#include <QtSerialBus/QModbusDevice>
#include <QtSerialBus/QModbusClient>
#include <QtSerialBus/QModbusDataUnit>
#include <QtSerialBus/QModbusTcpClient>

class ModbusPort : public MirCommunication
{
    Q_OBJECT
public:
    ModbusPort();
    ~ModbusPort();

    bool PortInit() override;

    void setModbusType(int index) override;

    QSerialPortInfo getPort() override;

    QList<QSerialPortInfo> getPortList() override;
    void setPort(int index = 0) override;

    QString getError() override;

    QString readInfo() override;
    void writeInfo(QString data) override;
private:
    bool isUsed;
    QModbusClient * serialClient;
};

#endif
