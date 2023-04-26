#include "feedbacksocket.h++"

using namespace Network;

FeedbackSocket::FeedbackSocket(QObject* parent)
    : AbstractUDPSocket{parent}
{

}


void FeedbackSocket::start(const QString& address)
{
    this->connect(address);
    qDebug() << "[FEEDBACK] Started socket";
}

void FeedbackSocket::stop()
{

}

void FeedbackSocket::processResult(QByteArray data)
{

}
