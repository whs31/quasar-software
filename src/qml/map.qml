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
    Material.accent: "#EEE1C6"
    Material.primary: "#E59E6D"

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
        property string m_provider: "osm";            //|
        property int m_mapMode: 0;                    //|
        property bool c_USEBASE64: false;             //|
    //==================================================|


    property double latitude: 0.0
    property double longitude: 0.0
    property double elevation: 0.0
    property double velocity: 0.0
    property var currentQtCoordinates: QtPositioning.coordinate(59.660784, 30.200268); //in case of no connection
    property var imageArray: []

    //-------widgets ui checkboxes------
    property bool followPlane: false;
    property bool enableTooltip: true;
    property bool enableRoute: true;
    property bool enablePredict: true;
    property bool enableDiagram: true;
    //----------------------------------


    //ruler
    property int r_currentstate: 0;
    property var r_firstpoint: QtPositioning.coordinate(0.0, 0.0);
    property var r_secondpoint: QtPositioning.coordinate(0.0, 0.0);
    property int fc: 0;

    //called every C_UPDATETIME (0.5 s default)
    function getTelemetry(lat, lon, elv, speed)
    {
        latitude = lat; longitude = lon; elevation = elv; velocity = speed;
        drawPlane();
        currentQtCoordinates = QtPositioning.coordinate(latitude,longitude);
        if(followPlane) panGPS();
        if(enableRoute) drawRoute(lat, lon);
        speedText.text = Number(speed).toFixed(1);
        elevationText.text = Number(elevation).toFixed(0);
    }

    function loadSettings(d1, d2, d3, d4, d5, s1, s2, testmode, usebase64, cfgpath)
    {
        if(testmode)
        {
            m_provider = "osm";
            m_mapMode = 3;
        } else {
            m_provider = "osm";
            m_mapMode = 0;
        }

        c_ANTENNAPOSITION = s1;
        c_PATH = s2;
        c_PREDICTRANGE = d1;
        c_DIAGRAMLENGTH = d2;
        c_CAPTURETIME = d3;
        c_DIAGRAMAZIMUTH = d4;
        c_DRIFTANGLE = d5;
        c_USEBASE64 = usebase64;
        console.log("[QML] Config loaded in qml");
    }

    //--------------------------SAR images-------------------------------------------{
    function clearImageArray()
    {
        for (var i = 0; i < imageArray.length; i++)  {
              hideImage(i);
              mapView.removeMapItem(imageArray[i]);
          }
        imageArray = [];
    }

    function addImage(centerlat, centerlon, dx, dy, x0, y0, angle, filename, h, base64encoding)
    {
        var item = Qt.createQmlObject('
                                                    import QtQuick 2.0;
                                                    import QtLocation 5.12;

                                                    MapQuickItem {
                                                        id: imageItem
                                                        z:1

                                                    }
    ', mapView, "dynamic");
        //one degree = 111 120 meters
        item.anchorPoint.x = -x0;
        item.anchorPoint.y = h/2;
        item.coordinate = QtPositioning.coordinate(centerlat, centerlon);
        if(!c_USEBASE64)
        {
            console.log("[QML] Displaying image from " + filename);
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
            ', mapView, "dynamic");
        } else {
            console.log("[QML] Displaying image from base64 string");
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
                                                            source: "data:image/png;base64,'+ base64encoding +'"
                                                            visible: true
                                                        }

                                                    }
            ', mapView, "dynamic");
        }

        if(dx!==0) { item.zoomLevel = log(2, 156543.03392*Math.cos(centerlat*Math.PI/180)/dx); } else { item.zoomLevel = log(2, 156543.03392*Math.cos(centerlat*Math.PI/180)/1); }
                                        //metersPerPx = 156543.03392 * Math.cos(latLng.lat() * Math.PI / 180) / Math.pow(2, zoom) где latLng - anchor point РЛИ и zoom - зум карты
                                        //zoom = log2((156543.03392*cos(PI*lat/180))/dx)
        mapView.addMapItem(item);
        imageArray.push(item);
    }

    function log(base, exponent) { return Math.log(exponent) / Math.log(base); }

    function hideImage(filecounter)
    {
        imageArray[filecounter].visible = false;
        imageArray[filecounter].enabled = false;
    }

    function showImage(filecounter)
    {
        imageArray[filecounter].visible = true;
        imageArray[filecounter].enabled = true;
        fc = filecounter;
    }

    function panImage(filecounter)
    {
        console.log("[QML] Map centered on image");
        mapView.center = imageArray[filecounter].coordinate;
        fc = filecounter;
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
            if(enablePredict) { drawPredict(angle); }
        }
    }

    function drawPredict(angle)
    {
        predictLine.path = [];
        var p_lat = latitude+Math.sin((90-angle)*Math.PI/180) * (c_PREDICTRANGE*0.00899928);
        var p_lon = longitude+Math.cos((90-angle)*Math.PI/180) * (c_PREDICTRANGE*0.00899928);
        predictLine.addCoordinate(QtPositioning.coordinate(latitude, longitude));
        predictLine.addCoordinate(QtPositioning.coordinate(p_lat, p_lon));
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
        if(arg===2) { followPlane=true; } else { followPlane = false; timer_3s.stop(); }
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
            name: m_provider;
            PluginParameter {
                id: parameterOSM;
                name: "osm.mapping.providersrepository.address";
                value: "file:///"+ApplicationDirPath+"/maptsc";
            }
            Component.onCompleted: console.log(parameterOSM.value);

        }
        activeMapType: mapView.supportedMapTypes[m_mapMode]
        center: QtPositioning.coordinate(59.660784, 30.200268);
        zoomLevel: 9
        copyrightsVisible: false

        MapPolyline { id: mapPolyline; line.width: 5; opacity: 0.75; line.color: Material.accent; path: [ ]; z: 10; }
        MapPolyline { id: rulerLine; line.width: 4; opacity: 0.8; line.color: Material.color(Material.Amber, Material.Shade100); z: 10; path: [ ]; }
        MapPolyline { id: predictLine; line.width: 3; opacity: 0.2; line.color: Material.accent; z: 9; path: [ ]; }
        MapPolygon { id: diagramPoly; border.width: 3; opacity: 0.4; border.color: Material.accent; z: 9; path: []; }

        Behavior on center { CoordinateAnimation { duration: 1000; easing.type: Easing.Linear } }
        Behavior on zoomLevel { NumberAnimation { duration: 100 } }
        onZoomLevelChanged: zoomSlider.value = 1-(mapView.zoomLevel/18);
        MouseArea {
            id: mapMouseArea
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onEntered: { drawTooltip(); }
            onPositionChanged: {
                changeTooltipPosition();
                if(r_currentstate === 2)
                {
                    drawRuler();
                    r_secondpoint = mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY));
                    rulerText.text = r_firstpoint.distanceTo(r_secondpoint).toLocaleString(Qt.locale("ru_RU"), 'f', 0) + " м";
                }
            }
            onExited: { clearTooltip(); }
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
            onPressed: {
                if(followPlane||timer_3s.running) {
                    followPlane = false;
                    timer_3s.restart();
                    numAnim1.restart();
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
            z:6
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
                source: "qrc:/ui-resources/right-arrow-map.png"
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
                source: "qrc:/ui-resources/right-arrow-map.png"
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
                source: "qrc:/ui-resources/qml_gpsarrow.png"
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
        Component.onCompleted: { mapView.addMapItem(planeMapItem); zoomSlider.value = 1-(mapView.zoomLevel/18); }
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

        ProgressBar {
            id: cameraGrip;
            opacity: 0.3;
            anchors.top: speedElvRect.bottom;
            anchors.left: speedElvRect.left;
            anchors.right: speedElvRect.right;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 40;
            from: 0;
            to: 3000;
            value: 0
            NumberAnimation on value {
                id: numAnim1
                from: 0
                to: 3000
                duration: 3000
            }

        }

        //----------------------zoom slider---------------------------
        RoundButton
        {
            icon.source: "qrc:/ui-resources/b_zoomout.png"
            icon.color: "black"
            icon.width: 32
            icon.height: 32
            id: zoomOut
            width: 40
            height: 40
            radius: 10
            opacity: 1
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            highlighted: true
            flat: false
            anchors.bottomMargin: 20
            anchors.rightMargin: 30
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
            icon.source: "qrc:/ui-resources/b_zoomin.png"
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
            icon.source: "qrc:/ui-resources/b_plane.png"
            icon.color: "black"
            icon.width: 32
            icon.height: 32
            id: panButton
            width: 40
            height: 40
            radius: 10
            opacity: 1
            z: 100
            anchors.right: zoomOut.left
            anchors.verticalCenter: zoomOut.verticalCenter
            highlighted: true
            flat: false
            anchors.rightMargin: 0
            hoverEnabled: true
            enabled: true
            display: AbstractButton.IconOnly
            onClicked: panGPS()
        }

        RoundButton
        {
            icon.source: "qrc:/ui-resources/b_ruler.png"
            icon.color: "black"
            icon.width: 32
            icon.height: 32
            id: rulerButton
            width: 40
            height: 40
            radius: 10
            opacity: 1
            z: 100
            anchors.right: panButton.left
            anchors.verticalCenter: panButton.verticalCenter
            highlighted: true
            flat: false
            anchors.rightMargin: 0
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
            icon.source: "qrc:/ui-resources/b_imagemarker.png"
            icon.color: "black"
            icon.width: 32
            icon.height: 32
            id: panImageButton
            width: 40
            height: 40
            radius: 10
            z: 100
            opacity: 1
            anchors.right: rulerButton.left
            anchors.verticalCenter: rulerButton.verticalCenter
            highlighted: true
            flat: false
            anchors.rightMargin: 0
            hoverEnabled: true
            enabled: true
            display: AbstractButton.IconOnly
            onClicked:
            {
                panImage(fc);
                //dont follow plane for a while
                if(followPlane)
                {
                    followPlane = false;
                    timer_3s.restart();
                    numAnim1.restart();
                }
        }
        Timer { id: timer_3s; interval: 3000; running: false; repeat: false; onTriggered: { followPlane = true; cameraGrip.value = 0; } }
    }
}
}


