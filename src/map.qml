import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtLocation 5.12
import QtPositioning 5.12

//import cpp.invoker 1.0


Item {
    id: qqview
    /*Invoker {
        id: invoker
    }*/
    property double latitude: 0.0
    property double longitude: 0.0
    property double elevation: 0.0
    property double velocity: 0.0
    property var panToCurrentlocation: QtPositioning.coordinate(51.660784, 39.200268);

    function getTelemetry(lat, lon, elv, speed)
    {
        latitude = lat; longitude = lon; elevation = elv; velocity = speed;
        //panGPS();
        drawRoute(lat, lon);
    }

    function panGPS()
    {
        mapView.center = panToCurrentlocation;
        panToCurrentlocation = QtPositioning.coordinate(latitude,longitude);
    }

    function drawRoute(lat, lon)
    {
        mapPolyline.addCoordinate(QtPositioning.coordinate(lat,lon));
    }

            Map {
                id: mapView
                visible: true
                anchors.fill: parent
                plugin: Plugin {
                    id: mapPluginID;
                    name: "osm";
                    PluginParameter {
                        name: "osm.mapping.providersrepository.address";
                        value: "file:///home/user/quasar-ui/QuaSAR-UI/osmconfigs";
                    }

                }
                activeMapType: mapView.supportedMapTypes[0]
                center: QtPositioning.coordinate(59.660784, 30.200268);
                zoomLevel: 9
                copyrightsVisible: false
                MapPolyline {
                    id: mapPolyline
                    line.width: 4
                    opacity: 0.8
                    line.color: '#e2c700'
                    path: [ ]
                }
                Behavior on center {
                    CoordinateAnimation {
                        duration: 1000
                        easing.type: Easing.Linear
                    }
                }
            }
}


/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.66;height:480;width:640}
}
##^##*/
