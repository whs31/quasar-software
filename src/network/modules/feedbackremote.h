#ifndef FEEDBACKREMOTE_H
#define FEEDBACKREMOTE_H

#include <QObject>

#include "network/udpremote.h"
#include <plugin.h>
#include <pluginHostAPI.h>

class FeedbackRemote : public QObject
{
    Q_OBJECT
public:
    explicit FeedbackRemote(QObject *parent = nullptr, PluginHostAPI* pluginHostAPI = nullptr);
    ~FeedbackRemote();
    
    void connect(QString ip, quint16 port);
    void disconnect(void);

signals:
    void redirectFeedback(QByteArray data);

private slots:
    void receiveFeedback(QByteArray data);

private:
    const QString STORAGE_STATUS_MARKER = "*FREE_DISK_SPACE*";

    UDPRemote *udpRemote = nullptr;
    PluginHostAPI* pluginHostAPI = nullptr;
};

#endif // FEEDBACKREMOTE_H
