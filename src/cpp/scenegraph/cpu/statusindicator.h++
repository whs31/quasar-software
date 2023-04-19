#pragma once

#include "definitions.h++"
#include <QtQuick/QQuickPaintedItem>

class StatusIndicator : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString errorColor READ errorColor WRITE setErrorColor NOTIFY errorColorChanged)
    Q_PROPERTY(QString warnColor READ warnColor WRITE setWarnColor NOTIFY warnColorChanged)
    Q_PROPERTY(QString successColor READ successColor WRITE setSuccessColor NOTIFY successColorChanged)
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)

    QString m_errorColor = "#ff0000";
    QString m_warnColor = "#ffff00";
    QString m_successColor = "#00ff00";
    int m_state;

    public:
        StatusIndicator(QQuickItem* parent = nullptr);
        void paint(QPainter* painter) override;

        QString errorColor() const;
        void setErrorColor(const QString& other);

        QString warnColor() const;
        void setWarnColor(const QString& other);

        QString successColor() const;
        void setSuccessColor(const QString& other);

        int state() const;
        void setState(int other);

        signals:
            __signal errorColorChanged();
            __signal warnColorChanged();
            __signal successColorChanged();
            __signal stateChanged();
};
