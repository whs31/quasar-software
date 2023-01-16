import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Item {
    property string status: "EmptyStatustext";
    property color textcolor: "#dae1e5";
    property string prefix: "Статус чего-либо: ";

    width: childrenRect.width;

    Rectangle
    {
        id: bg;
        opacity: enabled ? 1 : 0;
        color: "#203a40";
        radius: 20;
        width: statusText.paintedWidth + 24;
        height: statusText.implicitHeight + 6;
        Text {
            id: statusText;
            text: prefix + status;
            font.capitalization: Font.MixedCase;
            font.pixelSize: 14;
            font.bold: true;
            color: textcolor;
            anchors.centerIn: parent;
            verticalAlignment: Text.AlignVCenter
            onTextChanged: {
                bg.opacity = 1;
                timer.restart();
            }
            
        }
        Behavior on opacity { NumberAnimation { duration: 200; } }
        Timer {
            id: timer;
            interval: 5000;
            running: true;
            repeat: false;
            onTriggered: {
                bg.opacity = 0;
            }
        }
    }
}
