#ifndef AUTOCAPTUREMARKWINDOWBACKEND_H
#define AUTOCAPTUREMARKWINDOWBACKEND_H

#include <QObject>
#include "config/runtimedata.h"

class AutocaptureMarkWindowBackend : public QObject
{
    Q_OBJECT
public:
    static AutocaptureMarkWindowBackend* get(QObject* parent = nullptr);

signals:

private:
    explicit AutocaptureMarkWindowBackend(QObject *parent = nullptr);
    static AutocaptureMarkWindowBackend* pointer;

};

#endif // AUTOCAPTUREMARKWINDOWBACKEND_H
