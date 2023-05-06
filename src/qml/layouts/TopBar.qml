import QtQuick 2.15
import Theme 1.0

import "topbar" as Top

Rectangle {
    color: Theme.color("dark1");

//    Top.Header { id: c_TopBarHeader;
//        anchors.top: parent.top;
//        anchors.bottom: parent.bottom;
//        anchors.right: parent.right;
//        width: 255;
//    }

    Top.MapToolbar { id: c_TopBarMap;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.right: c_TopBarHeader.left;

        visible: root.i_CurrentTabAlias === 0;
        enabled: visible;
    }
}
