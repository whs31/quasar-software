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

    //=====================config=======================|
        property string c_VEHICLE: "helicopter";      //|
        property string c_ANTENNAPOSITION: "right";   //|
        property string c_PATH: "file:///";           //|
        property double c_PREDICTRANGE: 0.0;          //|
        property double c_DIAGRAMLENGTH: 0.0;         //|
        property double c_CAPTURETIME: 0.0;           //|
        property double c_DIAGRAMAZIMUTH: 0.0;        //|
        property double c_DRIFTANGLE: 0.0;            //|
    //==================================================|

    property double latitude: 0.0
    property double longitude: 0.0
    property double elevation: 0.0
    property double velocity: 0.0
    property var currentQtCoordinates: QtPositioning.coordinate(59.660784, 30.200268); //in case of no connection
    property var imageArray: []

    //-------widgets ui checkboxes------
    property var followPlane: false;
    property var enableTooltip: true;
    property var enableRoute: true;
    //----------------------------------


    //ruler
    property int r_currentstate: 0;
    property var r_firstpoint: QtPositioning.coordinate(0.0, 0.0);
    property var r_secondpoint: QtPositioning.coordinate(0.0, 0.0);

    //called every C_UPDATETIME (0.5 s default)
    function getTelemetry(lat, lon, elv, speed)
    {
        latitude = lat; longitude = lon; elevation = elv; velocity = speed;
        drawPlane();
        currentQtCoordinates = QtPositioning.coordinate(latitude,longitude);
        if(followPlane) panGPS(); //@TODO отключает слежение за бортом при нажатии на карту мышью и передает этот факт в cpp
        if(enableRoute) drawRoute(lat, lon);
        speedText.text = Number(speed).toFixed(1);
        elevationText.text = Number(elevation).toFixed(0);
        //console.log(imageArray.length);
    }

    function loadSettings(d1, d2, d3, d4, d5, s1, s2)
    {
        c_ANTENNAPOSITION = s1;
        c_PATH = s2;
        c_PREDICTRANGE = d1;
        c_DIAGRAMLENGTH = d2;
        c_CAPTURETIME = d3;
        c_DIAGRAMAZIMUTH = d4;
        c_DRIFTANGLE = d5;
        console.log("[QML] Config loaded in qml");
    }

    //--------------------------SAR images-------------------------------------------{
    function clearImageArray()
    {
        for (var i = 0; i < imageArray.length; i++)  {
              hideImage(i);
          }
        imageArray = [];
    }

    function addImage(centerlat, centerlon, dx, dy, x0, y0, angle, filename, h)
    {
        console.log("[QML] Displaying image from " + filename);
        var item = Qt.createQmlObject('
                                                    import QtQuick 2.0;
                                                    import QtLocation 5.12;

                                                    MapQuickItem {
                                                        id: imageItem
                                                        z:1

                                                    }
    ', mapView, "dynamic"); //3000x1273 hardcoded f now
        //one degree = 111 120 meters
        item.anchorPoint.x = -x0;
        item.anchorPoint.y = h/2;
        console.log("H is "+h)
        item.coordinate = QtPositioning.coordinate(centerlat, centerlon);

        item.sourceItem = Qt.createQmlObject('
                                                    import QtQuick 2.0;
                                                    import QtGraphicalEffects 1.12;

                                                    Rectangle {
                                                        opacity: 1;
                                                        transform: Rotation {
                                                            id: imageRotation
                                                            origin.x: -'+x0+'
                                                            origin.y: imageSource.height/2;
                                                            angle: '+angle+'
                                                        }

                                                        Image {
                                                            id: imageSource;
                                                            opacity: 1;
                                                            source: "file:///'+ filename +'"
                                                            visible: true
                                                        }

                                                    }
            ', mapView, "dynamic"); /*
                                                        Image {
                                                            id: mask
                                                            source: "qrc:/img-deprecated/jpeg_opacityMask.png"
                                                            sourceSize: Qt.size(imageSource.width, imageSource.height)
                                                            visible: false
                                                        }
                                                        OpacityMask {
                                                            anchors.fill: imageSource
                                                            source: imageSource
                                                            maskSource: mask
                                                        }
                                                        */
        item.zoomLevel = log(2, 156543.03392*Math.cos(centerlat*Math.PI/180)/dx);
                                        //https://developer.here.com/documentation/data-layers/dev_guide/topics/zoom-levels.html **deprecated**
                                        //metersPerPx = 156543.03392 * Math.cos(latLng.lat() * Math.PI / 180) / Math.pow(2, zoom) где latLng - anchor point РЛИ и zoom - зум карты
                                        //dx = metersPerPx (без учета dy)
                                        //zoom = log2((156543.03392*cos(PI*lat/180))/dx)
        mapView.addMapItem(item);
        imageArray.push(item); //если изображения будут отображены не по очереди, то все ломается
        //change opacity of newly created jpg
    }

    function log(base, exponent) { return Math.log(exponent) / Math.log(base); }

    function hideImage(filecounter)
    {
        imageArray[filecounter].visible = false;
        imageArray[filecounter].enabled = false;
        console.log("[QML] Image hidden", filecounter);
    }

    function showImage(filecounter)
    {
        imageArray[filecounter].visible = true;
        imageArray[filecounter].enabled = true;
        console.log("[QML] Image shown", filecounter);
    }

    function panImage(filecounter)
    {
        console.log("[QML] Map centered on image");
        mapView.center = imageArray[filecounter].coordinate;
        //mapView.zoomLevel = 14
    }
    //-------------------------------------------------------------------------------}

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
            z: 10
        }
        MapPolyline {
            id: rulerLine
            line.width: 4
            opacity: 0.8
            line.color: Material.color(Material.Amber, Material.Shade100)
            z: 10
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
                source: "qrc:/img/right-arrow-map.png"
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
                source: "qrc:/img/right-arrow-map.png"
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
                source: if(c_VEHICLE==="helicopter") { "qrc:/img/helicopter.png" } else { "qrc:/img/plane.png" }
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
            z: 12
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
            z: 100
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
            z: 100
        }
        Slider
        {
            id: zoomSlider
            width: 40
            height: 200
            z: 100
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
            z: 100
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
            z: 100
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
            z: 100
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
            z: 100
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
                console.log("panned"); // remove this
            }
        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.01;height:480;width:640}
}
##^##*/
