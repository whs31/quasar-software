#ifndef SIGNALLINKER_H
#define SIGNALLINKER_H

#include <QObject>

class SignalLinker : public QObject
{
    Q_OBJECT
public:
    static SignalLinker* get(QObject* parent = nullptr);
    void sendClose(void);
    

private:
    static SignalLinker* _instance;
    explicit SignalLinker(QObject *parent = nullptr);

signals:
    void closeSignal();

};

#endif // SIGNALLINKER_H
