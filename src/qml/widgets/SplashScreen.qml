import QtQuick 2.15
import Theme 1.0

Rectangle {
    property bool smooth_startup: true;
    enabled: true;
    opacity: enabled ? smooth_startup ? 0 : 1 : 0;
    color: ColorTheme.active.color(ColorTheme.Dark)

    Component.onCompleted: {
        smooth_startup = true;
        smooth_startup = false;
    }

    Behavior on opacity { NumberAnimation { duration: 300; easing.type: Easing.InOutQuad; } }

    Image { id: logo;
        width: 200;
        height: width;
        anchors.centerIn: parent;
        source: "qrc:/logo/logo_large_gray.png";

        NumberAnimation on rotation { from: 270; to: 0; easing.type: Easing.InOutSine; running: true; duration: 800; }
    }
}
