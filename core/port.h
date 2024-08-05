#ifndef _PORT_H
#define _PORT_H

#include "port/serialport.h"
#include <QCamera>
#include <QCameraImageCapture>

class Port : QObject
{
    Q_OBJECT
public:
    Port(QObject *parent = nullptr);
    ~Port();

private:
    SerialPort * port;

    QCamera * camera;
    QCameraImageCapture * image;

    int flag;
};

#endif
