#include "modbusport.h"

ModbusPort::ModbusPort()
{
    qDebug()<<Q_FUNC_INFO<<"ModbusPort类构造";
}

ModbusPort::~ModbusPort()
{
    qDebug()<<Q_FUNC_INFO<<"ModbusPort类析构";
}

bool ModbusPort::PortInit()
{

}

void ModbusPort::setModbusType(int index)
{
    if(index < 0 || index > 1 )
    {
        qDebug()<<"请按照正确规范传入参数 0:代表rtu通信 1:代表tcp通信";
        return;
    }
}

QSerialPortInfo ModbusPort::getPort()
{

}

QList<QSerialPortInfo> ModbusPort::getPortList()
{

}

void ModbusPort::setPort(int index)
{

}

QString ModbusPort::getError()
{

}

QString ModbusPort::readInfo()
{

}

void ModbusPort::writeInfo(QString data)
{

}
