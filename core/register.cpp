#include "register.h"

#include "core/MachineControl.h"
#include "core/context.h"

void Register::registerClass(){
    //注意规范：核心类注入处

    //注册类型
    qRegisterMetaType<QMap<int,QStringList>>("QMap<int,QStringList>");

    //核心类实现后请在此处注入
     qmlRegisterType<MachineControl>("Core.MachineControl", 1, 0, "MachineControl");//机器控制
     qmlRegisterUncreatableType<Context>("Core.Context", 1, 0, "Context","请务实例化此对象");//sql执行
}
