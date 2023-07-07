#ifndef RECEIVER_H
#define RECEIVER_H

#include <QWidget>
#include <QUdpSocket>
#include <QTime>
#include <QTimer>

struct Packet {
    int id;
    int numOfDatagrams;
    QString time;
    QByteArray payload;
    Packet() {}
    Packet(int t1, int t2, QString t3, QByteArray t4) : id(t1), numOfDatagrams(t2), time(t3), payload(t4) {}
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

private slots:
    void processData();
    void checkProcess();

private:
    Ui::Receiver *ui;
    QUdpSocket *receiver, *senderSocket;
    QTimer *timer;
    Packet dataGram;
    QHostAddress senderAddress;
    unsigned int allDatagramPayload;
    unsigned int countDatagram;
    double speed;
    QTime startTime, endTime;
    bool isReading;

    void sendInfo();
    bool isChannelOverloaded();

    void initSenderSocket();
    void initReceiverSocket();
    void initTimer();

};

#endif // RECEIVER_H
