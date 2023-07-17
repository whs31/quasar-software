import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15

import Theme 1.0
import Config 1.0

Pane {
    id: control
    property bool shown: false
    property bool valid: true

    opacity: shown ? 0.9 : 0;
    Behavior on opacity { NumberAnimation { duration: 300; } }
    enabled: shown;

    layer.enabled: true
    layer.effect: DropShadow {
        samples: 16
        radius: 16
        horizontalOffset: 6
        verticalOffset: 6
        opacity: 0.5
    }

    component ConfigIPv4Input: RowLayout {
        property string description: "None"
        property string key: "null/null"

        Text {
            Layout.fillWidth: true
            text: description + ":"
            color: ColorTheme.active.color(ColorTheme.Text)
            font { family: root.mainfont; weight: Font.DemiBold }
        }

        TextField {
            validator: RegExpValidator { regExp:  /^((?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){0,3}(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/ }
            selectByMouse: true
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            text: Settings.io.parameter(key)
            font { family: root.mainfont; weight: Font.Bold }
            onEditingFinished: Settings.setParameter(key, text)
        }
    }

    component SectionSeparator: Rectangle {
        property string description: "Header description"
        Layout.fillWidth: true
        Layout.fillHeight: true
        color: ColorTheme.active.color(ColorTheme.Surface)
        width: parent.width
        height: 20
        radius: 10

        Text {
            anchors.fill: parent
            text: description
            color: ColorTheme.active.color(ColorTheme.Text)
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 15 }
            horizontalAlignment: Text.AlignHCenter
        }
    }

    ColumnLayout {
        spacing: 5

        Text {
            text: "НАСТРОЙКИ ПРОГРАММЫ"
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 17 }
            color: ColorTheme.active.color(ColorTheme.Text)
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
        }

        ScrollView {
            id: scrollview
            Layout.fillHeight: true
            Layout.fillWidth: true
            implicitHeight: 500;
            implicitWidth: parent.width;
            clip: true;
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn;
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff;

            ColumnLayout {
                width: scrollview.width - 30;

                SectionSeparator { description: "Сетевые настройки" }

                ConfigIPv4Input { description: "IP-адрес РЛС"; key: "ip/de10" }
                ConfigIPv4Input { description: "IP-адрес АРМ"; key: "ip/computer" }
                ConfigIPv4Input { description: "IP-адрес вычислителя"; key: "ip/jetson" }
                ConfigIPv4Input { description: "IP-адрес навигации"; key: "ip/navigation" }
                ConfigIPv4Input { description: "IP-адрес коммутатора антенн"; key: "ip/com1" }
                ConfigIPv4Input { description: "IP-адрес коммутатора питания"; key: "ip/com2" }
            }
        }

        Row {
            id: dialog_buttons

            RoundButton {
                id: button_Save
                enabled: control.valid

                width: 200
                height: 44
                radius: 4

                font {
                    family: root.mainfont
                    weight: Font.Bold
                }

                Material.elevation: 30
                Material.background: ColorTheme.active.color(ColorTheme.BaseShade)

                text: "Сохранить"
                onPressed: {
                    Settings.save()
                    shown = false
                }
            }

            RoundButton {
                id: button_Cancel

                width: 200
                height: 44
                radius: 4

                font {
                    family: root.mainfont
                    weight: Font.Bold
                }

                Material.elevation: 30
                Material.background: ColorTheme.active.color(ColorTheme.BaseShade)

                text: "Отменить"
                onPressed: {
                    Settings.revert()
                    shown = false
                }
            }
        }
    }
}
