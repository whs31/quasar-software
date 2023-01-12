#include "saroutputconsoleemulator.h"

SAROutputConsoleEmulator::SAROutputConsoleEmulator(QObject *parent)
    : QObject{parent}
{

}

void SAROutputConsoleEmulator::send(QByteArray data)
{
    QUdpSocket socket;
    socket.writeDatagram(data, QHostAddress(SConfig::getHashString("LoaderIP")), SConfig::getHashString("ListenPort").toUInt());
    qDebug()<<SConfig::getHashString("LoaderIP")<<":"<<SConfig::getHashString("ListenPort").toUInt();
}

void SAROutputConsoleEmulator::sampleTest(void)
{
    send("Hello world!");
    send("Привет мир!");
    send("\nNew line\n");
    char buf[16];
    for(int cnt = 0; cnt < 100; cnt++){
        sprintf(buf, "<%3d%%>\e[6D", cnt);
        send(buf);
    }
}
