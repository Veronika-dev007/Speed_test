#include "sender.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("SpeedTest");
    QApplication::setApplicationName("UdpSender");

    Sender w;
    w.show();

    return a.exec();
}
