#include "tcpsocket.h"

TcpSocket::TcpSocket( QObject *parent) : QObject(parent)
{
    clientSocket = new QTcpSocket(this);
    clientSocket->abort();

    clientSocket->connectToHost("192.168.50.16",5555);

//    if(clientSocket->waitForConnected(3000))
//        qDebug()<<clientSocket->errorString();

    connect(clientSocket,&QAbstractSocket::connected, this, &TcpSocket::useConnection);
}

void TcpSocket::useConnection()
{
    qDebug()<<"Connected!";
}

void TcpSocket::sendMessage(QString s)
{
     clientSocket->write("0"); //отправляем сообщение серверу
}


