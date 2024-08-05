#include "port.h"

Port::Port(QObject *parent)
    : QObject(parent)
{
    this->port = new SerialPort(this);

    this->camera = new QCamera(this);
    this->image = new QCameraImageCapture(this->camera);

    this->camera->setCaptureMode(QCamera::CaptureStillImage);//图片捕获

    int length = this->port->getPortList().length();

    for(int i = 0;i < length;i++)//如果串口给了回复 则是我们需要的设备 类似单片机中从机应答
    {
        this->port->setPort(i);
        this->port->PortInit();
        this->port->writeInfo("10101010");
        if(this->port->readInfo().contains("01010101"))
            break;
    }

    this->camera->start();//开启摄像头

    connect(this->port,&SerialPort::moveDevice,this,[&]{
        this->image->capture();//收到移动信号就进行拍照记录
    });

    qDebug()<<Q_FUNC_INFO<<"port类构造";
}

Port::~Port()
{
    qDebug()<<Q_FUNC_INFO<<"port类构造";
}
