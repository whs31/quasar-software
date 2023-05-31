import QtQuick 2.15
import Theme 1.0

Rectangle {
    radius: 10;

    property bool shown: false;
    property real pitch;
    property real roll;
    property real yaw;

    height: shown ? implicitHeight : 0;
    visible: height > 0;
    Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad; duration: 200; } }
    clip: true;

    Rectangle { color: parent.color; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom; height: 10; }
}
