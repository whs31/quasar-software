#ifndef IBACKENDIOHANDLER_H
#define IBACKENDIOHANDLER_H

#include <QObject>
#include <QMessageBox>
#include "linkerqml.h"
#include <QStandardPaths>
#include <QFileDialog>
#include "runtimedata.h"

#include "sconfig.h"

class IBackendIOHandler : public QObject
{
    Q_OBJECT
public:
    explicit IBackendIOHandler(QObject *parent = nullptr);
    Q_INVOKABLE bool clearTrack(void);
    Q_INVOKABLE void reconnect(void);
    Q_INVOKABLE void disconnect(void);
    Q_INVOKABLE void changeDirectory(void);
    Q_INVOKABLE bool calibrateSeaLevel(void);
};

#endif // IBACKENDIOHANDLER_H
