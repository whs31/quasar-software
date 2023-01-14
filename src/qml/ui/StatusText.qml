import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Item {
    property string status: "EmptyStatustext";
    property color textcolor: "#dae1e5";
    property string prefix: "Статус чего-либо: ";

    width: childrenRect.width;

    Text {
        id: statusText;
        text: prefix + status;
        font.capitalization: Font.MixedCase;
        font.pixelSize: 11;
        font.bold: true;
        color: textcolor;
        opacity: enabled ? 1 : 0
        verticalAlignment: Text.AlignVCenter
        onTextChanged: {
            statusText.opacity = 1;
            timer.restart();
        }
        Behavior on opacity { NumberAnimation { duration: 200; } }
        Timer {
            id: timer;
            interval: 5000;
            running: true;
            repeat: false;
            onTriggered: {
                statusText.opacity = 0;
            }
        }
    }
}
