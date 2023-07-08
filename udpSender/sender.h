#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QByteArray>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class Widget;
}

class Sender : public QWidget
{
    Q_OBJECT

public:
    explicit Sender(QWidget *parent = 0);
    ~Sender();

private:
    void sendData();
    void initTimer();
    void initSendSocket();
    void initReceiveSocket();

private slots:
    void on_btnSend_clicked();
    void processData();

private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket, *receiveSocket;
    QString senderAddress, receiverAddress;
    QTimer *timer;
    int numberOfDatagrams;
};

struct Packet {
    int id;
    int numOfDatagrams;
    qint64 time;
    QByteArray payload;
    Packet() {}
    Packet(int t1, int t2, qint64 t3, QByteArray t4) : id(t1), numOfDatagrams(t2), time(t3), payload(t4) {}
 };

#endif // WIDGET_H
