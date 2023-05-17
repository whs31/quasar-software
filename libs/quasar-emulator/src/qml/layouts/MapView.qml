import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtGraphicalEffects 1.15
import Telemetry 1.0

Map {
    center: QtPositioning.coordinate(Telemetry.latitude, Telemetry.longitude);
    opacity: 0.75;
    zoomLevel: 15;
    tilt: 45;
    activeMapType: supportedMapTypes[1];
    copyrightsVisible: false;
    plugin: Plugin {
        name: "osm";

        PluginParameter {
            name: "osm.mapping.providersrepository.address";
            value: "file:///" + Telemetry.getOsmConfig();
        }

        Component.onCompleted: console.info("[MAP] Using osmconfig: " + Telemetry.getOsmConfig());
    }
    Behavior on center { CoordinateAnimation { duration: 500; easing.type: Easing.Linear } }
    Behavior on zoomLevel { NumberAnimation { duration: 100 } }
    focus: true;
    Keys.onPressed: (event)=> {
                        if(event.key === Qt.Key_L)
                            console.log("Debug key pressed");
                        if (event.key === Qt.Key_D)
                            root.yaw = 1;
                        if (event.key === Qt.Key_A)
                            root.yaw = -1;
                        if (event.key === Qt.Key_W)
                            root.pitch = 1;
                        if (event.key === Qt.Key_S)
                            root.pitch = -1;
                        if (event.key === Qt.Key_Q)
                            root.roll = -1;
                        if (event.key === Qt.Key_E)
                            root.roll = 1;
    }
    Keys.onReleased: (event)=> {
                         if (event.key === Qt.Key_D)
                             root.yaw = 0;
                         if (event.key === Qt.Key_A)
                             root.yaw = 0;
                         if (event.key === Qt.Key_W)
                             root.pitch = 0;
                         if (event.key === Qt.Key_S)
                             root.pitch = 0;
                         if (event.key === Qt.Key_Q)
                             root.roll = 0;
                         if (event.key === Qt.Key_E)
                             root.roll = 0;
    }

    MapQuickItem {
        anchorPoint.x: 20;
        anchorPoint.y: 20;
        transform: Rotation {
            id: rotation;
            origin.x: 20;
            origin.y: 20;
            angle: Telemetry.course;
        }
        coordinate: QtPositioning.coordinate(Telemetry.latitude, Telemetry.longitude);
        z: 18;
        sourceItem: Item {
            Image {
                id: planeSource;
                layer.enabled: true;
                transformOrigin: Item.Center;
                smooth: true;
                source: "qrc:/images/gpsarrow.png";
                visible: false;
            }
            ColorOverlay {
                id: overlayPlane;
                anchors.fill: planeSource;
                source: planeSource;
                opacity: 0.75;
                color: "#ebcb8b";
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
                color: "#ebcb8b";
                spread: 0.5;
                transparentBorder: true;
                source: overlayPlane;
            }
        }
        Behavior on coordinate {
            CoordinateAnimation {
                duration: 250;
                easing.type: Easing.Linear;
            }
        }
    }
}
