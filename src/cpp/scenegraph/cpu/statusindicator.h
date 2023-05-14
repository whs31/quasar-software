#pragma once

#include <QtQuick/QQuickPaintedItem>
#include <ccl/ccl_global.h>

class StatusIndicator : public QQuickPaintedItem
{
    Q_OBJECT
    PROPERTY_DEF(QString, errorColor, setErrorColor, m_errorColor)
    PROPERTY_DEF(QString, warnColor, setWarnColor, m_warnColor)
    PROPERTY_DEF(QString, successColor, setSuccessColor, m_successColor)
    PROPERTY_DEF(int, state, setState, m_state)

    public:
        StatusIndicator(QQuickItem* parent = nullptr);
        void paint(QPainter* painter) override;

        signals:
            void errorColorChanged();
            void warnColorChanged();
            void successColorChanged();
            void stateChanged();

    private:
        QString m_errorColor = "#ff0000";
        QString m_warnColor = "#ffff00";
        QString m_successColor = "#00ff00";
        int m_state;
};
