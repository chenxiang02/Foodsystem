#ifndef _SERIAL_PORT_H
#define _SERIAL_PORT_H

#include "mircommunication.h"


class SerialPort : public MirCommunication
{
    Q_OBJECT
public:

    enum MessType{
        moveError = 10001010,
    };

    Q_ENUM(MessType)

    SerialPort(QObject * parent = nullptr);
    ~SerialPort();

    bool PortInit() override;//串口初始化

    QList<QSerialPortInfo> getPortList() override;

    QSerialPortInfo getPort() override;
    void setPort(int index = 0) override;

    QString getError() override;//获取当前错误信息

    QString readInfo() override;//读取信息

    void writeInfo(QString data) override;//写入信息

    QString errorToString(QSerialPort::SerialPortError error);

    int getBaudrate() const;
    void setBaudrate(int value);
signals:
    void Success();
    void moveDevice();

public slots:
    void ErrorPrompt(QSerialPort::SerialPortError error);
    void handlerMessage();

private:
    QSerialPort * serialport;
    QString errorInfo;
    QSerialPortInfo port;

    bool isUsed;

    int baudrate;
};

#endif
