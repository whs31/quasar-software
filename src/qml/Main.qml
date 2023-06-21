import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Dialogs 1.3

import Theme 1.0
import Config 1.0
import Network 1.0
import Filesystem 1.0
import Images 1.0
import Offline 1.0
import ImageProcessing 1.0

import "widgets" as Widgets
import "layouts" as Layouts
import "tabs" as Tabs
import "windows" as Windows
import "widgets/tabbar" as NPM

ApplicationWindow  { id: window_root;
    Material.theme: Material.Dark;
    Material.accent: Theme.color("color1");
    Material.primary: Theme.color("accent");
    Material.foreground: Theme.color("light0");
    Material.background: Theme.color("dark1");

    title: "СПО РЛС «‎Квазар»";
    minimumWidth: 1280;
    minimumHeight: 720;
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

    FileDialog { id: window_ExportDialog;
        property string s_Url: window_ExportDialog.fileUrl;
        title: "Выберите каталог для экспорта";
        folder: Paths.imageCache();
        selectFolder: true;
        onAccepted: {
            console.log("[GUI] Selected folder " + window_ExportDialog.fileUrl);
            let b = ImagesModel.exportSelectedImages(fileUrl);
            if(!b)
                messagebox.open("Нет экспортируемых РЛИ", "Вы не отметили для экспорта ни одного изображения с карты. Пожалуйста, отметьте изображения для экспорта.", "warn");
        }
        onRejected: {
            console.log("[GUI] Folder selection cancelled");
        }
    }

    Loader {
        anchors.fill: parent;
        active: true;
        asynchronous: true;
        sourceComponent: Item { id: root;
            anchors.fill: parent;
            layer.smooth: true;
            layer.samples: 8;
            layer.enabled: true;

            enum Tabs
            {
                MapView,
                EditorView,
                NetworkView
            }

            readonly property int tab: control_TabBar.currentIndex;
            function openTab(i)
            {
                control_TabBar.currentIndex = i;
                console.log("[GUI] Opening tab " + (i + 1));
            }

            property bool consoleshown: false;
            property bool vt100termshown: false;
            property string mainfont: font_Main.name;
            property string monofont: font_Mono.name;

            FontLoader { id: font_Main; source: "qrc:/fonts/Overpass.ttf"; }
            FontLoader { id: font_Mono; source: "qrc:/fonts/UbuntuMono.ttf"; }

            property real tileloadprogress;
            Connections {
                target: TileLoader;
                function onProgress(a) {
                    tileloadprogress = a;
                }
            }

            Widgets.DebugConsole { id: debugConsole; enabled: root.consoleshown; }
            Widgets.SARConsole { id: sarConsole; enabled: root.vt100termshown; }
            Widgets.ProgressPopup { anchors.centerIn: parent; progress: Network.tcpProgress; z: 100;
                text: "Загрузка изображения по TCP-IP";
            }
            Widgets.ProgressPopup { anchors.centerIn: parent; progress: ImageProcessing.progress; z: 100;
                text: "Обработка изображений";
            }
            Widgets.ProgressPopup { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter; progress: tileloadprogress; z: 100;
                text: "Загрузка оффлайн-карт";
            }

            Windows.InfoWindow { id: c_InfoWindow; z: 98; anchors.centerIn: root; }
            Windows.MessageWindow { id: messagebox; anchors.centerIn: parent; z: 99; }
            Windows.DialogWindow { id: dialogwindow; anchors.centerIn: parent; z: 99; }
            Windows.MarkerWindow { id: markerwindow; anchors.centerIn: parent; z: 97; }
            Windows.SettingsWindow { id: c_SettingsWindow; visible: false; }
            Windows.StripMatrixWindow { id: window_StripMatrix; visible: false; }

            Layouts.BottomBar { id: layout_BottomBar;
                height: 46;
                anchors {
                    left: parent.left;
                    right: parent.right;
                    bottom: parent.bottom;
                }
            }

            NPM.ExpandableTabBar { id: control_TabBar;
                z: 100;
                contentHeight: 25;
                anchors {
                    left: parent.left;
                    right: parent.right;
                    top: parent.top;
                }

                NPM.ExpandableTabButton {
                    text: "ИНТЕРАКТИВНАЯ КАРТА";
                    font {
                        family: root.mainfont
                    }

                    icon.source: "qrc:/icons/google-material/earth.png";
                    palette {
                        buttonText: Theme.color("light0");
                        highlight: Theme.color("dark3");
                        highlightedText: Theme.color("light0");
                    }
                }

                NPM.ExpandableTabButton {
                    text: "РЕДАКТИРОВАНИЕ ИЗОБРАЖЕНИЙ";
                    font {
                        family: root.mainfont
                    }
                    icon.source: "qrc:/icons/google-material/edit.png";
                    palette {
                        buttonText: Theme.color("light0");
                        highlight: Theme.color("yellow");
                        highlightedText: Theme.color("dark2");
                    }
                    enabled: c_FocusTab.currentAssignedIndex >= 0;
                }

                NPM.ExpandableTabButton {
                    text: "СЕТЕВЫЕ ПОДКЛЮЧЕНИЯ";
                    font {
                        family: root.mainfont
                    }
                    icon.source: "qrc:/icons/google-material/link.png";
                    palette {
                        buttonText: Theme.color("light0");
                        highlight: Theme.color("color3");
                        highlightedText: Theme.color("dark2");
                    }
                }
            }

            SwipeView { id: view_MainView;
                anchors {
                    top: control_TabBar.bottom;
                    bottom: layout_BottomBar.top;
                    left: parent.left;
                    right: parent.right;
                }
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
}
