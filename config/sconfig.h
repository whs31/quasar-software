#ifndef SCONFIG_H
#define SCONFIG_H

#include <QObject>

class SConfig : public QObject
{
    Q_OBJECT
public:
    explicit SConfig(QObject *parent = nullptr);

signals:

};

#endif // SCONFIG_H
