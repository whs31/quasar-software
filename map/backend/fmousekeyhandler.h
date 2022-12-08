#ifndef FMOUSEKEYHANDLER_H
#define FMOUSEKEYHANDLER_H

#include <QObject>
#include "qqml.h"
#include <QClipboard>
#include <QMessageBox>

class FMouseKeyHandler : public QObject
{
    Q_OBJECT
public:
    explicit FMouseKeyHandler(QObject *parent = nullptr);
    Q_INVOKABLE void copyCoordinates(qreal latitude, qreal longitude);

signals:

private:
    QClipboard* clipboard;
};

#endif // FMOUSEKEYHANDLER_H
