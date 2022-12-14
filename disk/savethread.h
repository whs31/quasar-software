#ifndef SAVETHREAD_H
#define SAVETHREAD_H

#include <QThread>
#include <QObject>

class SaveThread : public QThread
{
    Q_OBJECT
public:
    explicit SaveThread(QObject *parent = nullptr);
};

#endif // SAVETHREAD_H
