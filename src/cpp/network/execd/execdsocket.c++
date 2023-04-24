#include "execdsocket.h++"

using namespace Network;

ExecdSocket::ExecdSocket(QObject* parent)
    : AbstractUDPSocket{parent}
{

}

void ExecdSocket::start(const QString &address)
{
    this->connect(address);
    qDebug() << "[EXECD] Started socket";
}

void ExecdSocket::stop()
{
    this->disconnect();
    qDebug() << "[EXECD] Socket shutted down";
}

