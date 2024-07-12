#ifndef _MACHINE_CONTROL_H
#define _MACHINE_CONTROL_H


#include <QObject>
#include <QScopedPointer>
#include <iostream>
#include "systemlog/log.h"
#include "systemlog/success.h"
#include "systemlog/fault.h"
#include "systemlog/waring.h"
#include "PowerControl.h"


enum{
    PowerOff = 0,
    Sleep,
    Reboot
};

class MachineControl : public QObject//这种写法不好 有时间可以将他抽象封装一下
{
    Q_OBJECT
public:
    explicit MachineControl(QObject *parent=nullptr);
   ~MachineControl();
   Q_INVOKABLE void setPower(int PowerRight,int TimeOut);

signals:
   void PowerSignal();

private:
   PowerControl * d;
};


#endif
