#include "feedbackremote.h"

FeedbackRemote::FeedbackRemote(QObject *parent, PluginHostAPI* pluginHostAPI)
    : QObject{parent}, pluginHostAPI(pluginHostAPI)
{
    udpRemote = new UDPRemote();
    QObject::connect(udpRemote, SIGNAL(received(QByteArray)), this, SLOT(receiveFeedback(QByteArray)));
}

FeedbackRemote::~FeedbackRemote()
{
    udpRemote->Disconnect();
    delete udpRemote;
}

void FeedbackRemote::connect(QString ip, quint16 port)
{
    disconnect();
    udpRemote->Connect(ip + ":" + QString::number(port));
    Debug::Log("[FEEDBACK REMOTE] Listening to SAR on " + ip + ":" + QString::number(port));
}

void FeedbackRemote::disconnect(void)
{
    udpRemote->Disconnect();
    Debug::Log("[FEEDBACK REMOTE] Disconnecting...");
}

void FeedbackRemote::receiveFeedback(QByteArray data)
{
    //emit redirectFeedback(data);
    pluginHostAPI->execute("Terminal", "print", data);

    QString stringData = data.data();
    QString dataString = data.data();
    if(dataString.contains(STORAGE_STATUS_MARKER))
    {
        QStringList _split;
        dataString.remove(STORAGE_STATUS_MARKER);
        dataString.remove(0, 1);
        Debug::Log("[SAR] Received storage status: " + dataString);
        _split = dataString.split(' ', Qt::SkipEmptyParts);
        //RuntimeData::get()->setFreeDiskSpace(_split.first().toInt());
        //RuntimeData::get()->setTotalDiskSpace(_split.last().toInt());
    }
}