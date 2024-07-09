#include "PowerControl.h"
#include <stdlib.h>


PowerControl::PowerControl(QObject * parent) : QObject(parent)
{
   qDebug()<<Q_FUNC_INFO<<"PowerControl类构造";
}

PowerControl::~PowerControl()
{
    qDebug()<<Q_FUNC_INFO<<"PowerControl类析沟";
}

bool PowerControl::MachineOff(time_s off_Sec)
{
    //用于判断用户输入参数是否合法
    if(off_Sec < Legal)
    {
        return false;
    }

//初期时间不够 后期请忽略此方法
#if USE_METHOD
    if(off_Sec == Legal)//立即关机
    {
      //执行shell命令 后期请使用内核注入方式
      BoolReturnValue ret = system("poweroff");
      return ret;
    }
    else //延时关机
    {
        QString receiveValue = "shutdown -t " + QString::number(off_Sec);
        BoolReturnValue ret = system(receiveValue.toUtf8());
        return ret;
    }
    return false;
#endif
}

bool PowerControl::MachineSleep(time_s Sleep_Sec)
{
    //用于判断用户输入参数是否合法
    if(Sleep_Sec < Legal)
    {
        return false;
    }
//初期时间不够 后期请忽略此方法
#if USE_METHOD
    if(Sleep_Sec == Legal)//立即睡眠
    {
        BoolReturnValue ret = system("");
    }
#endif
}

bool PowerControl::MachineReboot(time_s Reboot_Sec)
{
    //用于判断用户输入参数是否合法
    if(Reboot_Sec < Legal)
    {
        return false;
    }
//初期时间不够 后期请忽略此方法
#if USE_METHOD
    if(Reboot_Sec == Legal)//立即重启
    {
        BoolReturnValue ret = system("reboot");
        return ret;
    }
    else //延时重启
    {
       QTimer * timer = new QTimer();
       int RebootSEec = Reboot_Sec; //因为qt5要注入类型（qt6 没这么麻烦） 避免麻烦直接接受
       timer->start(RebootSEec);
       connect(timer,&QTimer::timeout,this,[&]{
           timer->stop();
           delete timer;
           system("reboot");
       });
       return true;
    }
    return false;
#endif
}
