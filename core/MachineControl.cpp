#include "MachineControl.h"

MachineControl::MachineControl(QObject *parent):QObject(parent)
{
    this->d = new PowerControl;
   qDebug()<<Q_FUNC_INFO<<"MachineControl类构造";
}

MachineControl::~MachineControl()
{
    delete  d;
    qDebug()<<Q_FUNC_INFO<<"MachineControl类析沟";
}

void MachineControl::setPower(int PowerRight,int TimeOut)
{
    Success info_Success;
    Fault info_Fault;
    WaringInfo info_Waring;
    Log * printRecord = &info_Success;
    try {
        if(PowerRight == PowerOff)//这里后期优化 可以考虑工厂模式 因时间有限暂不作处理
        {
           d->MachineOff(TimeOut);
        }else if(PowerRight == Sleep)
        {
            d->MachineSleep(TimeOut);
        }else if(PowerRight == Reboot)
        {
            d->MachineReboot(TimeOut);
        }
    } catch (const std::exception& e) {
        printRecord = &info_Fault;
        printRecord->printLog("MachineControl类 Power函数执行失败");
    }

    printRecord->printLog("MachineControl类 Power函数执行成功");
}

