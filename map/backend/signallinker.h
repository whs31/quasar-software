#ifndef SIGNALLINKER_H
#define SIGNALLINKER_H

#include <QObject>

class SignalLinker : public QObject
{
    Q_OBJECT
public:
    static SignalLinker* get(QObject* parent = nullptr);
    void sendClose(void);
    void sendMinimize(void);
    void sendLog(void);
    void sendSettings(void);
    void sendInfo(void);
    void sendEmulator(void);
    Q_INVOKABLE void formSingleImage(void); 
    

private:
    static SignalLinker* _instance;
    explicit SignalLinker(QObject *parent = nullptr);

signals:
    void closeSignal();
    void minimizeSignal();
    void settingsSignal();
    void infoSignal();
    void logSignal();
    void emulatorSignal();
    void formSingleImageSignal();

};

#endif // SIGNALLINKER_H
