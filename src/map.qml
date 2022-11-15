import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtLocation 5.12
import QtPositioning 5.12
import QtGraphicalEffects 1.0

//import cpp.invoker 1.0


Rectangle {
    id: qqview
    /*Invoker {
        id: invoker
    }*/
    Material.theme: Material.Dark
    Material.accent: Material.Cyan
    Material.primary: Material.Lime

    layer.enabled: true
    layer.samples: 4

    //=================preconfig=======================
    property string vehicle: "helicopter";
    property string antennaPosition: "right";



    property double latitude: 0.0
    property double longitude: 0.0
    property double elevation: 0.0
    property double velocity: 0.0
    property var currentQtCoordinates: QtPositioning.coordinate(59.660784, 30.200268);

    property var followPlane: false;
    property var enableTooltip: true;
    property var enableRoute: true;

    property int r_currentstate: 0;
    property var r_firstpoint: QtPositioning.coordinate(0.0, 0.0);
    property var r_secondpoint: QtPositioning.coordinate(0.0, 0.0);

    function getTelemetry(lat, lon, elv, speed) //called every C_UPDATETIME (0.5 s default)
    {
        latitude = lat; longitude = lon; elevation = elv; velocity = speed;
        drawPlane();
        currentQtCoordinates = QtPositioning.coordinate(latitude,longitude);
        if(followPlane) panGPS(); //@TODO отключает слежение за бортом при нажатии на карту мышью и передает этот факт в cpp
        if(enableRoute) drawRoute(lat, lon);
        speedText.text = Number(speed).toFixed(1);
        elevationText.text = Number(elevation).toFixed(0);
    }

    //--------------------------route&gps--------------------------------------------{
    function drawPlane()
    {
        planeMapItem.coordinate = QtPositioning.coordinate(latitude, longitude);
        var atan = 0.0; var angle = 0.0;
        var coord = QtPositioning.coordinate(latitude, longitude);
        var e = 5;
        if(Math.abs(currentQtCoordinates.distanceTo(coord)) > e && Math.abs(currentQtCoordinates.distanceTo(coord)) > e)
        {
            angle = currentQtCoordinates.azimuthTo(coord);
            planeMapItem.rotationAngle = angle;
        }
    }

    function panGPS()
    {
        mapView.center = currentQtCoordinates;
    }

    function drawRoute(lat, lon)
    {
        mapPolyline.addCoordinate(QtPositioning.coordinate(lat,lon));
    }

    function clearRoute()
    {
        mapPolyline.path = [];
    }

    function changeDrawRoute(arg)
    {
        if(arg===2) { enableRoute=true; } else { enableRoute = false; }
    }

    function changeFollowPlane(arg)
    {
        if(arg===2) { followPlane=true; } else { followPlane = false; }
    }
    //------------------------------------------------------------------------------}

    //-------------------tooltip-------------------------{
    function changeEnableTooltip(arg)
    {
        if(arg===2) { enableTooltip=true; } else { enableTooltip = false; }
    }

    function drawTooltip()
    {
        cursorTooltip.visible = true;
        cursorTooltipText.visible = true;
    }

    function changeTooltipPosition()
    {
        if(enableTooltip)
        {
            if(mapMouseArea.pressed)
            {
                clearTooltip();
            }
            else {
                drawTooltip();
                cursorTooltip.x = mapMouseArea.mouseX;
                cursorTooltip.y = mapMouseArea.mouseY;
                var coordToStr = mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY));
                cursorTooltipText.text = "  ➤Ш: <b><i>"+coordToStr.latitude.toFixed(5)+"</b></i>,   Д: <b><i>"+coordToStr.longitude.toFixed(5)+"</b></i>";
            }
        }
        else {
            clearTooltip();
        }
    }

    function clearTooltip()
    {
        cursorTooltip.visible = false;
        cursorTooltipText.visible = false;
    }
    //---------------------------------------------------}

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


    Map {
        id: mapView
        visible: true
        anchors.fill: parent
        layer.smooth: true
        plugin: Plugin {
            id: mapPluginID;
            name: "osm";
            PluginParameter {
                name: "osm.mapping.providersrepository.address";
                value: "qrc:/osmconfigs";
            }

        }
        activeMapType: mapView.supportedMapTypes[0]
        center: QtPositioning.coordinate(59.660784, 30.200268);
        zoomLevel: 9
        copyrightsVisible: false
        MapPolyline {
            id: mapPolyline
            line.width: 5
            opacity: 0.75
            line.color: Material.accent
            path: [ ]
        }
        MapPolyline {
            id: rulerLine
            line.width: 4
            opacity: 0.8
            line.color: Material.color(Material.Amber, Material.Shade100)
            path: [ ]
        }

        Behavior on center {
            CoordinateAnimation {
                duration: 1000
                easing.type: Easing.Linear //Easing.InOutQuart
            }
        }
        Behavior on zoomLevel {
            NumberAnimation { duration: 100 }
        }

        onZoomLevelChanged: zoomSlider.value = 1-(mapView.zoomLevel/18);
        MouseArea {
            id: mapMouseArea
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onEntered: {
                drawTooltip();
            }
            onPositionChanged: {
                changeTooltipPosition();
                if(r_currentstate === 2)
                {
                    drawRuler();
                    r_secondpoint = mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY));
                    rulerText.text = r_firstpoint.distanceTo(r_secondpoint).toLocaleString(Qt.locale("ru_RU"), 'f', 0) + " м";
                }
            }
            onExited: {
                clearTooltip();
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
                    //aMean(r_firstpoint, r_secondpoint);
                }
                else if(r_currentstate === 3)
                {
                    r_currentstate = 0;
                    clearRuler();

                }
            }
        }
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
            z:5
            sourceItem: Text {
                id: rulerText;
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                style: Text.Outline
                font.family: "Verdana"
                //layer.enabled: true

                color: Material.color(Material.Amber, Material.Shade100)
                text: "-----";
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
            z:5
            sourceItem: Image {
                id: r1Source;
                layer.enabled: true
                transformOrigin: Item.Right
                source: "qrc:/img/right-arrow.png"
            }
            ColorOverlay {
                id: r1Overlay;
                anchors.fill: r1MapItem;
                source: r1Source;
                opacity: 1;
                color: Material.color(Material.Amber, Material.Shade100)
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
            z:5
            sourceItem: Image {
                id: r2Source;
                layer.enabled: true
                transformOrigin: Item.Right
                source: "qrc:/img/right-arrow.png"
            }
            ColorOverlay {
                id: r2Overlay;
                anchors.fill: r2MapItem;
                source: r2Source;
                opacity: 1;
                color: Material.color(Material.Amber, Material.Shade100)
            }
        }
        MapQuickItem {
            property alias rotationAngle: rotation.angle
            id: planeMapItem
            anchorPoint.x: 20
            anchorPoint.y: 20
            transform: Rotation {
                id: rotation
                origin.x: 20;
                origin.y: 20;
                angle: 0
            }
            z:5
            sourceItem: Image {
                id: planeSource;
                layer.enabled: true
                transformOrigin: Item.Center
                source: if(vehicle==="helicopter") { "qrc:/img/helicopter.png" } else { "qrc:/img/plane.png" }
            }
            ColorOverlay {
                id: overlayPlane;
                anchors.fill: planeMapItem;
                source: planeSource;
                opacity: 1;
                color: Material.accent
            }
            Behavior on coordinate {
                CoordinateAnimation {
                    duration: 250
                    easing.type: Easing.Linear
                }
            }
        }
        Component.onCompleted: {
            mapView.addMapItem(planeMapItem);
            zoomSlider.value = 1-(mapView.zoomLevel/18);
        }
        Rectangle {
            id: cursorTooltip
            visible: true
            width: 0
            height: 0
            Rectangle {
                id: tooltip
                color: "#000000"
                width: 148
                height: 15
                radius: 1
                opacity: 0.75
                Text {
                    id: cursorTooltipText
                    color: "#f6f5f4"
                    enabled: false
                    anchors.fill: parent
                    leftPadding: 8
                    font.pointSize: 8
                    minimumPointSize: 8
                    minimumPixelSize: 8
                    textFormat: Text.RichText
                }
            }
        }

        Rectangle {
            id: speedElvRect
            y: 62
            width: 200
            height: 40
            opacity: 0.9
            visible: true
            radius: 18
            color: Material.color(Material.Grey, Material.Shade900)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                id: speedText
                color: Material.primary
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.bold: true
                textFormat: Text.RichText
                anchors.leftMargin: 30
                text: qsTr("---.-")
            }
            Text {
                id: speedTextTT
                color: "#f6f5f4"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: speedText.right
                anchors.leftMargin: 5
                text: qsTr("км/ч")
            }
            Text {
                id: elevationText
                color: Material.primary
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: elevationTextTT.left
                horizontalAlignment: Text.AlignRight
                font.bold: true
                textFormat: Text.RichText
                anchors.rightMargin: 5
                text: qsTr("----")
            }
            Text {
                id: elevationTextTT
                color: "#f6f5f4"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                horizontalAlignment: Text.AlignRight
                anchors.rightMargin: 30
                text: qsTr("м")
            }
        }

        //----------------------zoom slider---------------------------
        RoundButton
        {
            icon.source: "qrc:/img/zoom-out.png"
            icon.color: "black"
            icon.width: 32
            icon.height: 32
            id: zoomOut
            width: 40
            height: 40
            radius: 10
            opacity: 1
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            highlighted: true
            flat: false
            anchors.bottomMargin: 20
            anchors.leftMargin: 30
            hoverEnabled: true
            enabled: true
            display: AbstractButton.IconOnly
            onClicked: mapView.zoomLevel -= 0.5
        }
        Slider
        {
            id: zoomSlider
            width: 40
            height: 200
            live: true
            anchors.bottom: zoomOut.top
            anchors.bottomMargin: 0
            anchors.horizontalCenter: zoomOut.horizontalCenter
            snapMode: Slider.NoSnap
            to: 0
            from: 1
            wheelEnabled: false
            clip: false
            orientation: Qt.Vertical
            value: 1
            onMoved: mapView.zoomLevel = (1-value)*18;
        }
        RoundButton
        {
            icon.source: "qrc:/img/zoom-in.png"
            icon.color: "black"
            icon.width: 32
            icon.height: 32
            id: zoomIn
            width: 40
            height: 40
            radius: 10
            opacity: 1
            anchors.horizontalCenter: zoomOut.horizontalCenter
            anchors.bottom: zoomSlider.top
            highlighted: true
            flat: false
            anchors.bottomMargin: -5
            hoverEnabled: true
            enabled: true
            display: AbstractButton.IconOnly
            onClicked: mapView.zoomLevel += 0.5
        }
        //-------------------------------------------------------------

        RoundButton
        {
            icon.source: "qrc:/img/gps (2).png"
            icon.color: "black"
            icon.width: 32
            icon.height: 32
            id: panButton
            width: 40
            height: 40
            radius: 10
            opacity: 1
            anchors.left: zoomOut.right
            anchors.verticalCenter: zoomOut.verticalCenter
            highlighted: true
            flat: false
            anchors.leftMargin: 0
            hoverEnabled: true
            enabled: true
            display: AbstractButton.IconOnly
            onClicked: panGPS()
        }

        RoundButton
        {
            icon.source: "qrc:/img/ruler (1).png"
            icon.color: "black"
            icon.width: 32
            icon.height: 32
            id: rulerButton
            width: 40
            height: 40
            radius: 10
            opacity: 1
            anchors.left: panButton.right
            anchors.verticalCenter: panButton.verticalCenter
            highlighted: true
            flat: false
            anchors.leftMargin: 0
            hoverEnabled: true
            enabled: true
            display: AbstractButton.IconOnly
            onClicked:
            {
                if(r_currentstate !== 0) { r_currentstate = 1;
                    clearRuler(); } else {
                    r_currentstate = 1;
                }
            }
        }

        RoundButton
        {
            icon.source: "qrc:/img/picture.png"
            icon.color: "black"
            icon.width: 32
            icon.height: 32
            id: panImageButton
            width: 40
            height: 40
            radius: 10
            opacity: 1
            anchors.left: rulerButton.right
            anchors.verticalCenter: rulerButton.verticalCenter
            highlighted: true
            flat: false
            anchors.leftMargin: 0
            hoverEnabled: true
            enabled: true
            display: AbstractButton.IconOnly
            onClicked:
            {
                console.log("panned");
            }
        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.01;height:480;width:640}
}
##^##*/
