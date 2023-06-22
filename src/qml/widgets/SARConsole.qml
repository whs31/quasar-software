import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Terminals 1.0
import Network 1.0
import Theme 1.0

Pane { id: control;
    width: 600;
    height: 500;
    x: root.width / 2;
    y: root.height / 2;
    z: 100;
    clip: true;
    opacity: root.vt100termshown ? 1 : 0;

    Behavior on opacity { NumberAnimation { duration: 150; } }
    Material.background: Qt.darker(Theme.color("dark0"), 1.2);
    Material.elevation: 200;

    Pane { id: header;
        height: 32;
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: -12
        }

        Material.background: Theme.color("dark3");
        Material.elevation: 20;

        Text { id: title;
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

            text: "КОНСОЛЬ РЛС";
            color: Theme.color("light0");
            verticalAlignment: Text.AlignVCenter;
        }

        MouseArea { // move window mouse area
            anchors {
                fill: parent
                margins: -12
                rightMargin: 8
            }

            property point offset: Qt.point(0, 0);
            onPressed: offset = Qt.point(mouseX, mouseY);
            onPositionChanged: {
                if(pressed) {
                    let global_pos = mapToItem(root, mouseX, mouseY);
                    control.x = global_pos.x - offset.x;
                    control.y = global_pos.y - offset.y;
                }
            }
        }

        Row {
            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
                topMargin: -8;
                bottomMargin: -3;
            }

            RoundButton {
                width: 26;
                height: 26;
                Material.background: Theme.color("orange");
                Material.elevation: 100;
                onPressed: VT100Terminal.clear();
            }

            RoundButton {
                width: 26;
                height: 26;
                Material.background: Theme.color("red");
                onPressed: root.vt100termshown = false;
            }
        }
    }

    ListView { id: scrollView;
        model: VT100Terminal;
        anchors {
            left: parent.left
            right: parent.right
            top: header.bottom
            bottom: inputArea.top
        }

        interactive: true;
        clip: true;

        ScrollBar.vertical: ScrollBar { id: vbar;
            active: true;
            policy: ScrollBar.AlwaysOn
            contentItem: Rectangle {
                implicitWidth: 4;
                implicitHeight: 100;
                radius: width / 2;
                color: vbar.pressed ? Theme.color("dark3")
                                    : Theme.color("dark2");
            }
        }

        delegate: Row {
            spacing: 5;

            Text {
                text: message;
                font.family: root.monofont;
                color: text.charAt(0) === "%" ? Theme.color("color3")
                                              : Theme.color("light0");
                font.bold: true;
                font.pixelSize: 15;
                textFormat: Text.StyledText;
            }
        }

        onCountChanged: scrollView.ScrollBar.vertical.position = 1.0;
    }

    Rectangle { id: inputArea;
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: -12
        }

        height: 28;
        color: Theme.color("dark1");
        border.width: 0.5;
        border.color: Theme.color("dark2");

        TextInput { id: input;
            anchors.fill: parent;
            anchors.leftMargin: 3;
            color: Theme.color("color0");
            text: "$";
            verticalAlignment: Text.AlignVCenter;
            selectByMouse: true;
            selectedTextColor: Theme.color("dark0");
            selectionColor: Theme.color("yellow");
            font.family: root.monofont;
            font.pixelSize: 14;
            onAccepted: {
                Network.executeString(text);
                text = "$";
            }
        }

        Text {
            anchors.fill: input;
            verticalAlignment: Text.AlignVCenter;
            font.family: root.monofont;
            font.pixelSize: 14;
            color: Theme.color("light0");
            text: input.text.length < 2 ? "  Введите команду для РЛС..." : "";
        }

        Rectangle { id: resizeButton;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
            width: 16;
            height: 16;
            color: Theme.color("dark1");

            MouseArea { // resize window mouse area
                property point offset: Qt.point(0, 0);
                anchors.fill: parent;
                hoverEnabled: true;
                onPressed: {
                    parent.color = Theme.color("dark2");
                    offset = Qt.point(mouseX, mouseY);
                }
                onReleased: parent.color = Theme.color("dark1");
                onPositionChanged: {
                    if(pressed) {
                        let global_pos = mapToItem(control, mouseX, mouseY);
                        control.width = global_pos.x - offset.x;
                        control.height = global_pos.y - offset.y;
                    }
                }
            }

            Image {
                source: "qrc:/icons/console/handle.png";
                anchors.centerIn: parent;
            }
        }
    }
}
