#ifndef _SOURCE_QUEUE_H
#define _SOURCE_QUEUE_H

#include <QString>
#include <QStringList>
#include <QObject>
#include <QDebug>

extern "C"
{
    #include <string.h>
    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/msg.h>
}



enum MessageType{
    MenuList = 0,
};

typedef struct QueueStruct
{
    int type;
    char date[2048];
}QueueInfomation;

#define MSGLEN sizeof(QueueInfomation)


class SourceQueue : public QObject
{
    Q_OBJECT
public:
    SourceQueue(QObject * parent = nullptr);
    ~SourceQueue();

    bool sendMsg(QString data);//接收信息
    QString receiveMsg();//发送信息

    void DestroyMsg();

//    static int getIndex();
//    static void setIndex();

private:
    static int index;//全局索引
    key_t key;//消息队列键值
    int msgid;//消息队列操作符
};

#endif
