#ifndef RECEIVER_H
#define RECEIVER_H

#include <QWidget>
#include <QUdpSocket>
#include <QTimer>
#include <cmath>
#include <QDateTime>

struct Packet {
    int id;
    int numOfDatagrams;
    qint64 time;
    QByteArray payload;
    Packet() {}
    Packet(int t1, int t2, qint64 t3, QByteArray t4) : id(t1), numOfDatagrams(t2), time(t3), payload(t4) {}
 };

namespace Ui {
class Receiver;
}

class Receiver : public QWidget
{
    Q_OBJECT

public:
    explicit Receiver(QWidget *parent = 0);
    ~Receiver();

private:
    void sendInfo();
    bool isChannelOverloaded();
    void initSenderSocket();
    void initReceiverSocket();
    void initTimer();

private slots:
    void processData();
    void checkProcess();

private:
    Ui::Receiver *ui;
    QUdpSocket *receiver, *senderSocket;
    QTimer *timer;
    Packet dataGram;
    QHostAddress senderAddress;
    int allDatagramPayload;
    unsigned int countDatagram;
    double curSpeed, prevSpeed;
    qint64 startTime, endTime, receiverSTime, receiverETime;
    bool isReading;

};

#endif // RECEIVER_H
