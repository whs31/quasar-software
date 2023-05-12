#pragma once

#include <Definitions>
#include <QtQuick/QQuickPaintedItem>

class StatusIndicator : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString errorColor READ errorColor WRITE setErrorColor NOTIFY errorColorChanged)
    Q_PROPERTY(QString warnColor READ warnColor WRITE setWarnColor NOTIFY warnColorChanged)
    Q_PROPERTY(QString successColor READ successColor WRITE setSuccessColor NOTIFY successColorChanged)
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)

    public:
        StatusIndicator(QQuickItem* parent = nullptr);
        void paint(QPainter* painter) override;

        __getter QString errorColor() const;
        __setter void setErrorColor(const QString& other);

        __getter QString warnColor() const;
        __setter void setWarnColor(const QString& other);

        __getter QString successColor() const;
        __setter void setSuccessColor(const QString& other);

        __getter int state() const;
        __setter void setState(int other);

        signals:
            __signal errorColorChanged();
            __signal warnColorChanged();
            __signal successColorChanged();
            __signal stateChanged();

    private:
        QString m_errorColor = "#ff0000";
        QString m_warnColor = "#ffff00";
        QString m_successColor = "#00ff00";
        int m_state;
};
