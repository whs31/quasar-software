#include "saroutputconsoleemulator.h"

SAROutputConsoleEmulator::SAROutputConsoleEmulator(QObject *parent)
    : QObject{parent}
{

}

void SAROutputConsoleEmulator::send(QByteArray data)
{
    QUdpSocket socket;
    socket.writeDatagram(data, QHostAddress("127.0.0.1"), SConfig::getHashString("ListenPort").toUInt());
}

void SAROutputConsoleEmulator::sampleTest(void)
{
    char buf[16];
    for(int cnt = 0; cnt < 100; cnt++){
        sprintf(buf, "<%3d%%>\e[6D", cnt);
        send(buf);
    }
    send("FREE_DISK_SPACE 1000000 10000000");
}
