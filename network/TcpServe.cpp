#include "TcpServe.h"

TcpServe::TcpServe(QObject *parent) :QTcpServer(parent)
{
    this->time = new QTimer(this);

    this->time->setInterval(60 * 1000);//60秒一个轮回

    this->time->start();

    this->CheckHeartPack = false;

    connect(time,&QTimer::timeout,this,&TcpServe::handlerHeart);//心跳检测 定时循环

    qDebug()<<Q_FUNC_INFO<<"TcpServe类构造";
}

TcpServe::~TcpServe()
{
    qDebug()<<Q_FUNC_INFO<<"TcpServe类析构";
}

void TcpServe::incomingConnection(qintptr handle)
{
    QTcpSocket * ClientSocket = new QTcpSocket(this);
    ClientSocket->setSocketDescriptor(handle);
    connect(ClientSocket,&QTcpSocket::readyRead,this,&TcpServe::readClientData);
    connect(ClientSocket,&QTcpSocket::disconnected,this,&TcpServe::clientDisconnected);
    ClientSockets.append(ClientSocket);
    HeartId.append(1);
}

void TcpServe::clientDisconnected()
{
    QTcpSocket * clientSocket = qobject_cast<QTcpSocket*>(sender());
    if(clientSocket)
    {
        HeartId.removeAt(ClientSockets.indexOf(clientSocket));//移除检测位
        ClientSockets.removeOne(clientSocket);
        clientSocket->close();
        clientSocket->deleteLater();
    }
}

void TcpServe::readClientData()
{

    QTcpSocket * clientSocket = qobject_cast<QTcpSocket*>(sender());

    QString Date = QString::fromUtf8(clientSocket->readAll());

    if(Date.contains("SQL Requsted Find")) //sql查询返回菜单
        emit SQLfind(clientSocket,Date);
    else if(Date.contains("Food List")&&Date.contains("List End"))//客户包:菜单信息
    {
        Date.remove(0,9);//删头去尾
        Date.remove(Date.length() - 8, 8);
        Date.append("MenuList");
        emit ReceiveDate(clientSocket,Date);
    }
    else if(Date.contains("Heart Palindrome"))//心跳检测回文包
    {
        HeartId[ClientSockets.indexOf(clientSocket)] = 1;
    }


}

void TcpServe::handlerHeart()
{
    QString heartData = "10101111";//协议头
    heartData.append("Heart Pack");
    heartData.append("01011111");//协议尾

    if(CheckHeartPack)
    {
        for(int i = 0;i < HeartId.size();i++)
        {
            if(HeartId.at(i) == 0)
            {
                this->ClientSockets[i]->close();
                this->ClientSockets.removeAt(i);
            }else
            {
                this->HeartId[i] = 0;
            }
        }
    }

    for(int i = 0;i < ClientSockets.size();i++)
    {
        ClientSockets[i]->write(heartData.toUtf8());
    }
    CheckHeartPack = true;
}
