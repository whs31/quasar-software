import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtLocation
import QtPositioning
import QtQuick.Layouts

import QuaSAR.API 1.0

import Theme 1.0
import Ruler 1.0
import ClickHandler 1.0
import Filesystem 1.0
import Config 1.0
import Images 1.0
import Markers 1.0
import Route 1.0
import Notifications 1.0

import "map" as MapTab
import "map/ui" as MapTabUI
import "map/mapquickitems" as MapQuickItems
import "../widgets" as Widgets

Map { id: maptab_root;
    property int i_MapMode: 1; // { 0 - offline, 5 - schema, 4 - hybrid, 1 - satellite }
    property alias routeType: c_Route.type;

    Component.onDestruction: {
        Settings.setParameter("state/latitude", center.latitude)
        Settings.setParameter("state/longitude", center.longitude)
        Settings.setParameter("state/zoom", zoomLevel)
        Settings.save()
    }

    tilt: 15;
    plugin: Plugin {
        name: "osm";

        PluginParameter {
            name: "osm.mapping.providersrepository.address";
            value: "file:///" + Paths.mapConfig();
        }

        Component.onCompleted: console.info("[MAP] Using osmconfig: " + Paths.mapConfig());
    }

    activeMapType: maptab_root.supportedMapTypes[i_MapMode];
    center: QtPositioning.coordinate(Settings.io.parameter("state/latitude"), Settings.io.parameter("state/longitude"));
    zoomLevel: Settings.io.parameter("state/zoom");
    copyrightsVisible: false;
    z: 0;

    Behavior on center { CoordinateAnimation { duration: 250; easing.type: Easing.InOutQuad; } }
    Behavior on zoomLevel { NumberAnimation { duration: 250; easing.type: Easing.InOutCubic; } }

    PinchHandler {
        id: pinch
        target: null
        onActiveChanged: if (active) {
            maptab_root.startCentroid = maptab_root.toCoordinate(pinch.centroid.position, false)
        }
        onScaleChanged: (delta) => {
            maptab_root.zoomLevel += Math.log2(delta)
            maptab_root.alignCoordinateToPoint(maptab_root.startCentroid, pinch.centroid.position)
        }
        grabPermissions: PointerHandler.TakeOverForbidden
    }

    WheelHandler {
        id: wheel
        acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
            ? PointerDevice.Mouse | PointerDevice.TouchPad
            : PointerDevice.Mouse
        rotationScale: 1/120
        property: "zoomLevel"
    }

    DragHandler {
        id: drag
        target: null
        onTranslationChanged: (delta) => maptab_root.pan(-delta.x, -delta.y)
    }

    Connections {
        target: NetworkAPI.telemetry;
        function onSeaLevelChanged() {
            if(NetworkAPI.telemetry.seaLevel === 0)
                NotificationsModel.add(NotificationsModel.Uncalibrated, NotificationsModel.Alert)
            else
                NotificationsModel.remove(NotificationsModel.Uncalibrated);
        }
        Component.onCompleted: NotificationsModel.add(NotificationsModel.Uncalibrated, NotificationsModel.Alert)
    }

    MouseArea { id: c_MapMouseArea;
        hoverEnabled: true;
        anchors.fill: parent;
        acceptedButtons: Qt.LeftButton | Qt.RightButton;

        onClicked: {
            if(ClickHandler.state === ClickHandler.RulerActive)
            {
                if(mouse.button === Qt.LeftButton)
                    c_RulerModel.insertPoint(maptab_root.toCoordinate(Qt.point(mouseX, mouseY)), 0);
                if(mouse.button === Qt.RightButton)
                    c_RulerModel.resetRoute();
            }
            else if(ClickHandler.state === ClickHandler.MarkerActive)
            {
                if(mouse.button === Qt.LeftButton)
                {
                    let coord = maptab_root.toCoordinate(Qt.point(mouseX, mouseY));
                    markerwindow.open(coord.latitude, coord.longitude);
                }
                ClickHandler.state = ClickHandler.Idle;
            }
            else if(ClickHandler.state === ClickHandler.TileLoaderActive)
            {
                if(mouse.button === Qt.LeftButton)
                {
                    if(tileloaderpolygon.path.count >= 4)
                        tileloaderpolygon.removeCoordinate(tileloaderpolygon.path[0]);
                    let c = maptab_root.toCoordinate(Qt.point(mouseX, mouseY));
                    tileloaderpolygon.addCoordinate(c);
                    tileloaderlastclicked = c;
                    dialog_TileDownloader.poly = tileloaderpolygon.path;
                    tileloaderui.shown = true;
                }
                else
                {
                    tileloaderpolygon.path = [];
                    dialog_TileDownloader.poly = tileloaderpolygon.path;
                    tileloaderui.shown = false;
                }
            }

            else
            {
                if(mouse.button === Qt.RightButton) {
                    let coord = maptab_root.toCoordinate(Qt.point(mouseX, mouseY));
                    ClickHandler.copyCoordinatesToClipboard(coord.latitude, coord.longitude);
                }
            }
        }

        onPositionChanged: {
            let coord = toCoordinate(Qt.point(mouseX, mouseY))
            coord_tooltip.latitude = coord.latitude;
            coord_tooltip.longitude = coord.longitude;
        }
    }

    Connections {
        target: dialog_TileDownloader;
        function onClr() {
            tileloaderpolygon.path = [];
            tileloaderui.shown = false;
            dialog_TileDownloader.poly = tileloaderpolygon.path;
            ClickHandler.state = ClickHandler.Idle;
        }
    }

    RulerModel { id: c_RulerModel; }
    MapTab.RulerItem { id: c_Ruler; fl_LastLatitude: c_RulerModel.lastLatitude; fl_LastLongitude: c_RulerModel.lastLongitude; }

    // main image view
    MapItemView {
        model: ImagesModel;
        add: Transition { NumberAnimation { property: "m_opacity"; from: 0; to: 1; duration: 500; easing.type: Easing.OutCubic; } }
        remove: Transition { NumberAnimation { property: "m_opacity"; from: 1; to: 0; duration: 500; easing.type: Easing.OutCubic; } }
        delegate: MapTab.MapImage { }

        Connections { target: ImagesModel; function onAdded() { panel_Tools.panImage(); } }
    }

    function deleteImage(index) { ImagesModel.remove(index); }
    MapItemView {
        model: ImagesModel;
        add: Transition { NumberAnimation { property: "m_opacity"; from: 0; to: 1; duration: 500; easing.type: Easing.OutCubic; } }
        remove: Transition { NumberAnimation { property: "m_opacity"; from: 1; to: 0; duration: 500; easing.type: Easing.OutCubic; } }
        delegate: MapTab.MapImageUI { }
    }

    MapItemView {
        model: StreamSegmentModel
        add: Transition { NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 1500; easing.type: Easing.OutCubic; } }
        remove: Transition { NumberAnimation { property: "opacity"; from: 1; to: 0; duration: 500; easing.type: Easing.OutCubic; } }
        delegate: MapQuickItems.Strip { }
    }

    MapItemView {
        model: MarkersModel;
        add: Transition { NumberAnimation { property: "m_opacity"; from: 0; to: 1; duration: 500; easing.type: Easing.OutCubic; } }
        remove: Transition { NumberAnimation { property: "m_opacity"; from: 1; to: 0; duration: 500; easing.type: Easing.OutCubic; } }
        delegate: MapQuickItems.GeoMarker { }
    }

    MapTab.UAV { id: c_UAV; }
    MapQuickItems.NotificationsUI { }
    MapTab.UAVRoute { id: c_Route; visible: opacity > 0; Behavior on opacity { NumberAnimation { duration: 300; } } }
    MapTab.StripRoute {id: stripRoute; visible: opacity > 0; Behavior on opacity { NumberAnimation { duration: 300; } } }
    RadarDiagram {  id: c_RadarDiagram;
        angle: 30 - Settings.io.parameter("image/div-correction") // @FIXME
        uavPosition: NetworkAPI.telemetry.position
        azimuth: NetworkAPI.telemetry.eulerAxes.y
        range: 3500
        direction: Settings.io.parameter("misc/antenna-alignment") === "right" ? 1 : 0
        type: RadarDiagram.Telescopic
    }

    MapPolygon { id: c_RadarDiagramView;
        property bool shown: true;
        path: c_RadarDiagram.polygon;
        border.width: 3;
        border.color: ColorTheme.active.color(ColorTheme.Yellow)
        color: Qt.lighter(ColorTheme.active.color(ColorTheme.Yellow), 1.2);
        opacity: shown ? 0.2 : 0;
        Behavior on opacity { NumberAnimation { duration: 200; } }
    }

    MapQuickItems.WorkstationPosition { }

    property var tileloaderlastclicked: QtPositioning.coordinate(0, 0);
    MapPolygon { id: tileloaderpolygon;
        property bool shown: true;
        border.width: 3;
        border.color: ColorTheme.active.color(ColorTheme.Green);
        color: Qt.lighter(ColorTheme.active.color(ColorTheme.Green), 1.2);
        opacity: shown ? 0.4 : 0;
        Behavior on opacity { NumberAnimation { duration: 200; } }
    }

    MapQuickItem {
        id: tileloaderui
        property bool shown: false
        opacity: shown ? 0.75 : 0
        Behavior on opacity { NumberAnimation { duration: 200 } }
        Behavior on coordinate { CoordinateAnimation { duration: 250; easing.type: Easing.InOutQuad } }
        coordinate: tileloaderlastclicked
        sourceItem: MapTabUI.DialogTileLoader { id: dialog_TileDownloader }
    }

    MapQuickItems.StripEraser {
        id: eraser
        coordinate: maptab_root.toCoordinate(Qt.point(c_MapMouseArea.mouseX, c_MapMouseArea.mouseY))
        visible: false
    }

    // ui

    Widgets.CoordinateTooltip { id: coord_tooltip;
        property bool shown: !panel_Parameters.shown;

        anchors {
            bottom: button_ExpandParameters.top
            right: parent.right
            margins: 5
        }
        z: 60;
        opacity: shown ? 0.85 : 0;
        Behavior on opacity { NumberAnimation { duration: 500; } }
    }

    MapTabUI.PanelZoom { id: panel_Zoom;
        property bool shown: !panel_Parameters.shown;

        anchors {
            bottom: coord_tooltip.top
            right: parent.right
            margins: 5
        }
        z: 60;
        enabled: shown;
        opacity: shown ? 0.85 : 0;
        Behavior on opacity { NumberAnimation { duration: 500; } }
    }

    MapTab.AttitudeIndicator {
        id: attitude
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        enabled: false
        visible: false
        width: 250
        implicitHeight: 150
        pitch: NetworkAPI.telemetry.eulerAxes.x
        roll: NetworkAPI.telemetry.eulerAxes.z
        yaw: NetworkAPI.telemetry.eulerAxes.y
    }

    RoundButton {
        id: button_HideIndicator
        enabled: false
        visible: false
        anchors {
            bottom: attitude.top
            bottomMargin: -7
            horizontalCenter: attitude.horizontalCenter
        }
        height: 40
        radius: 4
        icon.source: attitude.shown ? "qrc:/icons/vector/common/collapse.svg"
                                    : "qrc:/icons/vector/common/expand.svg"
        icon.color: ColorTheme.active.color(ColorTheme.Text)
        font.family: root.mainfont
        text: attitude.shown ? "" : "Авиагоризонт"
        Material.background: Material.background
        Material.primary: Material.primary
        Material.accent: Material.accent
        checkable: true
        checked: false
        onCheckedChanged: attitude.shown = checked
    }

    MapTabUI.PanelMainToolbar {
        id: panel_MainToolbar
        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
            margins: 5
        }
        opacity: 0.85
    }

    MapTabUI.PanelFormParameters {
        id: panel_FormParameters
        anchors {
            top: panel_MainToolbar.bottom
            left: panel_MainToolbar.left
            right: panel_MainToolbar.right
        }
    }

    MapTabUI.PanelTools {
        id: panel_Tools
        anchors {
            top: parent.top
            right: parent.right
            margins: 5
        }
        opacity: 0.85
    }

    MapTabUI.PanelEntities {
        id: panel_Entities
        anchors {
            top: panel_Tools.bottom
            topMargin: 30
            right: parent.right
            margins: 5
        }
        opacity: 0.85
    }

    MapTabUI.PanelParameters {
        id: panel_Parameters
        anchors {
            bottom: parent.bottom
            right: parent.right
        }
        opacity: 0.85
    }

    RoundButton {
        id: button_ExpandParameters
        anchors {
            bottom: panel_Parameters.top
            bottomMargin: -7
            right: panel_Parameters.right
            rightMargin: -7
        }
        checkable: true
        height: 40
        radius: 4
        icon.source: panel_Parameters.shown ? "qrc:/icons/vector/common/collapse.svg"
                                            : "qrc:/icons/vector/common/expand.svg"
        icon.color: ColorTheme.active.color(ColorTheme.Text)
        font.family: root.mainfont
        text: panel_Parameters.shown ? "" : "Параметры карты"
        Material.elevation: 30
        Material.background: Material.background
        Material.primary: Material.primary
        Material.accent: Material.accent
        onCheckedChanged: panel_Parameters.shown = checked
    }
}
