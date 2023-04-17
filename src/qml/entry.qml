import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

import Theme 1.0

import "widgets" as Widgets
import "layouts" as Layouts
import "tabs" as Tabs

Window { id: root;
    width: 640;
    height: 480;
    visible: true;
    Component.onCompleted: showFullScreen();
    color: Theme.color("dark0");

    Widgets.DebugConsole { id: c_DebugConsole; }
    DropShadow { z: 99; anchors.fill: c_DebugConsole; horizontalOffset: 12; verticalOffset: 12; radius: 16;
                     samples: 32; color: "#30000000"; source: c_DebugConsole; cached: true; }


    Layouts.TopBar { id: c_TopBar;
        height: 70;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
    }

    Layouts.TabSwitcher { id: c_TabBar;
        height: 24;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: c_TopBar.bottom;
    }
    DropShadow { z: 99; anchors.fill: c_TabBar; horizontalOffset: 1; verticalOffset: 12; radius: 16;
                     samples: 32; color: "#30000000"; source: c_TabBar; cached: true; }

    Layouts.BottomBar { id: c_BottomBar;
        height: 40;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
    }
    DropShadow { z: 99; anchors.fill: c_BottomBar; horizontalOffset: 1; verticalOffset: -12; radius: 16;
                     samples: 32; color: "#30000000"; source: c_BottomBar; cached: true; }
}
