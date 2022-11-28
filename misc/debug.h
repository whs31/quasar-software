#ifndef DEBUG_H
#define DEBUG_H

#include <QObject>
#include <QDebug>

class Debug : public QObject
{
    Q_OBJECT
public:
    explicit Debug(QObject *parent = nullptr);
    static void Log(QString text);
signals:

};

#endif // DEBUG_H
