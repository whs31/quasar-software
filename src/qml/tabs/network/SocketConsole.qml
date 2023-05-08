import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0

Page {
    property string name: "Socket Console";

    Material.elevation: 100;

    header: Rectangle {
        color: Theme.color("dark2");
        height: 24;

        Text {
            anchors.fill: parent;
            anchors.leftMargin: 3;
            text: name;
            font.family: root.mainfont;
            color: Theme.color("light0");
            font.bold: true;
            font.pixelSize: 15;
        }
    }

    Rectangle {
        color: Theme.color("dark1");
        anchors.fill: parent;
    }
}
