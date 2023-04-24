import QtQuick 2.15
import Theme 1.0

import "topbar" as Top

Rectangle {
    color: Theme.color("dark1");

    Top.Header { id: c_TopBarHeader;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        width: 255;
    }
}
