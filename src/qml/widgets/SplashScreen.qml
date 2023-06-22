import QtQuick 2.15
import Theme 1.0

Rectangle {
    enabled: true;
    opacity: enabled ? 1 : 0;
    color: Theme.color("dark0");

    Behavior on opacity { NumberAnimation { duration: 300; easing.type: Easing.InOutQuad; } }

    Image { id: logo;
        width: 200;
        height: width;
        anchors.centerIn: parent;
        source: "qrc:/logo/logo_large_gray.png";

        NumberAnimation on rotation { from: 180; to: 0; easing.type: Easing.InOutQuad; running: true; duration: 800; }
    }
}
