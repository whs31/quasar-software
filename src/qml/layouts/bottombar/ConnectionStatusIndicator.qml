import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import Theme 1.0

Rectangle { id: control
    required property bool connected

    color: ColorTheme.active.color(ColorTheme.Dark)
    radius: height / 2

    RowLayout {
        anchors {
            fill: parent
            leftMargin: height / 3
        }

        Rectangle { id: indicator
            Layout.alignment: Qt.AlignVCenter
            height: control.height / 3
            width: height
            radius: height / 2
            color: connected ? ColorTheme.active.color(ColorTheme.Green)
                             : ColorTheme.active.color(ColorTheme.Red)

            SequentialAnimation {
                NumberAnimation {
                    target: indicator
                    property: "opacity"
                    from: 0
                    to: 1
                    duration: 500
                }

                NumberAnimation {
                    target: indicator
                    property: "opacity"
                    from: 1
                    to: 0
                    duration: 500
                }

                loops: Animation.Infinite;
                running: true;
            }
        }

        Text {
            Layout.fillWidth: true
            height: control.height
            color: connected ? ColorTheme.active.color(ColorTheme.Green)
                             : ColorTheme.active.color(ColorTheme.Red)
            font {
                weight: Font.ExtraBold
                family: root.mainfont
                pixelSize: 15
                capitalization: Font.AllUppercase
            }
            text: connected ? "Подключено к РЛС" : "Нет подключения к РЛС"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }
}
