#ifndef DIALOGWINDOWBACKEND_H
#define DIALOGWINDOWBACKEND_H

#include <QObject>
#include "config/runtimedata.h"

class DialogWindowBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString header       READ getHeader       WRITE setHeader            NOTIFY headerChanged)
    Q_PROPERTY(QString icon         READ getIcon         WRITE setIcon              NOTIFY iconChanged)
    Q_PROPERTY(QString text         READ getText         WRITE setText              NOTIFY textChanged)
    Q_PROPERTY(bool shown           READ getShown        WRITE setShown             NOTIFY shownChanged)
    Q_PROPERTY(int returnCode       READ getReturnCode   WRITE setReturnCode        NOTIFY returnCodeChanged)

public:
    static DialogWindowBackend* get(QObject* parent = nullptr);
    Q_INVOKABLE void show(void);

    QString getHeader() const;                          void setHeader(const QString &newHeader);
    QString getIcon() const;                            void setIcon(const QString &newIcon);
    QString getText() const;                            void setText(const QString &newText);
    bool getShown() const;                              void setShown(bool newShown);
    int getReturnCode() const;                          void setReturnCode(int newReturnCode);


signals:
    void headerChanged();
    void iconChanged();
    void textChanged();
    void shownChanged();
    void returnCodeChanged();

private:
    explicit DialogWindowBackend(QObject *parent = nullptr);
    static DialogWindowBackend* pointer;

    QString m_header = "Sample Header";
    QString m_icon = "qrc:/icons/debug.png";
    QString m_text = "Lorem ipsum";
    bool m_shown = false;
    int m_returnCode = 0;
};

#endif // DIALOGWINDOWBACKEND_H
