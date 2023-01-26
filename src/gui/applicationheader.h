#ifndef APPLICATIONHEADER_H
#define APPLICATIONHEADER_H

#include <QObject>

#include "map/backend/signallinker.h"

class ApplicationHeader : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationHeader(QObject *parent = nullptr);
    Q_INVOKABLE void close(void);
    Q_INVOKABLE void minimize(void);
    Q_INVOKABLE void log(void);
    Q_INVOKABLE void settings(void);
    Q_INVOKABLE void info(void);
    Q_INVOKABLE void emulator(void);

signals:

};

#endif // APPLICATIONHEADER_H
