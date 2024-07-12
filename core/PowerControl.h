#ifndef _POWER_CONTROL_H
#define _POWER_CONTROL_H

#include <QString>
#include <QDebug>

typedef int time_s;
typedef bool BoolReturnValue;

enum TimeSet{
    Legal = 0,
};

#define UNUSE_METHOD 0
#define USE_METHOD 1


class PowerControl
{
public:
    PowerControl();
    ~PowerControl();

    bool MachineOff(time_s off_Sec = 0);//关机函数

    bool MachineSleep(time_s Sleep_Sec = 0);//睡眠函数
    bool MachineReboot(time_s Reboot_Sec = 0);//重启函数
private:
    time_s sec ;//单位秒,用于制定关机 睡眠 重启多久后执行
};

#endif
