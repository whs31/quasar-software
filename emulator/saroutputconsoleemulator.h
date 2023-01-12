#ifndef SAROUTPUTCONSOLEEMULATOR_H
#define SAROUTPUTCONSOLEEMULATOR_H

#include <QObject>
#include <QByteArray>
#include <QUdpSocket>
#include "sconfig.h"

class SAROutputConsoleEmulator : public QObject
{
    Q_OBJECT
public:
    explicit SAROutputConsoleEmulator(QObject *parent = nullptr);
    void send(QByteArray data);
    void sampleTest(void);

signals:

};

#endif // SAROUTPUTCONSOLEEMULATOR_H
