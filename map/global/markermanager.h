#ifndef MARKERMANAGER_H
#define MARKERMANAGER_H

#include <QObject>

class MarkerManager : public QObject
{
    Q_OBJECT
public:
    explicit MarkerManager(QObject *parent = nullptr);

signals:

};

#endif // MARKERMANAGER_H
