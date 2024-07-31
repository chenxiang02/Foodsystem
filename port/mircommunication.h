#ifndef _MIR_COMMUNCATION_H
#define _MIR_COMMUNCATION_H

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QObject>

class MirCommunication : public QObject
{
public:
    MirCommunication();
    virtual ~MirCommunication();
};


#endif
