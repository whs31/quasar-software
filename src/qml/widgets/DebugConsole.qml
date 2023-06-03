import QtQuick 2.15
import QtQuick.Controls 2.15
import ConsoleWidget 1.0
import Theme 1.0

Rectangle { id: control;
    width: 600;
    height: 400;
    x: 150;
    y: 300; // относительно верхнего левого
    color: Theme.color("dark0");
    border.width: 0.5;
    border.color: Theme.color("dark2");
    z: 100;
    clip: true;

    Connections
    {
        target: Impl;
        function onAppendSignal(text)
        {
            textArea.append(text);
        }
    }
    Rectangle { id: header;
        height: 20;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
        color: Theme.color("dark3");

        Image { id: title;
            source: "qrc:/icons/console/header.png";
            anchors.left: parent.left;
            anchors.leftMargin: 5;
            anchors.verticalCenter: parent.verticalCenter;
        }

        MouseArea { // move window mouse area
            anchors.fill: parent;
            anchors.rightMargin: 20;
            property point offset: Qt.point(0, 0);
            onPressed: {
                parent.color = Theme.color("dark2");
                offset = Qt.point(mouseX, mouseY);
            }
            onReleased: {
                parent.color = Theme.color("dark3");
            }
            onPositionChanged: {
                if(pressed) {
                    let global_pos = mapToItem(root, mouseX, mouseY);
                    control.x = global_pos.x - offset.x;
                    control.y = global_pos.y - offset.y;
                }
            }
        }

        Rectangle { id: closeButton;
            anchors.right: parent.right;
            anchors.top: parent.top;
            width: 20;
            height: 20;
            color: Theme.color("dark3");

            MouseArea { // close window mouse area
                anchors.fill: parent;
                hoverEnabled: true;
                onEntered: parent.color = Theme.color("red");
                onExited: parent.color = Theme.color("dark3");
                onClicked: {
                    root.b_ConsoleShown = false;
                }
            }

            Image {
                source: "qrc:/icons/console/cross.png";
                anchors.centerIn: parent;
            }
        }
    }

    ScrollView { id: scrollView;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: header.bottom;
        anchors.bottom: inputArea.top;
        anchors.leftMargin: 5;

        TextArea { id: textArea;
            color: Theme.color("light0");
            background: Rectangle{
                color: Theme.color("dark0");
            }
            text: "[CONSOLE] Beginning logging...";
            selectByMouse: true;
            readOnly: true;
            selectedTextColor: Theme.color("dark0");
            selectionColor: Theme.color("accent");
            textFormat: Text.RichText;
            font.family: root.monofont;
            font.pixelSize: 13;
            wrapMode: Text.WordWrap;
            function append(strAdd)
            {
                textArea.text = textArea.text + strAdd;
                textArea.cursorPosition = textArea.length - 1;
            }
        }
    }

    Rectangle { id: inputArea;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        height: 28;
        color: Theme.color("dark1");
        border.width: 0.5;
        border.color: Theme.color("dark2");

        TextInput {
            anchors.fill: parent;
            anchors.leftMargin: 3;
            color: Theme.color("light1");
            text: "";
            verticalAlignment: Text.AlignVCenter;
            selectByMouse: true;
            selectedTextColor: Theme.color("dark0");
            selectionColor: Theme.color("yellow");
            font.family: root.monofont;
            font.pixelSize: 13;
            onAccepted:
            {
                Impl.sendCommand(text);
                text = "";
            }
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
