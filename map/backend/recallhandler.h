#ifndef IRECALLHANDLER_H
#define IRECALLHANDLER_H

#include <QObject>
#include <QMessageBox>
#include "linkerqml.h"
#include <QStandardPaths>
#include <QFileDialog>

#include "config/runtimedata.h"
#include "config/sconfig.h"

class RecallHandler : public QObject
{
    Q_OBJECT
public:
    explicit RecallHandler(QObject *parent = nullptr);
    Q_INVOKABLE bool clearTrack(void);
    Q_INVOKABLE void reconnect(void);
    Q_INVOKABLE void disconnect(void);
    Q_INVOKABLE void changeDirectory(void);
    Q_INVOKABLE bool calibrateSeaLevel(void);
    Q_INVOKABLE bool clearMap(void);
    Q_INVOKABLE bool clearCache(void);
    Q_INVOKABLE void placeMarker(void);
    Q_INVOKABLE void clearSARDisk(void);

};

#endif // IRECALLHANDLER_H
