import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0

import "bottombar" as Bottom

Rectangle {
    color: Theme.color("dark1");

    Bottom.StatusWidget { id: c_StatusWidget;
        anchors.left: parent.left;
        anchors.leftMargin: 6;
        anchors.top: parent.top;
    }

    Flickable {
        anchors.left: c_StatusWidget.right;
        anchors.leftMargin: 16;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: button_ToggleDebug.left;
        anchors.rightMargin: 100;
        clip: true;
        interactive: true;
        contentWidth: c_InfoPanel.width;
        flickableDirection: Flickable.HorizontalFlick;

        Bottom.InfoPanel { id: c_InfoPanel; }
    }

    RoundButton { id: button_ToggleDebug;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        height: 40;
        width: 40;
        radius: 4;
        icon.source: "qrc:/icons/bottombar/console.png";
        onPressed: root.b_ConsoleShown = !root.b_ConsoleShown;
    }
}
