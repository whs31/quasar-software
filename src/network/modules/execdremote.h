#ifndef EXECDREMOTE_H
#define EXECDREMOTE_H

#include <QObject>

class ExecdRemote : public QObject
{
    Q_OBJECT
public:
    explicit ExecdRemote(QObject *parent = nullptr);

signals:

};

#endif // EXECDREMOTE_H
