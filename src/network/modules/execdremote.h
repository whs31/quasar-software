#ifndef EXECDREMOTE_H
#define EXECDREMOTE_H

#include <QObject>

#include "network/udpremote.h"
#include "func/schecksum.h"
#include "misc/debug.h"

#include "config/runtimedata.h"
#include "config/config.h"
#include "data/datatelemetry.h"
#include "execd/argumentlist.h"

enum ExecdCommand : short int 
{
    StorageStatus,
    ClearStorage,
    FormImage,
    CheckServices
};

class ExecdRemote : public QObject
{
    Q_OBJECT
public:
    explicit ExecdRemote(QObject *parent = nullptr);
    ~ExecdRemote();
    
    void connect(QString ip, quint16 port);
    void disconnect(void);

public slots:
    void sendCommand(ExecdCommand command);

    void executeFormCommand();
    void executeClearCommand();

signals:

private slots:
    void receiveResponse(QByteArray data);

private:
    const QString STORAGE_STATUS_MARKER = "$FORM";
    const QString CACHE_CLEAR_COMMAND = "$clear_storage()";
    const QString STORAGE_STATUS_COMMAND = "$storage_status()";
    const QString FORM_MARKER = "$FORM";

    size_t getMessageID(void);
    QString makeCommand(QString string);

    UDPRemote *udpRemote = nullptr;
    size_t messageID = 0;
};

#endif // EXECDREMOTE_H
