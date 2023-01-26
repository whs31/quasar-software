#ifndef DEBUG_H
#define DEBUG_H

#include <QObject>
#include <QDebug>
#include <QDateTime>

class Debug : public QObject
{
    Q_OBJECT
public:
    explicit Debug(QObject *parent = nullptr);
    static void Log(QString text);
    static void NewSession();
signals:

};

#endif // DEBUG_H
