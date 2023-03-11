#ifndef APPLICATIONHEADER_H
#define APPLICATIONHEADER_H

#include <QObject>

#include "map/backend/signallinker.h"
#include "config/runtimedata.h"

class ApplicationHeader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool windowLockAlias           READ getWindowLockAlias        NOTIFY windowLockAliasChanged)
    Q_PROPERTY(QColor errorDarkAlias          READ getErrorDarkAlias         NOTIFY errorDarkAliasChanged)
    Q_PROPERTY(QColor primaryDarkAlias        READ getPrimaryDarkAlias       NOTIFY primaryDarkAliasChanged)
    Q_PROPERTY(QColor textWhiteAlias          READ getTextWhiteAlias         NOTIFY textWhiteAliasChanged)

public:
    explicit ApplicationHeader(QObject *parent = nullptr);
    Q_INVOKABLE void close(void);
    Q_INVOKABLE void minimize(void);
    Q_INVOKABLE void log(void);
    Q_INVOKABLE void settings(void);
    Q_INVOKABLE void info(void);
    Q_INVOKABLE void emulator(void);


    bool getWindowLockAlias() const;
    QColor getErrorDarkAlias() const;
    QColor getPrimaryDarkAlias() const;
    QColor getTextWhiteAlias() const;

signals:
    void windowLockAliasChanged();
    void errorDarkAliasChanged();
    void primaryDarkAliasChanged();
    void textWhiteAliasChanged();

private:

private slots:
    void emitWindowLockAliasChanged();

};

#endif // APPLICATIONHEADER_H
