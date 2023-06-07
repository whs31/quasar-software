import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Theme 1.0

Pane {
    property bool shown: false;
    property real pitch;
    property real roll;
    property real yaw;

    height: shown ? implicitHeight : 0;
    visible: height > 0;
    Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad; duration: 200; } }
    clip: true;
    Material.elevation: 30;

    Text {
        anchors.fill: parent;
        font {
            family: root.mainfont
            pixelSize: 15
            bold: true
        }
        color: Theme.color("orange");
        text: "Временно убрано в связи с реворком.";
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        wrapMode: Text.WordWrap;
    }
}
