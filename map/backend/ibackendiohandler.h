#ifndef IBACKENDIOHANDLER_H
#define IBACKENDIOHANDLER_H

#include <QObject>
#include <QMessageBox>
#include "linkerqml.h"

class IBackendIOHandler : public QObject
{
    Q_OBJECT
public:
    explicit IBackendIOHandler(QObject *parent = nullptr);
    Q_INVOKABLE bool clearTrack(void);
    Q_INVOKABLE void reconnect(void);
    Q_INVOKABLE void disconnect(void);
};

#endif // IBACKENDIOHANDLER_H
