#ifndef SETTINGSWINDOWBACKEND_H
#define SETTINGSWINDOWBACKEND_H

#include <QObject>
#include "config/runtimedata.h"

class SettingsWindowBackend : public QObject
{
    Q_OBJECT
public:
    static SettingsWindowBackend* get(QObject* parent = nullptr);

signals:

private:
    explicit SettingsWindowBackend(QObject *parent = nullptr);
    static SettingsWindowBackend* pointer;

};

#endif // SETTINGSWINDOWBACKEND_H
