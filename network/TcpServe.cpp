#include "TcpServe.h"

TcpServe::TcpServe(QObject *parent) :QTcpServer(parent)
{

}

TcpServe::~TcpServe()
{

}

void TcpServe::incomingConnection(qintptr handle)
{
    QTcpSocket * ClientSocket = new QTcpSocket(this);
    ClientSocket->setSocketDescriptor(handle);
    connect(ClientSocket,&QTcpSocket::readyRead,this,&TcpServe::readClientData);
    connect(ClientSocket,&QTcpSocket::disconnected,this,&TcpServe::clientDisconnected);
    ClientSockets.append(ClientSocket);
}

void TcpServe::clientDisconnected()
{
    QTcpSocket * clientSocket = qobject_cast<QTcpSocket*>(sender());
    if(clientSocket)
    {
        ClientSockets.removeOne(clientSocket);
        clientSocket->close();
        clientSocket->deleteLater();
    }
}

void TcpServe::readClientData()
{

    QTcpSocket * clientSocket = qobject_cast<QTcpSocket*>(sender());

    QString Date = QString::fromUtf8(clientSocket->readAll());

    if(Date.contains("SQL Requsted Find"))
        emit SQLfind(clientSocket,Date);
    if(Date.contains("Food List")&&Date.contains("List End"))
    {
        Date.remove(0,9);//删头去尾
        Date.remove(Date.length() - 8, 8);
        Date.append("MenuList");
        emit ReceiveDate(clientSocket,Date);
    }


}
