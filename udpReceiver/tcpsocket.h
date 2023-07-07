#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>


class TcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = 0);
    void sendMessage(QString s);

signals:

private slots:
    void useConnection();

private:
     QTcpSocket *clientSocket;
};

#endif // TCPSOCKET_H
