import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import "../../widgets" as Widgets

RowLayout {
    spacing: 0
    id: control
    required property bool offlineMode
    required property bool connected
    required property real delay

    function evaluateColor(mode, status, dl) {
        if(mode)
            return theme.rosewater
        if(!status)
            return theme.red
        if(dl > 3)
            return theme.yellow
        return theme.green
    }

    ToolButton {
        function evaluateIcon(mode, status, dl) {
            if(mode)
                return "qrc:/icons/vector/network/signal-offline.svg";
            if(!status)
                return "qrc:/icons/vector/network/signal-none.svg";
            if(dl > 3)
                return "qrc:/icons/vector/network/signal-medium.svg";
            return "qrc:/icons/vector/network/signal-good.svg";
        }

        function evaluateText(mode, status, dl) {
            if(mode)
                return "ОФФЛАЙН";
            if(!status)
                return "ОТКЛЮЧЕНО";
            if(dl > 3)
                return "ПЛОХОЕ СОЕДИНЕНИЕ";
            return "ПОДКЛЮЧЕНО";
        }

        function evaluateTooltip(mode, status, dl) {
            if(mode)
                return "Программа работает в оффлайн-режиме";
            if(!status)
                return "Отсутствует соединение с РЛС";
            if(dl > 3)
                return "Плохое соединение с РЛС: высокая задержка";
            return "Соединение с РЛС успешно установлено";
        }

        flat: true
        icon {
            source: evaluateIcon(offlineMode, connected, delay)
            color: parent.evaluateColor(offlineMode, connected, delay)
        }

        font {
            pixelSize: 16
            weight: Font.ExtraBold
        }

        text: evaluateText(offlineMode, connected, delay)
        Material.foreground: parent.evaluateColor(offlineMode, connected, delay)
        Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }

        Layout.fillWidth: true

        Widgets.TT { txt: parent.evaluateTooltip(offlineMode, connected, control.delay) }
    }

    ToolButton {
        flat: true
        font {
            pixelSize: 15
            weight: Font.Bold
        }
        enabled: !offlineMode
        text: offlineMode ? "------" : delay < 0.5 ? "~0.0 c" : delay > 100 ? "------" : Number(delay).toFixed(1) + " c"
        Material.foreground: parent.evaluateColor(offlineMode, connected, delay)
        Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }

        implicitWidth: enabled ? 68 : 0

        Widgets.TT { txt: "Задержка между пакетами с РЛС" }
    }

    ConnectButton { }
}
