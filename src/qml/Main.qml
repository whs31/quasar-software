import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Dialogs 1.3

import QuaSAR.API 1.0

import Theme 1.0
import Config 1.0
import Filesystem 1.0
import Images 1.0
import Offline 1.0
import ImageProcessing 1.0

import "widgets" as Widgets
import "layouts" as Layouts
import "tabs" as Tabs
import "windows" as Windows

ApplicationWindow  { id: window_root;
    Material.theme: Material.Dark
    Material.accent: ColorTheme.active.color(ColorTheme.Primary)
    Material.primary: ColorTheme.active.color(ColorTheme.Accent)
    Material.foreground: ColorTheme.active.color(ColorTheme.Text)
    Material.background: ColorTheme.active.color(ColorTheme.BaseShade)

    title: "QuaSAR";
    minimumWidth: 1280;
    minimumHeight: 800;
    width: 1280;
    height: 800;
    visible: true;

    color: ColorTheme.active.color(ColorTheme.Dark)
    font.family: root.mainfont
    palette {
        alternateBase: ColorTheme.active.color(ColorTheme.BaseShade)
        base: ColorTheme.active.color(ColorTheme.Dark)
        brightText: ColorTheme.active.color(ColorTheme.Accent)
        button: ColorTheme.active.color(ColorTheme.Surface)
        buttonText: ColorTheme.active.color(ColorTheme.Text)
        dark: ColorTheme.active.color(ColorTheme.Dark)
        highlight: ColorTheme.active.color(ColorTheme.Primary)
        highlightedText: ColorTheme.active.color(ColorTheme.Dark)
        light: ColorTheme.active.color(ColorTheme.Overlay)
        link: ColorTheme.active.color(ColorTheme.PrimaryLight)
        linkVisited: ColorTheme.active.color(ColorTheme.Mauve)
        mid: ColorTheme.active.color(ColorTheme.BaseShade)
        midlight: ColorTheme.active.color(ColorTheme.Surface)
        shadow: "black"
        text: ColorTheme.active.color(ColorTheme.Text)
        toolTipBase: ColorTheme.active.color(ColorTheme.Dark)
        toolTipText: ColorTheme.active.color(ColorTheme.Subtext)
        window: ColorTheme.active.color(ColorTheme.Dark)
        windowText: ColorTheme.active.color(ColorTheme.Text)
    }

    Component.onCompleted: showMaximized();

    FileDialog {
        id: window_FileDialog
        property string s_Url: window_FileDialog.fileUrl
        title: "Выберите каталог с радиолокационными изображениями";
        folder: Paths.imageCache()
        selectFolder: true
        onAccepted: {
            console.log("[GUI] Selected folder " + window_FileDialog.fileUrl)
            Settings.setParameter("state/folder", fileUrl)
            Settings.save()
            Filesystem.fetchImageDirectory()
        }
        onRejected: console.log("[GUI] Folder selection cancelled");
    }

    FileDialog { id: window_ExportDialog
        property string s_Url: window_ExportDialog.fileUrl
        title: "Выберите каталог для экспорта"
        folder: Paths.imageCache()
        selectFolder: true
        onAccepted: {
            console.log("[GUI] Selected folder " + window_ExportDialog.fileUrl)
            let b = ImagesModel.exportSelectedImages(fileUrl)
            if(!b)
                messagebox.open("Нет экспортируемых РЛИ", "Вы не отметили для экспорта ни одного изображения с карты. Пожалуйста, отметьте изображения для экспорта.", "warn")
        }
        onRejected: {
            console.log("[GUI] Folder selection cancelled")
        }
    }

    Loader {
        anchors.fill: parent;
        active: !splashscreen.enabled;
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

            readonly property int tab: tabbar.currentIndex;
            function openTab(i)
                {
                tabbar.currentIndex = i;
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

            Layouts.BottomBar { id: layout_BottomBar;
                height: 46;
                anchors {
                    left: parent.left;
                    right: parent.right;
                    bottom: parent.bottom;
                }
            }

            TabBar { id: tabbar
                z: 100
                contentHeight: 40
                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                }
                Material.accent: ColorTheme.active.color(ColorTheme.Overlay)

                TabButton {
                    text: "Интерактивная карта"
                    font.family: root.mainfont
                    font.bold: true
                    icon.source: "qrc:/icons/vector/misc/earth.svg"
                    Material.accent: ColorTheme.active.color(ColorTheme.Green)
                }

                TabButton {
                    text: "Редактирование изображений"
                    font.family: root.mainfont
                    font.bold: true
                    icon.source: "qrc:/icons/vector/common/edit.svg"
                    Material.accent: ColorTheme.active.color(ColorTheme.Yellow)
                    enabled: c_FocusTab.currentAssignedIndex >= 0
                }

                TabButton {
                    text: "Сетевые подключения"
                    font.family: root.mainfont
                    font.bold: true
                    icon.source: "qrc:/icons/vector/network/wifi.svg"
                    Material.accent: ColorTheme.active.color(ColorTheme.PrimaryLight)
                }
            }

            SwipeView { id: view_MainView;
                anchors {
                    top: tabbar.bottom;
                    bottom: layout_BottomBar.top;
                    left: parent.left;
                    right: parent.right;
                }
                interactive: false;
                currentIndex: tabbar.currentIndex;
                contentWidth: view_MainView.width;
                contentHeight: view_MainView.height;

                Tabs.MapTab { id: c_MapTab; }
                Tabs.FocusTab { id: c_FocusTab; }
                Tabs.NetworkTab { id: c_NetworkTab; }
            }

            Widgets.DebugConsole { id: debugConsole; enabled: root.consoleshown; }
            Widgets.SARConsole { id: sarConsole; enabled: root.vt100termshown; }
            Widgets.ProgressPopup { anchors.centerIn: parent; progress: NetworkAPI.remote.downloadProgress; z: 100; text: "Загрузка изображения по TCP-IP"; }
            Widgets.ProgressPopup { anchors.centerIn: parent; progress: ImageProcessing.progress; z: 100; text: "Обработка изображений"; }
            Widgets.ProgressPopup { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter; progress: tileloadprogress; z: 100; text: "Загрузка оффлайн-карт"; }

            Windows.NewSettingsWindow { id: settingswindow; z: 99; anchors.centerIn: root; }
            Windows.InfoWindow { id: c_InfoWindow; z: 100; anchors.centerIn: root; }
            Windows.MessageWindow { id: messagebox; anchors.centerIn: parent; z: 99; }
            Windows.DialogWindow { id: dialogwindow; anchors.centerIn: parent; z: 99; }
            Windows.MarkerWindow { id: markerwindow; anchors.centerIn: parent; z: 97; }
            Windows.StripMatrixWindow { id: window_StripMatrix; visible: false; }
            Windows.UpdateWindow { id: updatewindow; anchors.centerIn: parent; z: 100; }
        }
    }

    Widgets.SplashScreen { id: splashscreen;
        anchors.fill: parent;
        enabled: true;

        Timer { interval: 800; repeat: false; running: true; onTriggered: splashscreen.enabled = false; }
    }
}
