import QtQuick 2.15
import Theme 1.0

import "bottombar" as Bottom

Rectangle {
    color: Theme.color("dark1");

    Bottom.StatusWidget {
        anchors.left: parent.left;
        anchors.leftMargin: 6;
        anchors.top: parent.top;
    }
}
