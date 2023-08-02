import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import "../../widgets" as Widgets

RowLayout {
    required property real latitude
    required property real longitude
    required property real altitude
    required property real seaAltitude
    required property real velocity
    required property real direction
    required property int satellitesCount
    property string private_LatSuffix: latitude > 0 ? "°N" : "°S"
    property string private_LonSuffix: longitude > 0 ? "°E" : "°W"

    ToolButton {
        flat: true
        icon {
            source: "qrc:/icons/vector/toolbar/coord.svg"
            color: ColorTheme.active.color(ColorTheme.Text)
        }

        font {
            pixelSize: 13
            weight: Font.Bold
        }
        text: Number(latitude).toFixed(7) + private_LatSuffix + " " + Number(longitude).toFixed(7) + private_LonSuffix
        Material.foreground: ColorTheme.active.color(ColorTheme.Text)
        Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }

        Layout.preferredWidth: 240

        Widgets.TT { txt: "Текущие GPS-координаты БПЛА" }
    }

    ToolButton {
        flat: true
        icon {
            source: "qrc:/icons/vector/network/altitude.svg"
            color: ColorTheme.active.color(ColorTheme.Text)
        }

        font {
            pixelSize: 13
            weight: Font.Bold
        }
        text: Number(altitude).toFixed(0) +  " м"
        Material.foreground: ColorTheme.active.color(ColorTheme.Text)
        Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }

        Layout.preferredWidth: 90

        Widgets.TT { txt: "Текущая относительная высота БПЛА" }
    }

    ToolButton {
        flat: true

        font {
            pixelSize: 13
            weight: Font.DemiBold
        }
        text: Number(seaAltitude).toFixed(0) + " м"
        Material.foreground: ColorTheme.active.color(ColorTheme.Subtext)
        Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }

        Layout.preferredWidth: 65

        Widgets.TT { txt: "Текущая абсолютная (над уровнем моря) высота БПЛА" }
    }

    ToolButton {
        flat: true
        icon {
            source: "qrc:/icons/vector/network/speed.svg"
            color: ColorTheme.active.color(ColorTheme.Text)
        }

        font {
            pixelSize: 13
            weight: Font.Bold
        }
        text: Number(velocity).toFixed(0)+  " км/ч"
        Material.foreground: ColorTheme.active.color(ColorTheme.Text)
        Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }

        Layout.preferredWidth: 120

        Widgets.TT { txt: "Текущая скорость БПЛА в километрах в час" }
    }

    ToolButton {
        flat: true
        icon {
            source: "qrc:/icons/vector/network/compass.svg"
            color: ColorTheme.active.color(ColorTheme.Text)
        }

        font {
            pixelSize: 13
            weight: Font.Bold
        }
        text: Number(direction).toFixed(1)+  "°"
        Material.foreground: ColorTheme.active.color(ColorTheme.Text)
        Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }

        Layout.preferredWidth: 100

        Widgets.TT { txt: "Текущий курс БПЛА относительно севера" }
    }

    ToolButton {
        flat: true
        icon {
            source: "qrc:/icons/vector/network/antenna.svg"
            color: ColorTheme.active.color(ColorTheme.Subtext)
        }

        font {
            pixelSize: 13
            weight: Font.DemiBold
        }
        text: Number(satellitesCount).toFixed(0)
        Material.foreground: ColorTheme.active.color(ColorTheme.Subtext)
        Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }

        Layout.preferredWidth: 60

        Widgets.TT { txt: "Текущее количество спутников навигации" }
    }
}

