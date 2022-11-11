import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtLocation 5.12
import QtPositioning 5.12

//import cpp.invoker 1.0


Rectangle {
    id: qqview
    /*Invoker {
        id: invoker
    }*/
    layer.enabled: true
    layer.samples: 4
    property double latitude: 0.0
    property double longitude: 0.0
    property double elevation: 0.0
    property double velocity: 0.0
    property var currentQtCoordinates: QtPositioning.coordinate(51.660784, 39.200268);

    property var enableTooltip: true;

    function getTelemetry(lat, lon, elv, speed)
    {
        latitude = lat; longitude = lon; elevation = elv; velocity = speed;
        //panGPS();
        drawRoute(lat, lon);
    }

    function panGPS()
    {
        mapView.center = currentQtCoordinates;
        currentQtCoordinates = QtPositioning.coordinate(latitude,longitude);
    }

    function drawRoute(lat, lon)
    {
        mapPolyline.addCoordinate(QtPositioning.coordinate(lat,lon));
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
            line.color: '#00FFFF'
            path: [ ]
        }
        Behavior on center {
            CoordinateAnimation {
                duration: 1000
                easing.type: Easing.Linear
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
