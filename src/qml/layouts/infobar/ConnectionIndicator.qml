import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import "../../widgets" as Widgets

Item {
    id: control
    required property bool offlineMode
    required property bool connected
    required property real delay

    width: childrenRect.width
    height: childrenRect.height

    RowLayout {
        spacing: -2

        function evaluateColor(mode, status, dl) {
            if(mode)
                return ColorTheme.active.color(ColorTheme.Rosewater)
            if(!status)
                return ColorTheme.active.color(ColorTheme.Red)
            if(dl > 3)
                return ColorTheme.active.color(ColorTheme.Yellow)
            return ColorTheme.active.color(ColorTheme.Green)
        }

        Button {
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
                    return "OFFL";
                if(!status)
                    return "DISC";
                if(dl > 3)
                    return "CONP";
                return "CONN";
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

            Layout.preferredWidth: 93

            Widgets.TT { txt: parent.evaluateTooltip(offlineMode, connected, control.delay) }
        }

        Button {
            flat: true
            font {
                pixelSize: 15
                weight: Font.Bold
            }
            text: offlineMode ? "------" : delay < 0.5 ? "~0.0 c" : delay > 100 ? "------" : Number(delay).toFixed(1) + " c"
            Material.foreground: parent.evaluateColor(offlineMode, connected, delay)
            Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }

            Layout.preferredWidth: 68

            Widgets.TT { txt: "Задержка между пакетами с РЛС" }
        }
    }
}
