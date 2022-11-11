import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtLocation 5.12
import QtPositioning 5.12
import QtGraphicalEffects 1.0

//import cpp.invoker 1.0


Rectangle {
    id: qqview
    /*Invoker {
        id: invoker
    }*/
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

    function getTelemetry(lat, lon, elv, speed)
    {
        latitude = lat; longitude = lon; elevation = elv; velocity = speed;
        drawPlane();
        currentQtCoordinates = QtPositioning.coordinate(latitude,longitude);
        if(followPlane) panGPS(); //@TODO отключает слежение за бортом при нажатии на карту мышью и передает этот факт в cpp
        if(enableRoute) drawRoute(lat, lon);
    }

    //--------------------------route&gps--------------------------------------------{
    function drawPlane()
    {
        planeMapItem.coordinate = QtPositioning.coordinate(latitude, longitude);
        var atan = 0.0; var angle = 0.0;
        var e = 0.000001;
        if(Math.abs(longitude-currentQtCoordinates.longitude)>e&&Math.abs(latitude-currentQtCoordinates.latitude)>e)
        {
            atan = Math.atan2(longitude-currentQtCoordinates.longitude, latitude-currentQtCoordinates.latitude);
            angle = (atan*180)/Math.PI;
            //console.log(angle);
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
                value: "file:///home/user/quasar-ui/QuaSAR-UI/osmconfigs"; //@TODO убрать хардкод
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
            line.color: '#FFF5EE'
            path: [ ]
        }
        Behavior on center {
            CoordinateAnimation {
                duration: 1000
                easing.type: Easing.Linear //Easing.InOutQuart
            }
        }
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
            }
            onExited: {
                clearTooltip();
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
                color: "#FFF5EE"
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
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.66;height:480;width:640}
}
##^##*/
