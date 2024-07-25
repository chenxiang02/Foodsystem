#ifndef _TCP_SERVE_H
#define _TCP_SERVE_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThreadPool>
#include <QObject>
#include <QList>

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

private:
    QList<QTcpSocket*> ClientSockets; //服务器Socket ID链表
};

#endif
