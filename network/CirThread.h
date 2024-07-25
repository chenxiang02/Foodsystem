#ifndef _CIR_THREAD_H
#define _CIR_THREAD_H

#include <QThread>
#include <QObject>
#include "sourcepool/sourceQueue.h"
#include "TcpServe.h"

extern "C"
{
    #include <time.h>
    #include <string.h>
}

class CirThread:public QThread
{
    Q_OBJECT
public:

    enum EventStatus{
      SQL_Inquire_Food_Menu //sql查询语句
    };

    CirThread();
    ~CirThread();

public slots:
    void dataReceive(QTcpSocket * socket,QString Data);//数据
    void sqlFind(QTcpSocket * socket,QString Data);//sql查询

    void run() override;

private:
    TcpServe * serve;
    SourceQueue * storage;
};

#endif
