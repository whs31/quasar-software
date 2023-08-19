import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.15
import QuaSAR.API 1.0
import Config 1.0
import Filesystem 1.0
import Images 1.0
import Offline 1.0
import "widgets" as Widgets
import "layouts" as Layouts
import "tabs" as Tabs
import "windows" as Windows
import "qrc:/js/catpuccin.js" as Catpuccin

ApplicationWindow {
    id: window_root

    Material.theme: Material.Dark
    Material.accent: Catpuccin.mocha.sapphire.hex
    Material.primary: Catpuccin.mocha.mauve.hex
    Material.foreground: Catpuccin.mocha.text.hex
    Material.background: Catpuccin.mocha.base.hex
    title: "QuaSAR"
    minimumWidth: 1280
    minimumHeight: 800
    width: 1280
    height: 800
    visible: true
    color: Catpuccin.mocha.crust.hex
    font.family: root.mainfont
    Component.onCompleted: showMaximized()

    palette {
        alternateBase: Catpuccin.mocha.mantle.hex
        base: Catpuccin.mocha.base.hex
        brightText: Catpuccin.mocha.mauve.hex
        button: Catpuccin.mocha.surface0.hex
        buttonText: Catpuccin.mocha.text.hex
        dark: Catpuccin.mocha.crust.hex
        highlight: Catpuccin.mocha.teal.hex
        highlightedText: Catpuccin.mocha.crust.hex
        light: Catpuccin.mocha.overlay0.hex
        link: Catpuccin.mocha.teal.hex
        linkVisited: Catpuccin.mocha.sapphire.hex
        mid: Catpuccin.mocha.surface1.hex
        midlight: Catpuccin.mocha.surface2.hex
        shadow: "black"
        text: Catpuccin.mocha.text.hex
        toolTipBase: Catpuccin.mocha.crust.hex
        toolTipText: Catpuccin.mocha.subtext1.hex
        window: Catpuccin.mocha.base.hex
        windowText: Catpuccin.mocha.text.hex
    }

    Layouts.SidePanel {
        id: sidepanel

        y: menuBar.height + tabbar.height
        width: parent.width * 0.33
        height: parent.height - y
    }

    FileDialog {
        id: window_FileDialog

        property string s_Url: window_FileDialog.fileUrl

        title: "Выберите каталог с радиолокационными изображениями"
        folder: Paths.imageCache()
        selectFolder: true
        onAccepted: {
            console.log("[GUI] Selected folder " + window_FileDialog.fileUrl);
            Settings.setParameter("state/folder", fileUrl);
            Settings.save();
            Filesystem.fetchImageDirectory();
        }
        onRejected: console.log("[GUI] Folder selection cancelled")
    }

    FileDialog {
        id: window_ExportDialog

        property string s_Url: window_ExportDialog.fileUrl

        title: "Выберите каталог для экспорта"
        folder: Paths.imageCache()
        selectFolder: true
        onAccepted: {
            console.log("[GUI] Selected folder " + window_ExportDialog.fileUrl);
            let b = ImagesModel.exportSelectedImages(fileUrl);
            if (!b)
                messagebox.open("Нет экспортируемых РЛИ", "Вы не отметили для экспорта ни одного изображения с карты. Пожалуйста, отметьте изображения для экспорта.", "warn");

        }
        onRejected: {
            console.log("[GUI] Folder selection cancelled");
        }
    }

    Item {
        id: root

        enum Tabs {
            MapView,
            EditorView,
            NetworkView
        }

        readonly property int tab: tabbar.currentIndex
        property bool consoleshown: false
        property bool vt100termshown: false
        property string mainfont: font_Main.name
        property string monofont: font_Mono.name
        property real tileloadprogress: 0

        function openTab(i) {
            tabbar.currentIndex = i;
            console.log("[GUI] Opening tab " + (i + 1));
        }

        anchors.fill: parent
        visible: !splashscreen.enabled

        layer {
            smooth: true
            samples: 8
            enabled: true
        }

        FontLoader {
            id: font_Main

            source: "qrc:/fonts/Overpass.ttf"
        }

        FontLoader {
            id: font_Mono

            source: "qrc:/fonts/UbuntuMono.ttf"
        }

        Connections {
            function onProgress(a) {
                root.tileloadprogress = a;
            }

            target: TileLoader
        }

        Action {
            id: openSidePanelAction

            shortcut: "Ctrl+P"
            onTriggered: {
                if (!sidepanel.opened)
                    sidepanel.open();
                else
                    sidepanel.close();
            }
        }

        Button {
            id: sidepanelButton

            z: 100
            width: 52
            height: 52
            Material.background: Catpuccin.mocha.base.hex
            action: openSidePanelAction

            anchors {
                left: parent.left
                leftMargin: 0
                top: parent.top
                topMargin: -6
            }

            icon {
                source: "qrc:/icons/vector/common/list.svg"
                color: Catpuccin.mocha.text.hex
            }

        }

        TabBar {
            id: tabbar

            z: 100
            contentHeight: 40
            Material.accent: Catpuccin.mocha.surface0.hex
            Material.background: Catpuccin.mocha.surface0.hex

            anchors {
                left: sidepanelButton.right
                right: parent.right
                top: parent.top
            }

            TabButton {
                text: "Интерактивная карта"
                font.bold: true
                icon.source: "qrc:/icons/vector/misc/earth.svg"
                Material.accent: Catpuccin.mocha.green.hex
            }

            TabButton {
                text: "Редактирование изображений"
                font.bold: true
                icon.source: "qrc:/icons/vector/common/edit.svg"
                Material.accent: Catpuccin.mocha.peach.hex
                enabled: c_FocusTab.currentAssignedIndex >= 0
            }

            TabButton {
                text: "Сетевые подключения"
                font.bold: true
                icon.source: "qrc:/icons/vector/network/wifi.svg"
                Material.accent: Catpuccin.mocha.red.hex
            }

        }

        SwipeView {
            id: view_MainView

            interactive: false
            currentIndex: tabbar.currentIndex
            contentWidth: view_MainView.width
            contentHeight: view_MainView.height

            anchors {
                top: tabbar.bottom
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }

            Tabs.MapTab {
                id: c_MapTab
            }

            Tabs.FocusTab {
                id: c_FocusTab
            }

            Tabs.NetworkTab {
                id: c_NetworkTab
            }

        }

        Widgets.DebugConsole {
            id: debugConsole

            enabled: root.consoleshown
        }

        Widgets.SARConsole {
            id: sarConsole

            enabled: root.vt100termshown
        }

        Widgets.ProgressPopup {
            anchors.centerIn: parent
            progress: NetworkAPI.remote.downloadProgress
            z: 100
            text: "Загрузка изображения по TCP-IP"
        }

        Widgets.ProgressPopup {
            anchors.centerIn: parent
            progress: ImageProcessing.progress
            z: 100
            text: "Обработка изображений"
        }

        Widgets.ProgressPopup {
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            progress: root.tileloadprogress
            z: 100
            text: "Загрузка оффлайн-карт"
        }

        Windows.InfoWindow {
            id: c_InfoWindow

            z: 100
            anchors.centerIn: root
        }

        Windows.MessageWindow {
            id: messagebox

            anchors.centerIn: parent
            z: 99
        }

        Windows.DialogWindow {
            id: dialogwindow

            anchors.centerIn: parent
            z: 99
        }

        Windows.MarkerWindow {
            id: markerwindow

            anchors.centerIn: parent
            z: 97
        }

        Windows.UpdateWindow {
            id: updatewindow

            anchors.centerIn: parent
            z: 100
        }

    }

    Widgets.SplashScreen {
        id: splashscreen

        anchors.fill: parent
        enabled: true

        Timer {
            interval: 800
            repeat: false
            running: true
            onTriggered: splashscreen.enabled = false
        }

    }

    menuBar: Layouts.MenuHeader {
    }

    footer: Layouts.InfoBar {
        id: infobar

        Material.primary: Catpuccin.mocha.base.hex
    }

}
