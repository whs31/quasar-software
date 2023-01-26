import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import DynamicResolution 1.0
import RuntimeData 1.0

Item {
    property string status: "EmptyStatustext";
    property color label_color: "#FF0000";
    property int label_text_size: 12 * DynamicResolution.kh;
    property string label_text_family: "Helvetica [Cronyx]";

    width: statusText.paintedWidth + 5 * DynamicResolution.kw;
    height: statusText.paintedHeight + 5 * DynamicResolution.kh;

    Text {
        id: statusText;
        text: status;
        font.capitalization: Font.MixedCase;
        font.pixelSize: label_text_size;
        font.family: label_text_family;
        font.bold: true;
        color: label_color;
        opacity: 0;
        anchors.centerIn: parent;
        verticalAlignment: Text.AlignVCenter
        Behavior on opacity { NumberAnimation { duration: 300; } }
        property bool trigger: RuntimeData.statusPopupTrigger;
        onTriggerChanged: {
            if(trigger)
            {
                statusText.opacity = 1;
                timer.restart();
            }
        }
        Timer {
            id: timer;
            interval: 5000;
            running: true;
            repeat: false;
            onTriggered: {
                statusText.opacity = 0;
                RuntimeData.statusPopupTrigger = false;
            }
        }
    }

}
