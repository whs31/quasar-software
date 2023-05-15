import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.3

import Theme 1.0
import Config 1.0
import Network 1.0
import Filesystem 1.0

import "widgets" as Widgets
import "layouts" as Layouts
import "tabs" as Tabs
import "windows" as Windows

ApplicationWindow  { id: window_root;
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

    FileDialog { id: window_FileDialog;
        property string s_Url: window_FileDialog.fileUrl;
        title: "Выберите каталог с радиолокационными изображениями";
        folder: Paths.imageCache();
        selectFolder: true;
        onAccepted: {
            console.log("[GUI] Selected folder " + window_FileDialog.fileUrl);
            Config.storedCatalogue = fileUrl;
            Filesystem.fetchImageDirectory();
        }
        onRejected: {
            console.log("[GUI] Folder selection cancelled");
        }
    }

    Item { id: root;
        anchors.fill: parent;
        layer.smooth: true;
        layer.samples: 6;
        layer.enabled: true;

        property bool b_ConsoleShown: true;
        property bool b_AllowImageEdit: false;
        property string mainfont: font_Main.name;
        property string monofont: font_Mono.name;

        FontLoader { id: font_Main; source: "qrc:/fonts/Overpass.ttf"; }
        FontLoader { id: font_Mono; source: "qrc:/fonts/UbuntuMono.ttf"; }

        Widgets.DebugConsole { id: c_DebugConsole;
            enabled: root.b_ConsoleShown;
            visible: root.b_ConsoleShown;
        }
        DropShadow { z: 99; anchors.fill: c_DebugConsole; horizontalOffset: 1; verticalOffset: 12; radius: 16;
                     samples: 32; color: "#80000000"; source: c_DebugConsole; cached: true; enabled: root.b_ConsoleShown;
                     visible: root.b_ConsoleShown; }

        Windows.InfoWindow { id: c_InfoWindow; z: 98; anchors.centerIn: root; }
        DropShadow { z: 98; anchors.fill: c_InfoWindow; horizontalOffset: 1; verticalOffset: 12; radius: 16;
                     samples: 32; color: "#80000000"; source: c_InfoWindow; cached: true; enabled: c_InfoWindow.b_Shown;
                     visible: c_InfoWindow.b_Shown; }

        Windows.MessageWindow { id: messagebox; anchors.centerIn: parent; z: 99; }
        DropShadow { z: 98; anchors.fill: messagebox; horizontalOffset: 1; verticalOffset: 12; radius: 16;
                     samples: 32; color: "#80000000"; source: messagebox; cached: true; enabled: messagebox.b_Shown;
                     visible: messagebox.b_Shown; }

        Windows.DialogWindow { id: dialogwindow; anchors.centerIn: parent; z: 99; }
        DropShadow { z: 98; anchors.fill: dialogwindow; horizontalOffset: 1; verticalOffset: 12; radius: 16;
                     samples: 32; color: "#80000000"; source: dialogwindow; cached: true; enabled: dialogwindow.b_Shown;
                     visible: dialogwindow.b_Shown; }

        Windows.MarkerWindow { id: markerwindow; anchors.centerIn: parent; z: 97; }
        DropShadow { z: 96; anchors.fill: markerwindow; horizontalOffset: 1; verticalOffset: 12; radius: 16;
                     samples: 32; color: "#80000000"; source: markerwindow; cached: true; enabled: markerwindow.b_Shown;
                     visible: markerwindow.b_Shown; }

        Windows.SettingsWindow { id: c_SettingsWindow; visible: false; }

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
                font.family: root.mainfont;
                font.weight: Font.Bold;
            }

            TabButton {
                text: "РЕДАКТИРОВАНИЕ ИЗОБРАЖЕНИЙ";
                font.family: root.mainfont;
                font.weight: Font.Bold;
                enabled: root.b_AllowImageEdit;
            }

            TabButton {
                text: "СЕТЕВЫЕ ПОДКЛЮЧЕНИЯ";
                font.family: root.mainfont;
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
            contentWidth: view_MainView.width;
            contentHeight: view_MainView.height;

            Tabs.MapTab { id: c_MapTab; }
            Tabs.FocusTab { id: c_FocusTab; }
            Tabs.NetworkTab { id: c_NetworkTab; }
        }
    }
}
