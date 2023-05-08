import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls.Styles 1.4

import Theme 1.0
import Config 1.0
import Network 1.0

import "widgets" as Widgets
import "layouts" as Layouts
import "tabs" as Tabs

Window { id: window_root;
    Material.theme: Material.Dark;
    Material.accent: Theme.color("color1");
    Material.primary: Theme.color("accent");
    Material.foreground: Theme.color("light0");
    Material.background: Theme.color("dark1");

    title: "СПО РЛС «‎Квазар»";
    width: 1280;
    height: 720;
    visible: true;
    color: Theme.color("dark0");
    Component.onCompleted: showMaximized();

    Item { id: root;
        anchors.fill: parent;

        property bool b_ConsoleShown: true;
        property string s_FontMain: font_Main.name;

        FontLoader { id: font_Main; source: "qrc:/fonts/Overpass.ttf"; }

        Widgets.DebugConsole { id: c_DebugConsole;
            enabled: root.b_ConsoleShown;
            visible: root.b_ConsoleShown;
        }
        DropShadow { z: 99; anchors.fill: c_DebugConsole; horizontalOffset: 1; verticalOffset: 12; radius: 16;
                     samples: 32; color: "#80000000"; source: c_DebugConsole; cached: true; enabled: root.b_ConsoleShown;
                     visible: root.b_ConsoleShown; }

        Layouts.BottomBar { id: layout_BottomBar;
            height: 46;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
        }
        DropShadow { z: 99; anchors.fill: layout_BottomBar; horizontalOffset: 1; verticalOffset: -12; radius: 16;
                         samples: 32; color: "#80000000"; source: layout_BottomBar; cached: true; }

        TabBar { id: control_TabBar;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.top: parent.top;
            contentHeight: 25;
            background: Rectangle { color: Material.background; }
            z: 50;

            TabButton {
                text: "ИНТЕРАКТИВНАЯ КАРТА";
                font.family: root.s_FontMain;
                font.weight: Font.Bold;
            }

            TabButton {
                text: "РЕДАКТИРОВАНИЕ ИЗОБРАЖЕНИЙ";
                font.family: root.s_FontMain;
                font.weight: Font.Bold;
            }

            TabButton {
                text: "СЕТЕВЫЕ ПОДКЛЮЧЕНИЯ";
                font.family: root.s_FontMain;
                font.weight: Font.Bold;
            }

            TabButton {
                text: "НАСТРОЙКИ";
                font.family: root.s_FontMain;
                font.weight: Font.Bold;
            }
        }

        SwipeView { id: view_MainView;
            anchors.top: control_TabBar.bottom;
            anchors.bottom: layout_BottomBar.top;
            anchors.left: parent.left;
            anchors.right: parent.right;
            interactive: false;
            currentIndex: control_TabBar.currentIndex;

            Tabs.MapTab { id: c_MapTab; }
            Tabs.FocusTab { id: c_FocusTab; }
            Tabs.NetworkTab { id: c_NetworkTab; }
            Tabs.SettingsTab { id: c_SettingsTab; }
        }
    }
}
