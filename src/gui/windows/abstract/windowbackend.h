#ifndef WINDOWBACKEND_H
#define WINDOWBACKEND_H

#include <QObject>
#include "config/runtimedata.h"

class WindowBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool shown           READ getShown        WRITE setShown             NOTIFY shownChanged)
    Q_PROPERTY(int returnCode       READ getReturnCode   WRITE setReturnCode        NOTIFY returnCodeChanged)

public:
    explicit WindowBackend(QObject *parent = nullptr);
    Q_INVOKABLE virtual void show(void);
    Q_INVOKABLE virtual void cancel(void);
    Q_INVOKABLE virtual void accept(void);

    virtual bool getShown() const { return m_shown; }
    virtual void setShown(bool newShown)
    {
        if (m_shown == newShown) return;
        m_shown = newShown;
        emit shownChanged();
    }

    virtual int getReturnCode() const { return m_returnCode; }
    virtual void setReturnCode(int newReturnCode)
    {
        if (m_returnCode == newReturnCode) return;
        m_returnCode = newReturnCode;
        emit returnCodeChanged();
    }

signals:
    void shownChanged();
    void returnCodeChanged();

protected:
    bool m_shown = false;
    int m_returnCode = 0;

};

inline void WindowBackend::show()
{
    setReturnCode(0);
    setShown(true);
}

inline void WindowBackend::cancel()
{
    setReturnCode(-1);
    setShown(false);
    RuntimeData::get()->windowLockSet(false);
}

inline void WindowBackend::accept()
{
    setReturnCode(1);
    setShown(false);
    RuntimeData::get()->windowLockSet(false);
}

#endif // WINDOWBACKEND_H
