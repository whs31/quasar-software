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

    property bool lightmode: false
    property QtObject theme: QtObject {
        property color rosewater: lightmode ? Catpuccin.latte.rosewater.hex : Catpuccin.mocha.rosewater.hex
        property color flamingo: lightmode ? Catpuccin.latte.flamingo.hex : Catpuccin.mocha.flamingo.hex
        property color pink: lightmode ? Catpuccin.latte.pink.hex : Catpuccin.mocha.pink.hex
        property color mauve: lightmode ? Catpuccin.latte.mauve.hex : Catpuccin.mocha.mauve.hex
        property color red: lightmode ? Catpuccin.latte.red.hex : Catpuccin.mocha.red.hex
        property color maroon: lightmode ? Catpuccin.latte.maroon.hex : Catpuccin.mocha.maroon.hex
        property color peach: lightmode ? Catpuccin.latte.peach.hex : Catpuccin.mocha.peach.hex
        property color yellow: lightmode ? Catpuccin.latte.yellow.hex : Catpuccin.mocha.yellow.hex
        property color green: lightmode ? Catpuccin.latte.green.hex : Catpuccin.mocha.green.hex
        property color teal: lightmode ? Catpuccin.latte.teal.hex : Catpuccin.mocha.teal.hex
        property color sky: lightmode ? Catpuccin.latte.sky.hex : Catpuccin.mocha.sky.hex
        property color sapphire: lightmode ? Catpuccin.latte.sapphire.hex : Catpuccin.mocha.sapphire.hex
        property color blue: lightmode ? Catpuccin.latte.blue.hex : Catpuccin.mocha.blue.hex
        property color lavender: lightmode ? Catpuccin.latte.lavender.hex : Catpuccin.mocha.lavender.hex
        property color text: lightmode ? Catpuccin.latte.text.hex : Catpuccin.mocha.text.hex
        property color subtext1: lightmode ? Catpuccin.latte.subtext1.hex : Catpuccin.mocha.subtext1.hex
        property color subtext0: lightmode ? Catpuccin.latte.subtext0.hex : Catpuccin.mocha.subtext0.hex
        property color overlay2: lightmode ? Catpuccin.latte.overlay2.hex : Catpuccin.mocha.overlay2.hex
        property color overlay1: lightmode ? Catpuccin.latte.overlay1.hex : Catpuccin.mocha.overlay1.hex
        property color overlay0: lightmode ? Catpuccin.latte.overlay0.hex : Catpuccin.mocha.overlay0.hex
        property color surface2: lightmode ? Catpuccin.latte.surface2.hex : Catpuccin.mocha.surface2.hex
        property color surface1: lightmode ? Catpuccin.latte.surface1.hex : Catpuccin.mocha.surface1.hex
        property color surface0: lightmode ? Catpuccin.latte.surface0.hex : Catpuccin.mocha.surface0.hex
        property color base: lightmode ? Catpuccin.latte.base.hex : Catpuccin.mocha.base.hex
        property color mantle: lightmode ? Catpuccin.latte.mantle.hex : Catpuccin.mocha.mantle.hex
        property color crust: lightmode ? Catpuccin.latte.crust.hex : Catpuccin.mocha.crust.hex

        Behavior on rosewater { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on flamingo { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on pink { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on mauve { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on red { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on maroon { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on peach { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on yellow { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on green { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on teal { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on sky { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on blue { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on lavender { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on text { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on subtext1 { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on subtext0 { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on overlay2 { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on overlay1 { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on overlay0 { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on surface2 { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on surface1 { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on surface0 { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on base { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on mantle { ColorAnimation { easing.type: Easing.InOutQuad } }
        Behavior on crust { ColorAnimation { easing.type: Easing.InOutQuad } }
    }

    Material.theme: lightmode ? Material.Light : Material.Dark
    Material.accent: theme.sapphire
    Material.primary: theme.mauve
    Material.foreground: theme.text
    Material.background: theme.base

    title: "QuaSAR"
    minimumWidth: 1280
    minimumHeight: 800
    width: 1280
    height: 800
    visible: true
    color: theme.crust
    font.family: root.mainfont
    Component.onCompleted: showMaximized()

    palette {
        alternateBase: theme.mantle
        base: theme.base
        brightText: theme.mauve
        button: theme.surface0
        buttonText: theme.text
        dark: theme.crust
        highlight: theme.teal
        highlightedText: theme.crust
        light: theme.overlay0
        link: theme.teal
        linkVisited: theme.sapphire
        mid: theme.surface1
        midlight: theme.surface2
        shadow: "black"
        text: theme.text
        toolTipBase: theme.crust
        toolTipText: theme.subtext1
        window: theme.base
        windowText: theme.text
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
            Material.background: theme.base
            action: openSidePanelAction

            anchors {
                left: parent.left
                leftMargin: 0
                top: parent.top
                topMargin: -6
            }

            icon {
                source: "qrc:/icons/vector/common/list.svg"
                color: theme.text
            }

        }

        TabBar {
            id: tabbar

            z: 100
            contentHeight: 40
            Material.accent: theme.mantle
            Material.background: theme.mantle

            anchors {
                left: sidepanelButton.right
                right: parent.right
                top: parent.top
            }

            TabButton {
                text: "Интерактивная карта"
                font.bold: true
                icon.source: "qrc:/icons/vector/misc/earth.svg"
                Material.accent: theme.green
            }

            TabButton {
                text: "Редактирование изображений"
                font.bold: true
                icon.source: "qrc:/icons/vector/common/edit.svg"
                Material.accent: theme.peach
                enabled: c_FocusTab.currentAssignedIndex >= 0
            }

            TabButton {
                text: "Сетевые подключения"
                font.bold: true
                icon.source: "qrc:/icons/vector/network/wifi.svg"
                Material.accent: theme.red
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

    menuBar: Layouts.MenuHeader { }

    footer: Layouts.InfoBar {
        id: infobar

        Material.primary: theme.base
    }
}
