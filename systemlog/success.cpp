#include "success.h"


Success::Success()
{
    qDebug()<<Q_FUNC_INFO<<"Success类构造";

    pathDir = new QDir("/etc/FoodSystem");

    if(!pathDir->exists(pathDir->path())) // 如果该目录不存在则自动创建
    {
        qDebug()<<pathDir->mkdir(pathDir->path());//注意请用root权限运行程序
    }

    QString fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd");//获取当天日期文件名

    writeSuccess = new QFile(pathDir->path()+"/"+fileName+".log");

    if(pathDir->exists(writeSuccess->fileName()))//如果文件存在以写入追加形式打开
    {
        writeSuccess->open(QIODevice::Append|QIODevice::WriteOnly);
    }
    else//如果不存在则以创建方式打开
    {
        writeSuccess->open(QIODevice::Truncate|QIODevice::WriteOnly);
    }

    if(!writeSuccess->isOpen())
    {
        qDebug()<<Q_FUNC_INFO<<"文件打开失败";
    }
}

Success::~Success()
{
   delete writeSuccess;
   delete pathDir;
   qDebug()<<Q_FUNC_INFO<<"Success类回收";
}


void Success::printLog(QString info)
{
    QString fileContext = QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss") +" Success: "+ info +"\n";//拼接输入内容
    this->writeSuccess->write(fileContext.toUtf8(),fileContext.length());
    this->writeSuccess->close();
}
