#include "register.h"

#include "core/food.h"

#include "core/MachineControl.h"
#include "core/context.h"

#include "defaultconfig/rightconfig.h"
#include "defaultconfig/workconfig.h"
#include "defaultconfig/MenuDetail.h"
#include "defaultconfig/DataWidget.h"
#include "defaultconfig/OrderManage.h"
#include "defaultconfig/staff.h"

#include "network/CirThread.h"

void Register::registerClass(){
    //注意规范：核心类注入处

    //注册类型
    qRegisterMetaType<QMap<int,QStringList>>("QMap<int,QStringList>");

    //配置文件读写
    qmlRegisterType<RightConfig>("Config.Right",1,0,"ConfigRight");
    qmlRegisterType<WorkConfig>("Config.Work",1,0,"Work");
    qmlRegisterType<MenuDetail>("Config.MenuDetail",1,0,"MenuDetail");
    qmlRegisterType<DataWidget>("Config.DataWidget",1,0,"DataWidget");
    qmlRegisterType<OrderManage>("Config.OrderManage",1,0,"OrderManage");
    qmlRegisterType<Staff>("Config.Staff",1,0,"Staff");

    //核心类实现后请在此处注入
     qmlRegisterType<MachineControl>("Core.MachineControl", 1, 0, "MachineControl");//机器控制
     qmlRegisterType<Context>("Core.Context", 1, 0, "Context");//sql执行
//     qmlRegisterType<CirThread>("Core.CirThread", 1, 0, "CirThread");
}


#include "network/CirThread.h"

void Register::regiseterServe()//服务注入
{
   CirThread* d = new CirThread;
   d->run();

}
