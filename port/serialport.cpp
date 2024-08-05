#include "serialport.h"

SerialPort::SerialPort(QObject *parent)
{
     this->serialport = new QSerialPort;//绑定对象树 自动回收

     this->isUsed = false;

     this->baudrate = QSerialPort::Baud115200;
     qDebug()<<Q_FUNC_INFO<<"SerialPort类构造";
}

SerialPort::~SerialPort()
{
    this->serialport->close();
    delete this->serialport;
    qDebug()<<Q_FUNC_INFO<<"SerialPort类析构";
}

QList<QSerialPortInfo> SerialPort::getPortList()
{
    QList<QSerialPortInfo> PortList = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo&info, PortList) {
       qDebug()<<"可用串口:"<<info.portName();
    }
}

QSerialPortInfo SerialPort::getPort()
{
    return port;
}

void SerialPort::setPort(int index)
{
    this->port = getPortList().at(index);
}

bool SerialPort::PortInit()
{
    bool isSuccess = true;//通过与操作 只要有false 则代表此次执行不成功

    if(this->isUsed)
        this->serialport->close();//断开上一个连接

    this->serialport->setPort(getPort());

    isSuccess &= this->serialport->setBaudRate(getBaudrate());

    isSuccess &= this->serialport->setDataBits(QSerialPort::Data8);


    isSuccess &= this->serialport->setParity(QSerialPort::NoParity);

    isSuccess &= this->serialport->setStopBits(QSerialPort::OneStop);

    isSuccess &= this->serialport->setFlowControl(QSerialPort::HardwareControl);

    isSuccess &= this->serialport->open(QIODevice::ReadWrite);

    this->isUsed = isSuccess;//判断是否初始化成功

    connect(serialport,&QSerialPort::readyRead,this,&SerialPort::handlerMessage);

    return isSuccess;
}

QString SerialPort::getError()
{
    QString curretError = this->errorInfo;

    this->errorInfo.clear();//防止错误累积

    return curretError;
}

QString SerialPort::readInfo()
{
    if(!this->isUsed)
    {
        qDebug()<<"警告: 当前串口未完成初始化无法进行读取";
        return "";
    }

    QByteArray data = this->serialport->readAll();

    QString receiveData = QString::fromUtf8(data);//防止中文乱码

    return receiveData;
}

void SerialPort::writeInfo(QString data)
{
    if(!this->isUsed)
    {
        qDebug()<<"警告: 当前串口未完成初始化无法进行读取";
        return;
    }
    QByteArray midData = data.toUtf8();//防止直接转换造成错误

    char * writeData = midData.data();

    this->serialport->write(writeData,sizeof(writeData));
}

QString SerialPort::errorToString(QSerialPort::SerialPortError error)
{
    switch (error) {
        case QSerialPort::NoError:
            return  "没有错误";
        case QSerialPort::DeviceNotFoundError:
            return  "找不到设备";
        case QSerialPort::PermissionError:
            return  "没有足够的权限";
        case QSerialPort::OpenError:
            return  "打开设备时出错";
        case QSerialPort::ParityError:
            return  "奇偶校验错误";
        case QSerialPort::FramingError:
            return  "帧错误";
        case QSerialPort::BreakConditionError:
            return  "断线条件错误";
        case QSerialPort::WriteError:
            return  "写数据时出错";
        case QSerialPort::ReadError:
            return  "读数据时出错";
        case QSerialPort::ResourceError:
            return  "设备被意外移除或系统资源不足";
        case QSerialPort::UnsupportedOperationError:
            return  "不支持的操作";
        case QSerialPort::UnknownError:
            return  "未知错误";
        case QSerialPort::TimeoutError:
            return  "操作超时";
        case QSerialPort::NotOpenError:
            return  "尝试操作一个未打开的设备";
    }
}

int SerialPort::getBaudrate() const
{
    return baudrate;
}

void SerialPort::setBaudrate(int value)
{
    baudrate = value;
}

void SerialPort::ErrorPrompt(QSerialPort::SerialPortError error)
{
    this->errorInfo = errorToString(error);
    qDebug()<<Q_FUNC_INFO<<errorToString(error);
}

void SerialPort::handlerMessage()
{
    if(this->readInfo().contains(QString::number(MessType::moveError)))
        emit moveDevice();
}



