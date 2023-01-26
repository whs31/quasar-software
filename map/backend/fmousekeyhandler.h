#ifndef FMOUSEKEYHANDLER_H
#define FMOUSEKEYHANDLER_H

#include <QObject>
#include "qqml.h"
#include <QClipboard>
#include <QMessageBox>
#include "global/markermanager.h"
#include "config/runtimedata.h"
#include "stext.h"

class FMouseKeyHandler : public QObject
{
    Q_OBJECT
public:
    explicit FMouseKeyHandler(QObject *parent = nullptr);
    Q_INVOKABLE void copyCoordinates(qreal latitude, qreal longitude);
    Q_INVOKABLE void placeMarker(qreal latitude, qreal longitude); //in qml: if mousestate == MARKERPLACEMENT, draw ghost marker which follows cursor

signals:

private:
    QClipboard* clipboard;
};

#endif // FMOUSEKEYHANDLER_H
