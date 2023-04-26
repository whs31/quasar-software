#include "feedbackemulator.h++"
#include <QtCore/QDebug>
#include <QtNetwork/QUdpSocket>

using namespace Debug;

FeedbackEmulator::FeedbackEmulator(QObject *parent)
    : QObject{parent}
    , socket(new QUdpSocket(this))
{

}

void FeedbackEmulator::setAddress(const QString& address)
{
    if(not address.contains(":") or address.split(":").size() != 2) {
        qCritical() << "[DEBUG] Provided incorrect host address";
        return;
    }

    ip = address.split(":").first();
    port = address.split(":").last().toUInt();
    started = true;
}

void FeedbackEmulator::send(QByteArray data)
{
    if(not started) {
        qWarning() << "[DEBUG] Provide host address to emulator via console command [feedbackemu_init]";
        return;
    }

    socket->writeDatagram(data, QHostAddress(this->ip), this->port);
}

void FeedbackEmulator::testVT100()
{
    char buf[16];
    for(size_t i = 0; i < 100; i++){
        sprintf(buf, "<%3d%%>\e[6D", i);
        this->send(buf);
    }
    this->send("*FREE_DISK_SPACE* 70061867 114855520");
}



