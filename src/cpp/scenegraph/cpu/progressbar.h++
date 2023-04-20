#pragma once

#include "definitions.h++"
#include <QtQuick/QQuickPaintedItem>

class ProgressBar : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString errorColor READ errorColor WRITE setErrorColor NOTIFY errorColorChanged)
    Q_PROPERTY(QString warnColor READ warnColor WRITE setWarnColor NOTIFY warnColorChanged)
    Q_PROPERTY(QString successColor READ successColor WRITE setSuccessColor NOTIFY successColorChanged)
    Q_PROPERTY(QString backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)

    QString m_errorColor = "#ff0000";
    QString m_warnColor = "#ffff00";
    QString m_successColor = "#00ff00";
    QString m_backgroundColor = "#ffffff";
    int m_value;

    public:
        ProgressBar(QQuickItem* parent = nullptr);
        void paint(QPainter* painter) override;

        QString errorColor() const;
        void setErrorColor(const QString& other);

        QString warnColor() const;
        void setWarnColor(const QString& other);

        QString successColor() const;
        void setSuccessColor(const QString& other);

        QString backgroundColor() const;
        void setBackgroundColor(const QString& other);

        int value() const;
        void setValue(int other);

        signals:
            __signal errorColorChanged();
            __signal warnColorChanged();
            __signal successColorChanged();
            __signal valueChanged();
            __signal backgroundColorChanged();
};
