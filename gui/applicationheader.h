#ifndef APPLICATIONHEADER_H
#define APPLICATIONHEADER_H

#include <QObject>
#include "backend/signallinker.h"

class ApplicationHeader : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationHeader(QObject *parent = nullptr);
    Q_INVOKABLE void close(void);

signals:

};

#endif // APPLICATIONHEADER_H
