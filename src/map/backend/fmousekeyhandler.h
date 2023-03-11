#ifndef FMOUSEKEYHANDLER_H
#define FMOUSEKEYHANDLER_H

#include <QObject>

#include "map/global/markermanager.h"
#include "config/runtimedata.h"

class FMouseKeyHandler : public QObject
{
    Q_OBJECT
public:
    explicit FMouseKeyHandler(QObject *parent = nullptr);
    Q_INVOKABLE void copyCoordinates(qreal latitude, qreal longitude);
    Q_INVOKABLE void placeMarker(qreal latitude, qreal longitude);

signals:

private:
    QClipboard* clipboard;
};

#endif // FMOUSEKEYHANDLER_H
