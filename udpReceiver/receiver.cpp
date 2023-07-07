#include "receiver.h"
#include "ui_receiver.h"

Receiver::Receiver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Receiver)
{
    ui->setupUi(this);

    initReceiverSocket();
    initSenderSocket();
    initTimer();

    allDatagramPayload = 0;
    countDatagram = 0;
    speed = 0;
    isReading = false;
}

Receiver::~Receiver()
{
    delete ui;
}

void Receiver::initSenderSocket()
{
    senderSocket = new QUdpSocket(this);
}

void Receiver::initReceiverSocket()
{
    receiver = new QUdpSocket(this);
    receiver->bind(7777,QUdpSocket::ShareAddress);
    connect(receiver,&QUdpSocket::readyRead,this,&Receiver::processData);
}

void Receiver::initTimer()
{
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &Receiver::checkProcess);
}

QDataStream &operator >>(QDataStream &str, Packet &m)
{
  str >> m.id >> m.numOfDatagrams>>m.time;
  str.readRawData(m.payload.data(), m.payload.size());
  return str;
}

void Receiver::processData()
{
    int receivedDatagrams=0;

    if (!isReading){
        timer->start(3000);
        isReading = true;
    }

    while (receiver->hasPendingDatagrams()) {
       int dataGramSize = receiver->pendingDatagramSize();
       QByteArray buf(dataGramSize,Qt::Uninitialized);
       QDataStream s(&buf, QIODevice::ReadOnly);
       receiver->readDatagram(buf.data(), buf.size(),&senderAddress);

       dataGram.payload.resize(dataGramSize);
       s >> dataGram;

       if (!countDatagram)
           startTime = QTime::fromString(dataGram.time,QString("hh:mm:ss"));

       allDatagramPayload += dataGramSize;
       receivedDatagrams++;
    }

    countDatagram+=receivedDatagrams;
}

void Receiver::checkProcess()
{
    timer->stop();
    isReading = false;

    endTime = QTime::fromString(dataGram.time,QString("hh:mm:ss"));
    int transmissionTime = startTime.secsTo(endTime);

    if(isChannelOverloaded())
    {
        speed = (!transmissionTime) ? allDatagramPayload * 0.000008 : (allDatagramPayload * 0.000008)/transmissionTime;
        ui->label->setText(ui->label->text()+"\n\nПереполнение канала!\nКол-во принятых пакетов: "+QString::number(countDatagram)+" из "+QString::number(dataGram.numOfDatagrams)+"\nОбщий размер принятых пакетов (байт): "+QString::number(allDatagramPayload)+"\nВремя передачи (c): "+QString::number(transmissionTime)+"\nСкорость передачи (Mбит/с): "+QString::number(speed));
    }
    else
    {
        ui->label->setText(ui->label->text()+"\n\nКол-во принятых пакетов: "+QString::number(countDatagram)+" из "+QString::number(dataGram.numOfDatagrams));

        sendInfo();

        allDatagramPayload = 0;
        countDatagram = 0;
        speed = 0;
    }
}

void Receiver::sendInfo()
{
    QByteArray data(1,'0');
    for(int i=0; i<3; i++){
        senderSocket->writeDatagram(data.data(),data.size(), senderAddress, 8888);
    }
}

bool Receiver::isChannelOverloaded()
{
    if(dataGram.numOfDatagrams-countDatagram >= dataGram.numOfDatagrams*0.1)
        return true;
    return false;
}





