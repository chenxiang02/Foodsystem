#include "sourceQueue.h"

SourceQueue::SourceQueue(QObject *parent)
    : QObject(parent)
{
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
    msg.type = MenuList;
    strcpy(msg.date,data.toUtf8());
    return msgsnd(this->msgid,&msg,MSGLEN,0);
}

QString SourceQueue::receiveMsg()
{
   QueueInfomation msg;
   if(msgrcv(this->msgid,&msg,MSGLEN,0,0) == -1)
   {
       qDebug()<<Q_FUNC_INFO<<"msgrcv 接收信息错误";
       return "null";
   }
   QString date = msg.date;
   qDebug()<<"----"<<date;
   return date;

}

void SourceQueue::DestroyMsg()
{
   msgctl(this->msgid,IPC_RMID,NULL);
}
