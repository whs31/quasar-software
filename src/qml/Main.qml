import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

import Theme 1.0
import Config 1.0
import Network 1.0
import ImGUI 1.0

import "widgets" as Widgets
import "layouts" as Layouts
import "tabs" as Tabs

Window { id: root;
    property bool b_ConsoleShown: true;

    width: 640;
    height: 480;
    visible: true;
    color: Theme.color("dark0");

    onVisibilityChanged: {
        if(visibility !== 3)
            showFullScreen();
    }

    Component.onCompleted: {
        showFullScreen();
    }

    FontLoader { id: font_Medium; source: "qrc:/fonts/SofiaSans-Medium.ttf"; }
    FontLoader { id: font_SemiBold; source: "qrc:/fonts/SofiaSans-SemiBold.ttf"; }
    FontLoader { id: font_Bold; source: "qrc:/fonts/SofiaSans-Bold.ttf"; }
    FontLoader { id: font_ExtraBold; source: "qrc:/fonts/SofiaSans-ExtraBold.ttf"; }
    FontLoader { id: font_Main; source: "qrc:/fonts/Overpass.ttf"; }

    property string s_FontMedium: font_Medium.name;
    property string s_FontSemiBold: font_SemiBold.name;
    property string s_FontBold: font_Bold.name;
    property string s_FontExtraBold: font_ExtraBold.name;
    property string s_FontMain: font_Main.name;

    Widgets.DebugConsole { id: c_DebugConsole;
        enabled: b_ConsoleShown;
        visible: b_ConsoleShown;
    }
    DropShadow { z: 99; anchors.fill: c_DebugConsole; horizontalOffset: 12; verticalOffset: 12; radius: 16;
                     samples: 32; color: "#80000000"; source: c_DebugConsole; cached: true; visible: b_ConsoleShown; }


    Layouts.TopBar { id: c_TopBar;
        height: 70;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
    }

    Layouts.TabSwitcher { id: c_TabBar;
        height: 20;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: c_TopBar.bottom;
    }
    DropShadow { z: 99; anchors.fill: c_TabBar; horizontalOffset: 1; verticalOffset: 12; radius: 16;
                     samples: 32; color: "#80000000"; source: c_TabBar; cached: true; }

    Layouts.BottomBar { id: c_BottomBar;
        height: 46;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
    }
    DropShadow { z: 99; anchors.fill: c_BottomBar; horizontalOffset: 1; verticalOffset: -12; radius: 16;
                     samples: 32; color: "#80000000"; source: c_BottomBar; cached: true; }

    // tabs

    Tabs.MapTab { id: c_MapTab;
        anchors.top: c_TabBar.bottom;
        anchors.bottom: c_BottomBar.top;
        anchors.left: parent.left;
        anchors.right: parent.right;

        opacity: c_TabBar.i_CurrentTab === 0;
        enabled: c_TabBar.i_CurrentTab === 0;
        Behavior on opacity { NumberAnimation { duration: 200; } }
    }

    Tabs.FocusTab { id: c_FocusTab;
        anchors.fill: c_MapTab;
        opacity: c_TabBar.i_CurrentTab === 1;
        enabled: c_TabBar.i_CurrentTab === 1;
        Behavior on opacity { NumberAnimation { duration: 200; } }
    }

    ImGUI { id: qa;
        objectName: "imgui1"
        anchors.fill: parent
        //focus: true // for keybord input
        // note that transforms other than 2D translation are NOT supported
    }
}
