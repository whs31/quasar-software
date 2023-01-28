#ifndef DIALOGWINDOWBACKEND_H
#define DIALOGWINDOWBACKEND_H

#include <QObject>
#include "abstract/windowbackend.h"

class DialogWindowBackend : public WindowBackend
{
    Q_OBJECT
    Q_PROPERTY(QString header       READ getHeader       WRITE setHeader            NOTIFY headerChanged)
    Q_PROPERTY(QString icon         READ getIcon         WRITE setIcon              NOTIFY iconChanged)
    Q_PROPERTY(QString text         READ getText         WRITE setText              NOTIFY textChanged)

public:
    static DialogWindowBackend* get(QObject* parent = nullptr);

    QString getHeader() const;                          void setHeader(const QString &newHeader);
    QString getIcon() const;                            void setIcon(const QString &newIcon);
    QString getText() const;                            void setText(const QString &newText);

signals:
    void headerChanged();
    void iconChanged();
    void textChanged();

private:
    explicit DialogWindowBackend(QObject *parent = nullptr);
    static DialogWindowBackend* pointer;

    QString m_header = "Sample Header";
    QString m_icon = "qrc:/icons/debug.png";
    QString m_text = "Lorem ipsum";
};

#endif // DIALOGWINDOWBACKEND_H
