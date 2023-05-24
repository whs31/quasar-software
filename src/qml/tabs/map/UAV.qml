import QtQuick 2.15
import Network 1.0
import QtLocation 5.15
import QtPositioning 5.15
import QtGraphicalEffects 1.15

MapQuickItem {
    anchorPoint.x: 20;
    anchorPoint.y: 20;
    transform: Rotation {
        id: rotation;
        origin.x: 20;
        origin.y: 20;
        angle: Network.telemetry.course;
    }
    coordinate: QtPositioning.coordinate(Network.telemetry.latitude, Network.telemetry.longitude);
    z: 18;
    Behavior on coordinate { CoordinateAnimation { duration: 125; easing.type: Easing.Linear; } }

    sourceItem: Item {
        Image {
            id: planeSource;
            layer.enabled: true;
            transformOrigin: Item.Center;
            smooth: true;
            source: "qrc:/map/items/gpsarrow.png";
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
}
