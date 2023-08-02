import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Dialogs
import QtQuick.Layouts

import QuaSAR.API 1.0

import Theme 1.0
import Config 1.0
import Filesystem 1.0
import Images 1.0
import Offline 1.0

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
    Material.roundedScale: Material.ExtraSmallScale
    Material.containerStyle: Material.Filled

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

    menuBar: Layouts.MenuHeader { }

    footer: Layouts.InfoBar {
        id: infobar
        Material.primary: ColorTheme.active.color(ColorTheme.BaseShade)
    }

    Layouts.SidePanel {
        id: sidepanel
        y: menuBar.height + tabbar.height
        width: parent.width * 0.33
        height: parent.height - y
    }

    FolderDialog {
        id: window_FileDialog
        property string s_Url: window_FileDialog.selectedFolder
        title: "Выберите каталог с радиолокационными изображениями";
        currentFolder: Paths.imageCache()
        onAccepted: {
            console.log("[GUI] Selected folder " + window_FileDialog.selectedFolder)
            Settings.setParameter("state/folder", selectedFolder)
            Settings.save()
            Filesystem.fetchImageDirectory()
        }
        onRejected: console.log("[GUI] Folder selection cancelled");
    }

    FolderDialog { id: window_ExportDialog
        property string s_Url: window_ExportDialog.selectedFolder
        title: "Выберите каталог для экспорта"
        currentFolder: Paths.imageCache()
        onAccepted: {
            console.log("[GUI] Selected folder " + window_ExportDialog.selectedFolder)
            let b = ImagesModel.exportSelectedImages(selectedFolder)
            if(!b)
                messagebox.open("Нет экспортируемых РЛИ", "Вы не отметили для экспорта ни одного изображения с карты. Пожалуйста, отметьте изображения для экспорта.", "warn")
        }
        onRejected: {
            console.log("[GUI] Folder selection cancelled")
        }
    }

    Item { id: root;
        anchors.fill: parent;
        layer {
            smooth: true
            samples: 8
            enabled: true
        }
        visible: !splashscreen.enabled

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

        property bool consoleshown: false
        property bool vt100termshown: false
        property string mainfont: font_Main.name
        property string monofont: font_Mono.name

        FontLoader { id: font_Main; source: "qrc:/fonts/Overpass.ttf"; }
        FontLoader { id: font_Mono; source: "qrc:/fonts/UbuntuMono.ttf"; }

        property real tileloadprogress: 0
        Connections {
            target: TileLoader;
            function onProgress(a) {
                root.tileloadprogress = a;
            }
        }

        Action {
            id: openSidePanelAction
            shortcut: "Ctrl+P"
            onTriggered: {
                if(!sidepanel.opened)
                    sidepanel.open()
                else
                    sidepanel.close()
            }
        }

        ToolButton {
            id: sidepanelButton
            z: 100
            anchors {
                left: parent.left
                leftMargin: 0
                top: parent.top
                topMargin: -6
            }

            icon {
                source: "qrc:/icons/vector/common/list.svg"
                color: ColorTheme.active.color(ColorTheme.Text)
            }

            width: 52
            height: 52
            display: AbstractButton.IconOnly

            Material.roundedScale: Material.NotRounded
            Material.containerStyle: Material.Filled
            action: openSidePanelAction
        }

        Rectangle {
            color: ColorTheme.active.color(ColorTheme.BaseShade)
            anchors {
                left: parent.left
                leftMargin: 0
                top: parent.top
                topMargin: -6
            }
            height: 52
            width: 52
        }

        TabBar { id: tabbar
            z: 100
            contentHeight: 40
            anchors {
                left: sidepanelButton.right
                right: parent.right
                top: parent.top
            }
            Material.accent: ColorTheme.active.color(ColorTheme.Overlay)

            TabButton {
                text: "Интерактивная карта"
                font.bold: true
                icon.source: "qrc:/icons/vector/misc/earth.svg"
                Material.accent: ColorTheme.active.color(ColorTheme.Green)
            }

            TabButton {
                text: "Редактирование изображений"
                font.bold: true
                icon.source: "qrc:/icons/vector/common/edit.svg"
                Material.accent: ColorTheme.active.color(ColorTheme.Yellow)
                enabled: c_FocusTab.currentAssignedIndex >= 0
            }

            TabButton {
                text: "Сетевые подключения"
                font.bold: true
                icon.source: "qrc:/icons/vector/network/wifi.svg"
                Material.accent: ColorTheme.active.color(ColorTheme.PrimaryLight)
            }
        }

        SwipeView {
            id: view_MainView
            anchors {
                top: tabbar.bottom
                bottom: parent.bottom
                left: parent.left
                right: parent.right
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
        Widgets.ProgressPopup { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter; progress: root.tileloadprogress; z: 100; text: "Загрузка оффлайн-карт"; }

        Windows.InfoWindow { id: c_InfoWindow; z: 100; anchors.centerIn: root; }
        Windows.MessageWindow { id: messagebox; anchors.centerIn: parent; z: 99; }
        Windows.DialogWindow { id: dialogwindow; anchors.centerIn: parent; z: 99; }
        Windows.MarkerWindow { id: markerwindow; anchors.centerIn: parent; z: 97; }
        Windows.UpdateWindow { id: updatewindow; anchors.centerIn: parent; z: 100; }
    }


    Widgets.SplashScreen { id: splashscreen;
        anchors.fill: parent;
        enabled: true;

        Timer { interval: 800; repeat: false; running: true; onTriggered: splashscreen.enabled = false; }
    }
}
