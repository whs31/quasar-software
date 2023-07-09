import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15
import QuaSAR.API 1.0
import QuaSAR.API.Extras 1.0
import Theme 1.0

Pane {
    id: control

    width: 600
    height: 500
    x: root.width / 2
    y: root.height / 2
    z: 100
    clip: true
    opacity: root.vt100termshown ? 1 : 0
    Material.background: Qt.darker(ColorTheme.active.color(ColorTheme.Dark), 1.2)
    Material.elevation: 200
    layer.enabled: true

    Pane {
        id: header

        height: 32
        Material.background: ColorTheme.active.color(ColorTheme.Surface)
        Material.elevation: 20

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: -12
        }

        Text {
            id: title

            text: "КОНСОЛЬ РЛС"
            color: ColorTheme.active.color(ColorTheme.Subtext)
            verticalAlignment: Text.AlignVCenter

            anchors {
                left: parent.left
                leftMargin: 5
                verticalCenter: parent.verticalCenter
                verticalCenterOffset: 2
            }

            font {
                family: root.mainfont
                pixelSize: 14
                bold: true
            }

        }

        // move window mouse area
        MouseArea {
            property point offset: Qt.point(0, 0)

            onPressed: offset = Qt.point(mouseX, mouseY)
            onPositionChanged: {
                if (pressed) {
                    let global_pos = mapToItem(root, mouseX, mouseY);
                    control.x = global_pos.x - offset.x;
                    control.y = global_pos.y - offset.y;
                }
            }

            anchors {
                fill: parent
                margins: -12
                rightMargin: 8
            }

        }

        Row {
            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
                topMargin: -10
                bottomMargin: -3
            }

            RoundButton {
                height: 30
                Material.background: ColorTheme.active.color(ColorTheme.Orange)
                Material.foreground: ColorTheme.active.color(ColorTheme.Dark)
                Material.elevation: 100
                text: "Очистка"
                onPressed: NetworkOutput.clear()
            }

            RoundButton {
                width: 30
                height: 30
                Material.background: ColorTheme.active.color(ColorTheme.Red)
                onPressed: root.vt100termshown = false
            }

        }

    }

    ListView {
        id: scrollView

        model: NetworkOutput
        interactive: true
        clip: true
        onCountChanged: {
            scrollView.ScrollBar.vertical.position = 1;
            console.error(count);
        }

        anchors {
            left: parent.left
            right: parent.right
            top: header.bottom
            bottom: inputArea.top
        }

        ScrollBar.vertical: ScrollBar {
            id: vbar

            active: true
            policy: ScrollBar.AlwaysOn

            contentItem: Rectangle {
                implicitWidth: 4
                implicitHeight: 100
                radius: width / 2
                color: vbar.pressed ? ColorTheme.active.color(ColorTheme.Overlay) : ColorTheme.active.color(ColorTheme.Surface)
            }

        }

        delegate: Row {
            required property int index
            required property string message
            required property int type

            spacing: 5

            Text {
                text: message
                width: scrollView.width
                font.family: root.monofont
                color: text.charAt(0) === "%" ? ColorTheme.active.color(ColorTheme.PrimaryLightest) : ColorTheme.active.color(ColorTheme.Text)
                font.bold: true
                font.pixelSize: 15
                wrapMode: Text.WordWrap
            }

        }

    }

    Rectangle {
        id: inputArea

        height: 28
        color: ColorTheme.active.color(ColorTheme.BaseShade)
        border.width: 0.5
        border.color: ColorTheme.active.color(ColorTheme.Surface)

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: -12
        }

        TextInput {
            id: input

            anchors.fill: parent
            anchors.leftMargin: 3
            color: ColorTheme.active.color(ColorTheme.PrimaryDark)
            text: "$"
            verticalAlignment: Text.AlignVCenter
            selectByMouse: true
            selectedTextColor: ColorTheme.active.color(ColorTheme.Dark)
            selectionColor: ColorTheme.active.color(ColorTheme.Yellow)
            font.family: root.monofont
            font.pixelSize: 14
            onAccepted: {
                NetworkAPI.execute(text);
                text = "$";
            }
        }

        Text {
            anchors.fill: input
            verticalAlignment: Text.AlignVCenter
            font.family: root.monofont
            font.pixelSize: 14
            color: ColorTheme.active.color(ColorTheme.Text)
            text: input.text.length < 2 ? "  Введите команду для РЛС..." : ""
        }

        Rectangle {
            id: resizeButton

            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: 16
            height: 16
            color: ColorTheme.active.color(ColorTheme.BaseShade)

            // resize window mouse area
            MouseArea {
                property point offset: Qt.point(0, 0)

                anchors.fill: parent
                hoverEnabled: true
                onPressed: {
                    parent.color = ColorTheme.active.color(ColorTheme.Surface);
                    offset = Qt.point(mouseX, mouseY);
                }
                onReleased: parent.color = ColorTheme.active.color(ColorTheme.BaseShade)
                onPositionChanged: {
                    if (pressed) {
                        let global_pos = mapToItem(control, mouseX, mouseY);
                        control.width = global_pos.x - offset.x;
                        control.height = global_pos.y - offset.y;
                    }
                }
            }

            Image {
                source: "qrc:/icons/console/handle.png"
                anchors.centerIn: parent
            }

        }

    }

    Behavior on opacity {
        NumberAnimation {
            duration: 150
        }

    }

    layer.effect: DropShadow {
        samples: 16
        radius: 16
        horizontalOffset: 6
        verticalOffset: 6
        opacity: 0.5
    }

}
