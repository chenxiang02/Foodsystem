#ifndef _TCP_SERVE_H
#define _TCP_SERVE_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThreadPool>
#include <QObject>
#include <QList>
#include <QTimer>
#include <QDebug>

class TcpServe : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServe(QObject *parent = nullptr);
    ~TcpServe();
protected:
    void incomingConnection(qintptr handle) override;

signals:
    void SQLfind(QTcpSocket *socket,QString date);
    void ReceiveDate(QTcpSocket *socket,QString date);

private slots:
    void clientDisconnected(); //当产生客户端断开连接时向上层发送信号
    void readClientData();
    void handlerHeart();//心跳处理槽函数
private:
    QList<QTcpSocket*> ClientSockets; //服务器Socket链表
    QList<int> HeartId;//心跳检测表
    bool CheckHeartPack;
    QTimer * time;
};

#endif
