#pragma once

#include <definitions.h>
#include <QtQuick/QQuickPaintedItem>

class ProgressBar : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString errorColor READ errorColor WRITE setErrorColor NOTIFY errorColorChanged)
    Q_PROPERTY(QString warnColor READ warnColor WRITE setWarnColor NOTIFY warnColorChanged)
    Q_PROPERTY(QString successColor READ successColor WRITE setSuccessColor NOTIFY successColorChanged)
    Q_PROPERTY(QString backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)



    public:
        ProgressBar(QQuickItem* parent = nullptr);
        void paint(QPainter* painter) override;

        __getter QString errorColor() const;
        __setter void setErrorColor(const QString& other);

        __getter QString warnColor() const;
        __setter void setWarnColor(const QString& other);

        __getter QString successColor() const;
        __setter void setSuccessColor(const QString& other);

        __getter QString backgroundColor() const;
        __setter void setBackgroundColor(const QString& other);

        __getter int value() const;
        __setter void setValue(int other);

        signals:
            __signal errorColorChanged();
            __signal warnColorChanged();
            __signal successColorChanged();
            __signal valueChanged();
            __signal backgroundColorChanged();

    private:
        QString m_errorColor = "#ff0000";
        QString m_warnColor = "#ffff00";
        QString m_successColor = "#00ff00";
        QString m_backgroundColor = "#ffffff";
        int m_value;
};
