#ifndef FMOUSEKEYHANDLER_H
#define FMOUSEKEYHANDLER_H

#include <QObject>
#include "qqml.h"
#include <QClipboard>
#include <QMessageBox>
#include "global/markermanager.h"
#include "runtimedata.h"
#include "stext.h"

class FMouseKeyHandler : public QObject
{
    Q_OBJECT
public:
    explicit FMouseKeyHandler(QObject *parent = nullptr);
    Q_INVOKABLE void copyCoordinates(qreal latitude, qreal longitude);
    Q_INVOKABLE void placeMarker(qreal latitude, qreal longitude); //in qml: if mousestate == MARKERPLACEMENT, draw ghost marker which follows cursor

    Q_PROPERTY(qint16 mouseState READ mouseState WRITE setMouseState NOTIFY mouseStateChanged);

    qint16 mouseState(void);
    void setMouseState(qint16 state);

signals:
    void mouseStateChanged();

private:
    QClipboard* clipboard;
    qint16 _mouseState = MouseState::Blank;
};

#endif // FMOUSEKEYHANDLER_H
