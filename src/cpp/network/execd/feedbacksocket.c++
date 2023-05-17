#include "feedbacksocket.h"

using namespace Network;

FeedbackSocket::FeedbackSocket(QObject* parent)
    : AbstractUDPSocket{parent}
{
    QObject::connect(this, &FeedbackSocket::received, this, &FeedbackSocket::processResult);
}


void FeedbackSocket::start(const QString& address)
{
    this->connect(address);
    qInfo().noquote() << "[FEEDBACK] Started listening to SAR on" << address;
}

void FeedbackSocket::stop()
{
    this->disconnect();
    qInfo() << "[FEEDBACK] Socket disconnected";
}

void FeedbackSocket::processResult(QByteArray data)
{
    QString string = data.data();
    QString dataString = data.data();
    if(dataString.contains(STORAGE_STATUS_MARKER))
    {
        dataString.remove(STORAGE_STATUS_MARKER);
        dataString.remove(0, 1);

        qDebug().noquote() << "[SAR] Received storage status: " << dataString;

        emit diskSpaceReceived(dataString.split(' ', Qt::SkipEmptyParts).first().toLong(),
                               dataString.split(' ', Qt::SkipEmptyParts).last().toLong());
    }

    emit textReceived(data);
    emit socketMetrics(data, data.size(), false);
}
