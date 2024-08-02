#include "modbusport.h"

ModbusPort::ModbusPort()
{
    this->modbs = new QModbusRtuSerialMaster;
    qDebug()<<Q_FUNC_INFO<<"ModbusPort类构造";
}

ModbusPort::~ModbusPort()
{
    delete this->modbs;
    qDebug()<<Q_FUNC_INFO<<"ModbusPort类析构";
}

bool ModbusPort::PortInit()
{
    this->modbs->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,QSerialPort::Baud115200);
    this->modbs->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::Data8);
    this->modbs->setConnectionParameter(QModbusDevice::SerialParityParameter,QSerialPort::NoParity);
    this->modbs->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,QSerialPort::OneStop);
    isUsed = this->modbs->connectDevice();
    return isUsed;
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
