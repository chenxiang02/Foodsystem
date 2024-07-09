#ifndef __LOG_H
#define __LOG_H

#include <QDir>
#include <QFile>
#include <QFileDevice>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

enum LogInfo{
    Execute_SUCCESS,
    Waring,
    Segment_FAULT
};

class Log
{
public:
    Log();
    virtual ~Log();//接口类的析沟虚化

    /*
     * 为方便后续阅读,请遵守以下格式
     * 1.日志文件命名格式为年月日+应用程序名.log(如202-6-28-FoodSystem.log) 统一存放在/etc/应用程序名/log/ 中
     * 2.日志输入信息为年月日时分秒+执行状态码+文件+函数名，如(2024.6.28 12:15:18 Waring xxx类:xxx函数)
     * 3.关于p0事故查阅 一定要在程序崩溃日志+特殊符号提醒 如下（
     *
     * -------------------Segment_FAULT-------------
     * 2024.6.28 12:15:18 Segment_FAULT xxx类:xxx函数
     * ---------------------------------------------'
     *
     *
     * ）
    */

    virtual void printLog(QString info) = 0;//多态输出信息接口
};

#endif
