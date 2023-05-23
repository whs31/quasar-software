import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Dialogs

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

    FolderDialog { id: window_FileDialog;
        property string s_Url: window_FileDialog.fileUrl;
        title: "Выберите каталог с радиолокационными изображениями";
        currentFolder: Paths.imageCache();
        onAccepted: {
            console.log("[GUI] Selected folder " + window_FileDialog.selectedFolder);
            Config.storedCatalogue = selectedFolder;
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

        Windows.InfoWindow { id: c_InfoWindow; z: 98; anchors.centerIn: root; }
        Windows.MessageWindow { id: messagebox; anchors.centerIn: parent; z: 99; }
        Windows.DialogWindow { id: dialogwindow; anchors.centerIn: parent; z: 99; }
        Windows.MarkerWindow { id: markerwindow; anchors.centerIn: parent; z: 97; }
        Windows.SettingsWindow { id: c_SettingsWindow; visible: false; }
        Windows.StripMatrixWindow { id: window_StripMatrix; visible: false; }

        Layouts.BottomBar { id: layout_BottomBar;
            height: 46;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
        }

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
