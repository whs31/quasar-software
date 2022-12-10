#ifndef FMOUSEKEYHANDLER_H
#define FMOUSEKEYHANDLER_H

#include <QObject>
#include "qqml.h"
#include <QClipboard>
#include <QMessageBox>
#include "backend/smousestate.h"
#include "global/markermanager.h"

class FMouseKeyHandler : public QObject
{
    Q_OBJECT
public:
    explicit FMouseKeyHandler(QObject *parent = nullptr);
    Q_INVOKABLE void copyCoordinates(qreal latitude, qreal longitude);
    Q_INVOKABLE void placeMarker(qreal latitude, qreal longitude); //in qml: if mousestate == MARKERPLACEMENT, draw ghost marker which follows cursor

    Q_PROPERTY(short int mouseState READ mouseState WRITE setMouseState NOTIFY mouseStateChanged);

    short int mouseState(void);
    void setMouseState(short int state);

signals:
    void mouseStateChanged();

private:
    QClipboard* clipboard;
    short int _mouseState = MouseState::Blank;
};

#endif // FMOUSEKEYHANDLER_H
