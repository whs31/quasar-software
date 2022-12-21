import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtLocation 5.12
import QtPositioning 5.12
import QtGraphicalEffects 1.0
import "groups" as Groups
import "sar-image" as ImageSAR

//import

import SMath 1.0
import MouseKeyHandler 1.0
import MarkerManager 1.0
import ImageManager 1.0


Rectangle {
    id: qqview
    SMath { id: smath; }
    MouseKeyHandler { id: mouseKeyHandler; }

    Timer { interval: 16; running: true; repeat: true; onTriggered: { update(); } }
    property bool bottomPanning: false;
    property bool topPanning: false;
    property bool leftPanning: false;
    property bool rightPanning: false;

    //ux constants
    Material.theme: Material.Dark;
    Material.accent: "#204040";
    Material.primary: "#bc9117";
    Material.background: "#132623";
    property color accentDark: "#A2A2A2";
    property color primaryLight: "#00B5EB";
    property color primarySuperLight: "#97E3EE";
    property color yellowColor: "#F6C413";

    //ux settings
    layer.enabled: true;
    layer.samples: 4;

    //defaults constants
    property real defaultLatitude: 60.034;
    property real defaultLongitude: 30.28136;
    property real defaultZoom: 15.0;
    property int  defaultMapModeOnTestMode: 0;

    property var currentQtCoordinates: QtPositioning.coordinate(defaultLatitude, defaultLongitude);

    //ruler
    property int r_currentstate: 0;
    property var r_firstpoint: QtPositioning.coordinate(0.0, 0.0);
    property var r_secondpoint: QtPositioning.coordinate(0.0, 0.0);

    //===========================================================================================================================================================================================
    //===========================================================================================================================================================================================

    //called on map component initialized
    function awake()
    {
        mapView.addMapItem(planeMapItem);
    }

    //called right after awake
    function start()
    {
        zoomSliderElement.zoomSliderValue = 1 - (mapView.zoomLevel / 18);
        tiltSliderElement.tiltSliderValue = 1 - (mapView.tilt / 45);
    }

    function qmlBackendStart()
    {
        if(FStaticVariables.testMode) { defaultMapModeOnTestMode = 3; } else { defaultMapModeOnTestMode = 0; }
    }

    //called every fixed time (0.5 s default)           call time equals to C_UPDATETIME in sconfig
    function fixedUpdate()
    {
        //сначала рисуем самолёт, потом уже присваиваем курренткоординатес, иначе угол не посчитается
        drawPlane();
        currentQtCoordinates = QtPositioning.coordinate(FTelemetry.latitude,FTelemetry.longitude);

        if(FDynamicVariables.followPlane) panGPS();
        if(FDynamicVariables.enableRoute) drawRoute();

        onGUI();
    }

    //called after fixedupdate
    function onGUI()
    {
        telemetryPanel.textLatitude = Number(FTelemetry.latitude).toFixed(7);
        telemetryPanel.textLongitude = Number(FTelemetry.longitude).toFixed(7);
        telemetryPanel.textElevation = "<font color=\"#a385cf\">" + Number(FTelemetry.elevation).toFixed(0) + "</font>";
        telemetryPanel.textSpeed = "<font color=\"#a385cf\">" + Number(FTelemetry.speed).toFixed(1) + "</font>";
    }

    //called 60 times per second (enable Timer ^^^^)
    function update()
    {
        if(bottomPanning) { mapView.pan(0, 2); }
        if(topPanning) { mapView.pan(0, -2); }
        if(leftPanning) { mapView.pan(-2, 0); }
        if(rightPanning) { mapView.pan(2, 0); }
    }

    //===========================================================================================================================================================================================
    //===========================================================================================================================================================================================

    function panImage()
    {
        console.log("[QML] Map centered on image");
        var coords = QtPositioning.coordinate(imageModel.get(imageModel.count - 1).m_lat, imageModel.get(imageModel.count - 1).m_lon);
        mapView.center = coords;
    }
    function drawPlane()
    {
        planeMapItem.coordinate = QtPositioning.coordinate(FTelemetry.latitude, FTelemetry.longitude);
        var atan = 0.0; var angle = 0.0; var geometricalAngle = 0.0;
        var coord = QtPositioning.coordinate(FTelemetry.latitude, FTelemetry.longitude);
        var e = 5;
        if(Math.abs(currentQtCoordinates.distanceTo(coord)) > e && Math.abs(currentQtCoordinates.distanceTo(coord)) > e)
        {
            angle = currentQtCoordinates.azimuthTo(coord);

            atan = Math.atan2(FTelemetry.longitude-currentQtCoordinates.longitude, FTelemetry.latitude-currentQtCoordinates.latitude);
            geometricalAngle = (atan*180)/Math.PI;

            planeMapItem.rotationAngle = angle;
            if(FDynamicVariables.enablePredict) { drawPredict(geometricalAngle); } else { clearPredict(); }
        }
    }
    function drawPredict(angle)
    {
        predictLine.path = [];
        var p_lat = FTelemetry.latitude+Math.sin((90-angle)*Math.PI/180) * ( smath.metersToDegrees(FStaticVariables.predictRange * 1000) );
        var p_lon = FTelemetry.longitude+Math.cos((90-angle)*Math.PI/180) * ( smath.metersToDegrees(FStaticVariables.predictRange * 1000) );
        predictLine.addCoordinate(QtPositioning.coordinate(FTelemetry.latitude, FTelemetry.longitude));
        predictLine.addCoordinate(QtPositioning.coordinate(p_lat, p_lon));
    }
    function clearPredict() { predictLine.path = []; }
    function panGPS()
    {
        mapView.center = currentQtCoordinates;
    }
    function drawRoute()
    {
        mapPolyline.addCoordinate(QtPositioning.coordinate(FTelemetry.latitude, FTelemetry.longitude));
    }
    function clearRoute()
    {
        mapPolyline.path = [];
    }
    function changeTooltipPosition()
    {
        if(FDynamicVariables.enableTooltip)
        {
            if(mapMouseArea.pressed)
            {
                mapHoverCoordinatesTooltip.visible = false;
                mapHoverCoordinatesTooltip.visible = false;
            }
            else {
                mapHoverCoordinatesTooltip.visible = true;
                mapHoverCoordinatesTooltip.visible = true;
                mapHoverCoordinatesTooltip.x = mapMouseArea.mouseX;
                mapHoverCoordinatesTooltip.y = mapMouseArea.mouseY;
                var coordToStr = mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY));
                mapHoverCoordinatesTooltip.tooltipText = "➤ Ш: "+coordToStr.latitude.toFixed(5)+",  Д: "+coordToStr.longitude.toFixed(5);
            }
        }
        else {
            mapHoverCoordinatesTooltip.visible = false;
            mapHoverCoordinatesTooltip.visible = false;
        }
    }
    function drawRuler()
    {
        rulerLine.path = [];
        rulerLine.addCoordinate(r_firstpoint);
        rulerLine.addCoordinate(r_secondpoint);
        rulerTextMapItem.visible = true;

        var cc = QtPositioning.coordinate((r_firstpoint.latitude+r_secondpoint.latitude)/2, (r_firstpoint.longitude+r_secondpoint.longitude)/2);
        var geoAngle = r_firstpoint.azimuthTo(r_secondpoint); //между N и выбранным вектором
        var textAngle = geoAngle+0;
        if(textAngle>90 & textAngle<270) { textAngle+=180 }
        if(geoAngle>90 & geoAngle<270) { geoAngle +=180 }

        rulerTextMapItem.coordinate = cc;
        rulerTextMapItem.rulerRotationAngle = textAngle;
        r1MapItem.r1RotationAngle = geoAngle;
        r2MapItem.r2RotationAngle = geoAngle;
        r2MapItem.visible = true;
        r2MapItem.coordinate = r_secondpoint;
    }
    function clearRuler()
    {
        rulerLine.path = [];
        rulerTextMapItem.visible = false;
        r1MapItem.visible = false;
        r2MapItem.visible = false;
    }
    function addImage(meta, gui, base64: string, checksumSuccess: bool)
    {
        imageUIModel.append({   "m_lat": meta[0],
                                "m_lon": meta[1],
                                "m_width": meta[9],
                                "m_height": meta[10],
                                "m_latitude": gui[0],
                                "m_longitude": gui[1],
                                "m_dx": gui[2],
                                "m_dy": gui[3],
                                "m_x0": gui[4],
                                "m_y0": gui[5],
                                "m_angle": gui[6],
                                "m_driftAngle": gui[7],
                                "m_lx": gui[8],
                                "m_ly": gui[9],
                                "m_azimuth": gui[10],
                                "m_hash": gui[11],
                                "m_filename": gui[12],
                                "m_datetime": gui[13],
                                "m_checksumMatch": checksumSuccess ? "<font color=\"#73c924\">да</font>" : "<font color=\"#b16573\">нет</font>",
                                "m_visible": false
                            });
        imageModel.append({     "m_lat": meta[0],
                                "m_lon": meta[1],
                                "m_x0": meta[4],
                                "m_y0": meta[5],
                                "m_width": meta[9],
                                "m_height": meta[10],
                                "m_angle": meta[6],
                                "m_driftAngle": meta[7],
                                "m_base64": base64,
                                "m_zoom": smath.mercatorZoomLevel(1, meta[0]),
                                "m_i_visible": true
                            });
    }
    function addMarker(name: string, col: color, icon: string, latitude: real, longitude: real, anchorX: real, anchorY: real, zoomLevel: real){
        markerModel.append({    "m_name": name, 
                                "m_color": String(col), 
                                "m_qrc": icon, 
                                "lat": latitude, 
                                "lon": longitude, 
                                "anchorX": anchorX,
                                "anchorY": anchorY,
                                "m_zoom": zoomLevel
                            });
    }
    function markerRemove(i)
    {
        MarkerManager.removeMarker(i);
    }
    function imageRemove(i)
    {
        var b = ImageManager.removeImage(i);
        if(b) { return true; } 
        else { return false; }
    }
    ListModel { id: imageModel; }
    ListModel { id: imageUIModel; }
    ListModel { id: markerModel; }
    
    property bool markerPlacementCursorChange: false;

    Map {
        MouseArea {
            id: mapMouseArea;
            anchors.fill: parent;
            hoverEnabled: true;
            propagateComposedEvents: true;
            cursorShape: markerPlacementCursorChange ? Qt.PointingHandCursor : Qt.CrossCursor;
            //preventStealing: true; //never enable it, or gestures will be broken 
            acceptedButtons: Qt.LeftButton | Qt.RightButton;
            z: 0;
            onEntered: {
                mapHoverCoordinatesTooltip.visible = true;
            }
            onExited: {
                mapHoverCoordinatesTooltip.visible = false;
            }
            onPositionChanged: {
                changeTooltipPosition();
                if(r_currentstate === 2)
                {
                    drawRuler();
                    r_secondpoint = mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY));
                    rulerText.text = r_firstpoint.distanceTo(r_secondpoint).toLocaleString(Qt.locale("ru_RU"), 'f', 0) + " м";
                }
                if(mouseKeyHandler.mouseState === 1)
                {
                    markerPlacementCursorChange = true;
                } else { markerPlacementCursorChange = false; }
            }
            onClicked:
            {
                if(r_currentstate !== 0 & mouse.button === Qt.RightButton)
                {
                    r_currentstate = 0;
                    clearRuler();
                }
                else if(r_currentstate === 1 & mouse.button === Qt.LeftButton)
                {
                    r_firstpoint = mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY));
                    r1MapItem.coordinate = r_firstpoint;
                    r1MapItem.visible = true;
                    r_currentstate = 2;
                    r_secondpoint = r_firstpoint;
                }
                else if(r_currentstate === 2 & mouse.button === Qt.LeftButton)
                {
                    r_secondpoint = mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY));
                    r_currentstate = 3;

                    r2MapItem.visible = true;
                }
                else if(r_currentstate === 3)
                {
                    r_currentstate = 0;
                    clearRuler();
                }
                if(r_currentstate === 0 & mouse.button === Qt.RightButton)
                {
                    mouseKeyHandler.copyCoordinates(mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY)).latitude, mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY)).longitude);
                }
                if(mouseKeyHandler.mouseState === 1 & mouse.button === Qt.LeftButton)
                {
                    mouseKeyHandler.placeMarker(mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY)).latitude, mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY)).longitude);
                }
                mouse.accepted = false;
            }
        } 

        id: mapView
        anchors.fill: parent;
        layer.smooth: true;
        tilt: 15;
        plugin: Plugin {
            id: mapPluginID;
            name: "osm";
            PluginParameter {
                id: parameterOSM;
                name: "osm.mapping.providersrepository.address";
                value: "file:///"+OsmConfigPath;
            }
            Component.onCompleted: console.info("[MAP] using osmconfig: " + OsmConfigPath);
        }
        
        activeMapType: mapView.supportedMapTypes[defaultMapModeOnTestMode]
        center: QtPositioning.coordinate(defaultLatitude, defaultLongitude);
        zoomLevel: defaultZoom;
        copyrightsVisible: false;
        z: 0;

        Component.onCompleted: { awake(); start(); }

        Behavior on center { CoordinateAnimation { duration: 1000; easing.type: Easing.Linear } }
        Behavior on zoomLevel { NumberAnimation { duration: 100 } }
        onZoomLevelChanged: zoomSliderElement.zoomSliderValue = 1-(mapView.zoomLevel/18);
        onTiltChanged: tiltSliderElement.tiltSliderValue = 1 - (mapView.tilt / 45);

        MapItemView
        {
            model: imageModel;
            add: Transition {
                    NumberAnimation {
                        property: "m_opacity";
                        from: 0;
                        to: 1;
                        duration: 2000;
                        easing.type: Easing.OutCubic;
                    }
            }
            remove: Transition {
                        NumberAnimation {
                            property: "m_opacity";
                            from: 1;
                            to: 0;
                            duration: 2000;
                            easing.type: Easing.OutCubic;
                        }
            }
            delegate: ImageSAR.MapImage { }
        }

        MapItemView
        {
            model: imageUIModel;
            add: Transition {
                    NumberAnimation {
                        property: "m_scale";
                        from: 0;
                        to: 1;
                        duration: 500;
                        easing.type: Easing.OutCubic;
                    }
            }
            remove: Transition {
                        NumberAnimation {
                            property: "m_opacity";
                            from: 1;
                            to: 0;
                            duration: 2000;
                            easing.type: Easing.OutCubic;
                        }
            }
            delegate: ImageSAR.Dialog { }
        }
        MapItemView
        {
            model: markerModel;
            add: Transition {
                    NumberAnimation {
                        property: "m_opacity";
                        from: 0;
                        to: 1;
                        duration: 2000;
                        easing.type: Easing.OutCubic;
                    }
            }
            remove: Transition {
                        NumberAnimation {
                            property: "m_opacity";
                            from: 1;
                            to: 0;
                            duration: 2000;
                            easing.type: Easing.OutCubic;
                        }
            }
            delegate: Marker { }
        }
        MapPolyline { id: mapPolyline; line.width: 5; opacity: 0.75; line.color: Material.primary; path: [ ]; z: 1; }
        MapPolyline { id: rulerLine; line.width: 4; opacity: 0.8; line.color: "#a385cf"; z: 100; path: [ ]; }
        MapPolyline { id: predictLine; line.width: 3; opacity: 0.4; line.color: Material.primary; z: 1; path: [ ]; }
        MapPolygon { id: diagramPoly; border.width: 3; opacity: 0.4; border.color: Material.primary; z: 1; path: []; }
        MapQuickItem {
            property alias rulerRotationAngle: rulerRotation.angle
            id: rulerTextMapItem
            visible: false
            width: 2
            height: 2
            transform: Rotation {
                id: rulerRotation
                origin.x: rulerText.width/2;
                origin.y: rulerText.height/2;
                angle: 0
            }
            anchorPoint.x: rulerText.width/2
            anchorPoint.y: rulerText.height/2
            z:10
            sourceItem: Text {
                id: rulerText;
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                style: Text.Outline
                font.family: "Verdana"
                color: "#a385cf";
                text: "";
            }
        }
        MapQuickItem {
            property alias r1RotationAngle: r1Rotation.angle
            id: r1MapItem
            visible: false
            width: 2
            height: 2
            transform: Rotation {
                id: r1Rotation
                origin.x: r1Source.width;
                origin.y: r1Source.height/2;
                angle: 0
            }
            anchorPoint.x: r1Source.width
            anchorPoint.y: r1Source.height/2
            z: 10;
            sourceItem: Image {
                id: r1Source;
                layer.enabled: true
                transformOrigin: Item.Right
                source: "qrc:/ui-resources/qml/temp.png"
            }
            ColorOverlay {
                id: r1Overlay;
                anchors.fill: r1MapItem;
                source: r1Source;
                opacity: 1;
                color: "#a385cf";
            }
        }
        MapQuickItem {
            property alias r2RotationAngle: r2Rotation.angle
            id: r2MapItem
            visible: false
            width: 2
            height: 2
            transform: Rotation {
                id: r2Rotation
                origin.x: r2Source.width;
                origin.y: r2Source.height/2;
                angle: 0
            }
            anchorPoint.x: r2Source.width
            anchorPoint.y: r2Source.height/2
            z: 10;
            sourceItem: Image {
                id: r2Source;
                layer.enabled: true
                transformOrigin: Item.Right
                source: "qrc:/ui-resources/qml/temp.png"
            }
            ColorOverlay {
                id: r2Overlay;
                anchors.fill: r2MapItem;
                source: r2Source;
                opacity: 1;
                color: "#a385cf";
            }
        }
        MapQuickItem {
            property alias rotationAngle: rotation.angle
            id: planeMapItem
            anchorPoint.x: 20
            anchorPoint.y: 20
            transform: Rotation {
                id: rotation;
                origin.x: 20;
                origin.y: 20;
                angle: 0;
            }
            z: 18;
            sourceItem: Item {
                Image {
                    id: planeSource;
                    layer.enabled: true;
                    transformOrigin: Item.Center;
                    smooth: true;
                    source: "qrc:/ui-resources/qml/gpsarrow.png";
                    visible: false;
                }
                ColorOverlay {
                    id: overlayPlane;
                    anchors.fill: planeSource;
                    source: planeSource;
                    opacity: 0.75;
                    color: Material.primary;
                }
                DropShadow {
                    anchors.fill: overlayPlane;
                    horizontalOffset: 5;
                    verticalOffset: 5;
                    radius: 8.0;
                    samples: 17;
                    color: "#000000";
                    source: overlayPlane;
                }
                Glow {
                    anchors.fill: overlayPlane;
                    radius: 5;
                    samples: 17;
                    color: "#c4bb4b";
                    spread: 0.5;
                    transparentBorder: true;
                    source: overlayPlane;
                }
            }
            Behavior on coordinate {
                CoordinateAnimation {
                    duration: 250
                    easing.type: Easing.Linear
                }
            }
        }
        Groups.ImageToolsGroup
        {
            id: imagePanel;
            // opacity: 0.9;
            anchors.top: parent.top;
            anchors.left: parent.left;
            anchors.topMargin: 3;
            anchors.leftMargin: 3;
        }
        Groups.TelemetryPanel
        {
            id: telemetryPanel;
            Material.background: Material.accent;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 10;
            anchors.horizontalCenter: parent.horizontalCenter;
        }
        FloatingTooltip
        {
            id: mapHoverCoordinatesTooltip;
            visible: true;
            tooltipPadding: 10;
            tooltipText: "Ш: 50.0000000 Д: 30.0000000";
            transparency: 0.5;
        }
        //left to right <<<<<<<<<
        MenuImages
        {
            visible: false; //comment me
            enabled: false; //comment me
            anchors.left: parent.left;
            anchors.top: parent.top;
        }
        ZoomSlider 
        {
            id: zoomSliderElement;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
            anchors.rightMargin: 10;
            anchors.bottomMargin: 10;
            z: 100;
        }
        BottomToolbar
        {
            id: bottomToolbarElement;
            anchors.right: zoomSliderElement.left;
            anchors.rightMargin: 40;
            anchors.bottom: zoomSliderElement.bottom;
            z: 100;
        }
        TiltSlider
        {
            id: tiltSliderElement;
            anchors.left: parent.left;
            anchors.bottom: parent.bottom;
            anchors.leftMargin: 10;
            anchors.bottomMargin: 10;
            z: 100;
        }
        Gesture {
            id: gesture;
            anchors.fill: parent;
        }
    }
    Connections {

    }
}


