import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Ruler 1.0
import ClickHandler 1.0
import Filesystem 1.0
import Config 1.0
import Images 1.0
import Network 1.0
import Markers 1.0

import "map" as MapTab;
import "../widgets" as Widgets;

Map { id: c_Map;
    property int i_MapMode: 1; // { 0 - offline, 5 - schema, 4 - hybrid, 1 - sattelite }
    property bool b_ShowGrid: false;
    property bool b_ShowTrack: true;
    property bool b_ShowDiagram: true;
    property bool b_ShowCursorCoords: true;

    Component.onDestruction: {
        Config.storedLatitude = center.latitude;
        Config.storedLongitude = center.longitude;
        Config.storedZoomLevel = zoomLevel;
    }

    tilt: 15;
    //gesture.acceptedGestures: MapGestureArea.PanGesture | MapGestureArea.PinchGesture;
    plugin: Plugin {
        name: "osm";

        PluginParameter {
            name: "osm.mapping.providersrepository.address";
            value: "file:///" + Paths.mapConfig();
        }

        Component.onCompleted: console.info("[MAP] Using osmconfig: " + Paths.mapConfig());
    }

    activeMapType: c_Map.supportedMapTypes[i_MapMode];
    center: QtPositioning.coordinate(Config.storedLatitude, Config.storedLongitude);
    gesture.acceptedGestures: MapGestureArea.PanGesture | MapGestureArea.PinchGesture;
    zoomLevel: Config.storedZoomLevel;
    copyrightsVisible: false;
    z: 0;
    Behavior on center { CoordinateAnimation { duration: 250; easing.type: Easing.InOutQuad; } }

    MouseArea { id: c_MapMouseArea;
        hoverEnabled: true;
        anchors.fill: parent;
        acceptedButtons: Qt.LeftButton | Qt.RightButton;

        onClicked: {
            if(ClickHandler.state === ClickHandler.RulerActive)
            {
                if(mouse.button === Qt.LeftButton)
                    c_RulerModel.insertPoint(c_Map.toCoordinate(Qt.point(mouseX, mouseY)), 0);
                if(mouse.button === Qt.RightButton)
                    c_RulerModel.resetRoute();
            }
            else if(ClickHandler.state === ClickHandler.MarkerActive)
            {
                if(mouse.button === Qt.LeftButton)
                {
                    let coord = c_Map.toCoordinate(Qt.point(mouseX, mouseY));
                    markerwindow.open(coord.latitude, coord.longitude);
                }
                ClickHandler.state = ClickHandler.Idle;
            }

            else
            {
                if(mouse.button === Qt.RightButton) {
                    let coord = c_Map.toCoordinate(Qt.point(mouseX, mouseY));
                    ClickHandler.copyCoordinatesToClipboard(coord.latitude, coord.longitude);
                }
            }
        }

        onPositionChanged: {
            let coord = toCoordinate(Qt.point(mouseX, mouseY))
            coord_tooltip.latitude = coord.latitude;
            coord_tooltip.longitude = coord.longitude;
            coord_tooltip.x = mouseX + 10;
            coord_tooltip.y = mouseY;
        }
    }

    MapTab.UAV { id: c_UAV; }
    MapTab.UAVRoute { id: c_Route; visible: opacity > 0; Behavior on opacity { NumberAnimation { duration: 300; } } }

    RulerModel { id: c_RulerModel; }
    MapTab.RulerItem { id: c_Ruler; fl_LastLatitude: c_RulerModel.lastLatitude; fl_LastLongitude: c_RulerModel.lastLongitude; }

    Widgets.CoordinateTooltip { id: coord_tooltip; z: 60; opacity: 0.85; visible: checkbox_ShowCursorCoords.checked && !c_MapMouseArea.pressed; }

    // main image view
    MapItemView {
        model: ImagesModel;
        add: Transition { NumberAnimation { property: "m_opacity"; from: 0; to: 1; duration: 500; easing.type: Easing.OutCubic; } }
        remove: Transition { NumberAnimation { property: "m_opacity"; from: 1; to: 0; duration: 500; easing.type: Easing.OutCubic; } }
        delegate: MapTab.MapImage { }

        Connections { target: ImagesModel; function onAdded() { button_PanLastImage.self(); } }
    }

    function deleteImage(index) { ImagesModel.remove(index); }
    MapItemView {
        model: ImagesModel;
        add: Transition { NumberAnimation { property: "m_opacity"; from: 0; to: 1; duration: 500; easing.type: Easing.OutCubic; } }
        remove: Transition { NumberAnimation { property: "m_opacity"; from: 1; to: 0; duration: 500; easing.type: Easing.OutCubic; } }
        delegate: MapTab.MapImageUI { }
    }

    MapItemView {
        model: MarkersModel;
        add: Transition { NumberAnimation { property: "m_opacity"; from: 0; to: 1; duration: 500; easing.type: Easing.OutCubic; } }
        remove: Transition { NumberAnimation { property: "m_opacity"; from: 1; to: 0; duration: 500; easing.type: Easing.OutCubic; } }
        delegate: MapTab.MapMarker { }
    }

    // ui

    MapTab.AttitudeIndicator { id: attitude;
        width: 250;
        height: 200;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
        pitch: Network.telemetry.pitch;
        roll: Network.telemetry.roll;
        yaw: Network.telemetry.yaw;
    }

    Pane { id: panel_Tools;
        Material.elevation: 30;
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.margins: 5;
        opacity: 0.85;

        Column {
            spacing: 15;

            Column {
                RoundButton { id: button_Ruler;
                    checkable: true;
                    checked: ClickHandler.state === ClickHandler.RulerActive;
                    height: 44;
                    width: 44;
                    radius: 4;
                    icon.source: "qrc:/icons/google-material/ruler.png";
                    icon.color: Theme.color("light0");
                    Material.elevation: 30;
                    Material.background: checked ? Theme.color("yellow") : Theme.color("dark2");
                    onCheckedChanged: {
                        if(checked && ClickHandler.state === ClickHandler.Idle)
                            ClickHandler.state = ClickHandler.RulerActive;
                        else
                            ClickHandler.state = ClickHandler.Idle;
                    }
                }

                RoundButton { id: button_Protractor;
                    checkable: true;
                    checked: ClickHandler.state === ClickHandler.ProtractorActive;
                    height: 44;
                    width: 44;
                    radius: 4;
                    icon.source: "qrc:/icons/google-material/ruler2.png";
                    icon.color: Theme.color("light0");
                    Material.elevation: 30;
                    Material.background: checked ? Theme.color("accent") : Theme.color("dark2");
                    onCheckedChanged: {
                        if(checked && ClickHandler.state === ClickHandler.Idle)
                            ClickHandler.state = ClickHandler.ProtractorActive;
                        else
                            ClickHandler.state = ClickHandler.Idle;
                    }
                }
            }

            Column {
                RoundButton { id: button_PanUAV;
                    height: 44;
                    width: 44;
                    radius: 4;
                    icon.source: "qrc:/icons/google-material/gps.png";
                    icon.color: Theme.color("light0");
                    Material.elevation: 30;
                    Material.background: Theme.color("dark2");
                    onPressed: c_Map.center = c_UAV.coordinate;
                }

                RoundButton { id: button_PanLastImage;
                    function self() {
                        console.log("[GUI] Panned at " + ImagesModel.lastImagePosition());
                        c_Map.center = ImagesModel.lastImagePosition();
                    }

                    height: 44;
                    width: 44;
                    radius: 4;
                    icon.source: "qrc:/icons/google-material/image-gps.png";
                    icon.color: Theme.color("light0");
                    Material.background: Theme.color("dark2");
                    Material.elevation: 30;
                    onPressed: self();
                }
            }
        }
    }

    Pane { id: panel_Entities;
        anchors.top: panel_Tools.bottom;
        anchors.topMargin: 30;
        anchors.left: parent.left;
        anchors.margins: 5;
        opacity: 0.85;

        Column {
            RoundButton { id: button_Marker;
                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/google-material/marker.png";
                icon.color: Theme.color("light0");
                Material.elevation: 30;
                Material.background: ClickHandler.state === ClickHandler.MarkerActive ? Theme.color("accent") : Theme.color("dark2");
                onPressed: ClickHandler.state = ClickHandler.MarkerActive;
            }

            RoundButton { id: button_PlannerPoint;
                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/google-material/flag.png";
                icon.color: Theme.color("light0");
                Material.background: ClickHandler.state === ClickHandler.PlannerActive ? Theme.color("accent") : Theme.color("dark2");
                Material.elevation: 30;
                onPressed: ClickHandler.state = ClickHandler.PlannerActive;
            }

            RoundButton { id: button_ClearMarkers;
                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/google-material/remove-layer.png";
                icon.color: Theme.color("light0");
                Material.background: Theme.color("dark2");
                Material.elevation: 30;
                onPressed: dialogwindow.open("Удаление маркеров", "Вы уверены, что хотите удалить все маркеры карты?", "warn", 2);

                Connections {
                    target: dialogwindow;
                    function onClosed(status, uid) {
                        if(uid === 2 && status === true) {
                            console.log("[GUI] Markers cleared");
                            MarkersModel.clear();
                        }
                    }
                }
            }

            RoundButton { id: button_ClearImages;
                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/google-material/remove-image.png";
                icon.color: Theme.color("light0");
                Material.background: Theme.color("dark2");
                Material.elevation: 30;
                onPressed: dialogwindow.open("Удаление РЛИ", "Вы уверены, что хотите удалить все радиолокационные изображения с карты?", "warn", 4);

                Connections {
                    target: dialogwindow;
                    function onClosed(status, uid) {
                        if(uid === 4 && status === true) {
                            console.log("[GUI] Images cleared");
                            ImagesModel.clear();
                        }
                    }
                }
            }

            RoundButton { id: button_ToggleImages;
                height: 44;
                width: 44;
                radius: 4;
                icon.source: "qrc:/icons/google-material/hide.png";
                icon.color: Theme.color("light0");
                Material.background: Theme.color("dark2");
                Material.elevation: 30;
//                onPressed: {

//                }
            }
        }
    }

    Pane { id: panel_Parameters;
        property bool b_Expanded: false;

        anchors.bottom: layout_MapMode.top;
        anchors.right: parent.right;
        anchors.margins: 5;
        opacity: 0.85;
        width: b_Expanded ? implicitWidth : 0;
        visible: width > 0;
        Behavior on width { NumberAnimation { easing.type: Easing.InOutQuad; duration: 200; } }
        clip: true;

        ColumnLayout {
            spacing: -5;

            CheckBox { id: checkbox_FollowUAV;
                font.family: root.mainfont;
                checked: false;
                text: "Следить за БПЛА";
                //onCheckedChanged: binding)
            }

            CheckBox { id: checkbox_EnableGrid;
                font.family: root.mainfont;
                checked: false;
                text: "Отображать масштабную сетку";
                //onCheckedChanged:
            }

            CheckBox { id: checkbox_ShowCursorCoords;
                font.family: root.mainfont;
                checked: false;
                text: "Отображать координаты курсора";
            }

            CheckBox { id: checkbox_ShowTrack;
                font.family: root.mainfont;
                checked: true;
                text: "Отображать трек полёта";
                onCheckedChanged: {
                    if(checked)
                        c_Route.opacity = 1;
                    else
                        c_Route.opacity = 0;
                }
            }

            CheckBox { id: checkbox_ShowDiagram;
                font.family: root.mainfont;
                checked: true;
                text: "Отображать диаграмму направленности";
                //onCheckedChanged:
            }

            Column {
                Layout.fillWidth: true;

                RoundButton { id: button_ClearTrack;
                    radius: 4;
                    icon.source: "qrc:/icons/google-material/clear.png";
                    icon.color: Theme.color("light0");
                    height: 40;
                    font.family: root.mainfont;
                    width: checkbox_ShowDiagram.width;
                    text: "Очистить трек полёта";
                    Material.background: Theme.color("red");
                    onPressed: dialogwindow.open("Очистка трека", "Вы уверены, что хотите очистить трек полёта?", "warn", 1);
                    Connections {
                        target: dialogwindow;
                        function onClosed(status, uid) {
                            if(uid === 1 && status === true) {
                                console.log("[GUI] Track cleared");
                                c_Route.clear();
                            }
                        }
                    }
                }
            }
            Item { Layout.fillWidth: true; Layout.fillHeight: true; height: 30; }
        }
    }

    RoundButton { id: button_ExpandParameters;
        anchors.bottom: layout_MapMode.top;
        anchors.right: parent.right;
        anchors.margins: 5;
        checkable: true;
        height: 40;
        radius: 4;
        icon.source: panel_Parameters.b_Expanded ? "qrc:/icons/google-material/collapse.png"
                                                 : "qrc:/icons/google-material/expand.png";
        icon.color: Theme.color("light0");
        font.family: root.mainfont;
        text: panel_Parameters.b_Expanded ? "" : "Параметры карты";
        Material.elevation: 30;
        Material.background: Material.background;
        Material.primary: Material.primary;
        Material.accent: Material.accent;
        onCheckedChanged: panel_Parameters.b_Expanded = checked;
    }

    Pane { id: panel_ImageTools;
        property bool b_Expanded: false;

        Material.elevation: 30;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.margins: 0;
        opacity: 0.85;
        width: b_Expanded ? implicitWidth : 0;
        height: b_Expanded ? implicitHeight : 0;
        visible: height > 0;
        Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad; duration: 200; } }
        Behavior on width { NumberAnimation { easing.type: Easing.InOutQuad; duration: 200; } }
        clip: true;

        ColumnLayout {
            Column {
                Layout.fillWidth: true;
                RoundButton { id: button_FormImage;
                    font.family: root.mainfont;
                    height: 40;
                    width: layout_ImageTools.width;
                    radius: 4;
                    icon.source: "qrc:/icons/google-material/take-photo.png";
                    icon.color: Theme.color("light0");
                    text: "Формирование изображения";
                    Material.elevation: 30;
                    Material.background: Theme.color("color0");
                    //onPressed:
                }
            }

            Item { Layout.fillWidth: true; Layout.fillHeight: true; height: 15; }

            Grid { id: layout_ImageTools;
                columns: 2;
                Layout.fillWidth: true;

                RoundButton { id: button_FetchImages;
                    font.family: root.mainfont;
                    height: 40;
                    radius: 4;
                    icon.source: "qrc:/icons/google-material/refresh.png";
                    icon.color: Theme.color("light0");
                    text: "Обновить каталог";
                    Material.elevation: 30;
                    Material.background: Material.background;
                    onPressed: {
                        let ret = Filesystem.fetchImageDirectory();
                        if(!ret)
                            messagebox.open("Не найдены изображения", "В целевой папке не найдены радиолокационные изображения.", "warn");
                    }
                }

                RoundButton { id: button_ChooseCatalogue;
                    font.family: root.mainfont;
                    height: 40;
                    radius: 4;
                    icon.source: "qrc:/icons/google-material/folder.png";
                    icon.color: Theme.color("light0");
                    Material.elevation: 30;
                    Material.background: Material.background;
                    text: "Изменить каталог";
                    onPressed: window_FileDialog.open();
                }

                RoundButton { id: button_ClearLocalCache;
                    font.family: root.mainfont;
                    height: 40;
                    radius: 4;
                    icon.source: "qrc:/icons/google-material/delete.png";
                    icon.color: Theme.color("light0");
                    Material.elevation: 30;
                    Material.background: Theme.color("red");
                    text: "Очистить кэш";
                    onPressed: dialogwindow.open("Очистка кэша", "Вы уверены, что хотите очистить кэш радиолокационных изображений? Все изображения, сохраненные на этом АРМ, будут удалены!", "warn", 3);
                    Connections {
                        target: dialogwindow;
                        function onClosed(status, uid) {
                            if(uid === 3 && status === true) {
                                console.log("[GUI] Cache cleared");
                                Paths.clearImageCache();
                            }
                        }
                    }
                }
            }
            Item { Layout.fillWidth: true; Layout.fillHeight: true; height: 30; }
        }
    }

    RoundButton { id: button_ToggleImageTools;
        font.family: root.mainfont;
        height: 40;
        radius: 4;
        icon.source: panel_ImageTools.b_Expanded ? "qrc:/icons/google-material/expand-less.png"
                                                 : "qrc:/icons/google-material/expand-more.png";
        icon.color: Theme.color("light0");
        text: panel_ImageTools.b_Expanded ? "" : "Работа с изображениями";
        Material.elevation: 30;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.margins: 5;
        Material.background: Material.background;
        onPressed: panel_ImageTools.b_Expanded = !panel_ImageTools.b_Expanded;
    }

    Row { id: layout_MapMode;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        anchors.margins: 5;

        ComboBox { id: control_MapMode;
            font.family: root.mainfont;
            font.weight: Font.Bold;
            width: 170;
            currentIndex: 2;
            model: ["Оффлайн-карта", "Схема", "Спутник", "Гибрид"];

            onCurrentValueChanged: {
                if(currentValue === "Оффлайн-карта")
                    i_MapMode = 0;
                if(currentValue === "Схема")
                    i_MapMode = 5;
                if(currentValue === "Спутник")
                    i_MapMode = 1;
                if(currentValue === "Гибрид")
                    i_MapMode = 4;
            }
        }
    }
}
