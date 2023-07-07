#include "sender.h"
#include "ui_widget.h"

Sender::Sender(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    numberOfDatagrams = 400;

    initSendSocket();
    initReceiveSocket();
    initTimer();
}

Sender::~Sender()
{
    delete ui;
}

void Sender::initTimer()
{
    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer,&QTimer::timeout,[&](){timer->stop();});
}

void Sender::initSendSocket()
{
    udpSocket=new QUdpSocket(this);
}

void Sender::initReceiveSocket()
{
    receiveSocket = new QUdpSocket(this);
    receiveSocket->bind(8888,QUdpSocket::ShareAddress);
    connect(receiveSocket,&QUdpSocket::readyRead,this,&Sender::processData);
}

QDataStream &operator <<(QDataStream &str, Packet & m)
{
  str << (qint32)m.id;
  str << (qint32)m.numOfDatagrams;
  str << m.time;
  str.writeRawData(m.payload.data(),m.payload.size());
  return str;
}

void Sender::on_btnSend_clicked()
{
    senderAddress = ui->lineIPSender->text();
    receiverAddress = ui->lineIPReceiver->text();
    //senderAddress = "192.168.50.207";
    //receiverAddress =  "192.168.50.16";

    sendData();
}

void Sender::sendData()
{
    for(int i=0; i<numberOfDatagrams; i++){

        Packet dataGram(i+1,numberOfDatagrams,QTime::currentTime().toString("hh:mm:ss"),{2000,'a'});

        QByteArray buf;
        QDataStream s(&buf, QIODevice::WriteOnly);
        if (false) s.setByteOrder(QDataStream::LittleEndian);
        s << dataGram;

        udpSocket->writeDatagram(buf, QHostAddress(receiverAddress), 7777);
    }

    ui->lblTest->setText(ui->lblTest->text()+" "+QString::number(numberOfDatagrams));
}

void Sender::processData()
{
    QByteArray data ;

    while(receiveSocket->hasPendingDatagrams()){
           data.resize(receiveSocket->pendingDatagramSize());
           receiveSocket->readDatagram(data.data(), data.size());
    }

    if (!timer->isActive() && QString(data) == "0" ){
        timer->start(2000);
        numberOfDatagrams+=300;
        sendData();
    }

}



