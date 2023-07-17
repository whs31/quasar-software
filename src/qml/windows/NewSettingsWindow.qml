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

    ColumnLayout {
        spacing: 5

        RowLayout {
            Text {
                Layout.fillWidth: true
                text: "IP-адрес РЛС"
                color: ColorTheme.active.color(ColorTheme.Text)
                font { family: root.mainfont; weight: Font.DemiBold }
            }

            TextField {
                validator: RegExpValidator { regExp:  /^((?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){0,3}(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/ }
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                text: Settings.io.parameter("ip/de10")
                font { family: root.mainfont; weight: Font.Bold }
                onEditingFinished: Settings.setParameter("ip/de10", text)
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
