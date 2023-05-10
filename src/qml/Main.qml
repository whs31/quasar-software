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
import Paths 1.0
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

    MessageDialog { id: messagebox_ErrorFetchingImages;
        Material.theme: Material.Dark;
        Material.accent: Theme.color("color1");
        Material.primary: Theme.color("accent");
        Material.foreground: Theme.color("light0");
        Material.background: Theme.color("dark1");

        title: "Не найдены изображения";
        text: "В целевой папке не найдены радиолокационные изображения.";
        standardButtons: StandardButton.Close;
        icon: StandardIcon.Warning;
    }

    FileDialog { id: window_FileDialog;
        property string s_Url: window_FileDialog.fileUrl;
        title: "Выберите каталог с радиолокационными изображениями";
        folder: Paths.imageCache();
        selectFolder: true;
        onAccepted: {
            console.log("[GUI] Selected folder " + window_FileDialog.fileUrl);
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
        property string s_FontMain: font_Main.name;
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

        Windows.SettingsWindow { id: c_SettingsWindow; visible: false; }

        Layouts.BottomBar { id: layout_BottomBar;
            height: 46;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
        }
        DropShadow { z: 99; anchors.fill: layout_BottomBar; horizontalOffset: 1; verticalOffset: -12; radius: 16;
                         samples: 32; color: "#80000000"; source: layout_BottomBar; cached: true; }

        Row { id: layout_TabBarButtons;
            anchors.right: parent.right;
            anchors.top: parent.top;
            anchors.rightMargin: -1;
            anchors.margins: -7;
            spacing: -5;

            RoundButton { id: button_Settings;
                font.family: root.s_FontMain;
                height: 40;
                radius: 4;
                icon.source: "qrc:/icons/tabs/settings.png";
                Material.elevation: 30;
                Material.background: Material.background;
                flat: true;
                onPressed: {
                    if(c_SettingsWindow.visible === true)
                        c_SettingsWindow.hide();
                    else
                        c_SettingsWindow.show();
                }
            }

            RoundButton { id: button_About;
                font.family: root.s_FontMain;
                height: 40;
                radius: 4;
                icon.source: "qrc:/icons/tabs/info.png";
                Material.elevation: 30;
                Material.background: Material.background;
                flat: true;
                onPressed: {
                    if(c_InfoWindow.b_Shown)
                        c_InfoWindow.b_Shown = false;
                    else
                        c_InfoWindow.b_Shown = true;
                }
            }
        }

        TabBar { id: control_TabBar;
            anchors.left: parent.left;
            anchors.right: layout_TabBarButtons.left;
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
