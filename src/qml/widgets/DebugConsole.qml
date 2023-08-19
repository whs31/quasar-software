import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15

import Terminals 1.0

Pane {
    id: control

    width: 600
    height: 400
    x: root.width / 3
    y: root.height / 3
    opacity: root.consoleshown ? 1 : 0
    z: 100
    clip: true

    Material.background: theme.crust
    Material.elevation: 200
    Component.onCompleted: DebugConsole.execute("help")

    layer.enabled: true
    layer.effect: DropShadow {
        samples: 16
        radius: 16
        horizontalOffset: 6
        verticalOffset: 6
        opacity: 0.5
    }

    Pane {
        id: header

        height: 32
        Material.background: theme.base
        Material.elevation: 20

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: -12
        }

        Text {
            id: title

            text: "КОНСОЛЬ РАЗРАБОТЧИКА"
            color: theme.subtext0
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
                width: 30
                height: 30
                Material.background: theme.red
                onPressed: root.consoleshown = false
            }
        }
    }

    ListView { id: scrollView;
        model: DebugConsole;
        interactive: true;
        clip: true;

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
                color: vbar.pressed ? theme.surface0 : theme.surface2
            }

        }

        delegate: Row {
            spacing: 5

            Text {
                property var colors: [
                    theme.subtext0,
                    theme.teal,
                    theme.peach,
                    theme.red,
                    theme.green,
                    theme.pink,
                    theme.text
                ]

                width: scrollView.width;
                text: message;
                font.family: root.monofont;
                color: colors[type]
                font.bold: true
                font.pixelSize: 12
                textFormat: Text.RichText
            }
        }

        onCountChanged: scrollView.ScrollBar.vertical.position = 1.0;
    }

    Rectangle {
        id: inputArea

        color: theme.base
        border.width: 0.5
        border.color: theme.surface0
        height: 28

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: -12
        }

        TextInput {
            anchors.fill: parent;
            anchors.leftMargin: 3;
            color: theme.text
            text: "";
            verticalAlignment: Text.AlignVCenter;
            selectByMouse: true;
            selectedTextColor: theme.base
            selectionColor: theme.yellow
            font.family: root.monofont;
            font.pixelSize: 13;
            onAccepted: {
                DebugConsole.execute(text);
                text = "";
            }
        }

        Rectangle { id: resizeButton;
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: 16;
            height: 16;
            color: theme.base

            // resize window mouse area
            MouseArea {
                property point offset: Qt.point(0, 0)

                anchors.fill: parent
                hoverEnabled: true
                onPressed: {
                    parent.color = theme.surface0
                    offset = Qt.point(mouseX, mouseY);
                }
                onReleased: parent.color = theme.base
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

    Behavior on opacity { NumberAnimation { duration: 150; } }
}
