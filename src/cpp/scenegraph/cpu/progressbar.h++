#pragma once

#include <Definitions>
#include <QtQuick/QQuickPaintedItem>

class ProgressBar : public QQuickPaintedItem
{
    Q_OBJECT
    PROPERTY_DEF(QString, errorColor, setErrorColor, m_errorColor)
    PROPERTY_DEF(QString, warnColor, setWarnColor, m_warnColor)
    PROPERTY_DEF(QString, successColor, setSuccessColor, m_successColor)
    PROPERTY_DEF(QString, backgroundColor, setBackgroundColor, m_backgroundColor)
    PROPERTY_DEF(int, value, setValue, m_value)

    public:
        ProgressBar(QQuickItem* parent = nullptr);
        void paint(QPainter* painter) override;

        signals:
            __property_signal errorColorChanged();
            __property_signal warnColorChanged();
            __property_signal successColorChanged();
            __property_signal valueChanged();
            __property_signal backgroundColorChanged();

    private:
        QString m_errorColor = "#ff0000";
        QString m_warnColor = "#ffff00";
        QString m_successColor = "#00ff00";
        QString m_backgroundColor = "#ffffff";
        int m_value;
};
