#ifndef REMOTE_H
#define REMOTE_H

#include <QObject>

class Remote : public QObject
{
    Q_OBJECT
public:
    explicit Remote(QObject *parent = nullptr);
    virtual int Connect(__attribute__((unused)) QString addr) { return -1; };
    virtual int Disconnect() { return -1; };
    virtual int Send(__attribute__((unused)) QByteArray data) { return -1; };
signals:
    void received(QByteArray data);
    void disconnected();
};

#endif // REMOTE_H
