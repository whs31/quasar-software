#ifndef IRECALLHANDLER_H
#define IRECALLHANDLER_H

#include <QObject>
#include <QMessageBox>
#include <QStandardPaths>
#include <QFileDialog>

#include "config/runtimedata.h"
#include "config/sconfig.h"
#include "map/linkerqml.h"
#include "gui/windows/dialogwindowbackend.h"

class RecallHandler : public QObject
{
    Q_OBJECT
public:
    explicit RecallHandler(QObject *parent = nullptr);
    Q_INVOKABLE void reconnect(void);
    Q_INVOKABLE void disconnect(void);
    Q_INVOKABLE void changeDirectory(void);

};

#endif // IRECALLHANDLER_H
