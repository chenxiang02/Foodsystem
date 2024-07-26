#include "sourceQueue.h"

SourceQueue::SourceQueue(QObject *parent)
    : QObject(parent)
{
    index = 1;//队列必须从1开始
    if((key = ftok(".",100))==-1)
    {
        qDebug()<<Q_FUNC_INFO<<"ftok打开失败";
    }

    if((msgid = msgget(key,IPC_CREAT | 0777)) == -1)
    {
        qDebug()<<Q_FUNC_INFO<<"msgget获取失败";
    }
    qDebug()<<Q_FUNC_INFO<<"SourceQueue类构造";
}

SourceQueue::~SourceQueue()
{
    qDebug()<<Q_FUNC_INFO<<"SourceQueue类析构";
}

bool SourceQueue::sendMsg(QString data)
{
    QueueInfomation msg;

    msg.type = index;//遵守队列规则

    QByteArray toChar = data.toUtf8();//防止中文乱码

    memset(msg.date,0,sizeof(msg.date));//初始化缓存区

    strcpy(msg.date,toChar.data());//复值数据区

    int length = strlen(msg.date) ;

    msg.date[length + 1] = '\0';//结尾标识符

    ++index;
    return msgsnd(this->msgid,&msg,length,0);

}

QString SourceQueue::receiveMsg()
{
   QueueInfomation msg;
   if(msgrcv(this->msgid,&msg,MSGLEN,0,0) == -1)
   {
       qDebug()<<Q_FUNC_INFO<<"msgrcv 接收信息错误";
       return "null";
   }
   QString date = QString::fromUtf8(msg.date);
   return date;

}

void SourceQueue::DestroyMsg()
{
    msgctl(this->msgid,IPC_RMID,NULL);
}

void SourceQueue::setIndex(int value)
{
    index = value;
}
