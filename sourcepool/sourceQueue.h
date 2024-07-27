#ifndef _SOURCE_QUEUE_H
#define _SOURCE_QUEUE_H

#include <QString>
#include <QStringList>
#include <QObject>
#include <QDebug>
#include <iostream>

using namespace std;

extern "C"
{
    #include <stdio.h>
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
    long type;//必须要带的索引 具体可参考ipc文档
    char date[4096];
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

    int getIndex();
    void setIndex(int value);


public:
    static int count;

    static int getCount();
    static void setCount(int value);

private:

    long index;//全局索引
    key_t key;//消息队列键值
    int msgid;//消息队列操作符
};

#endif
