import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtGraphicalEffects 1.15

MapQuickItem {
    coordinate: gpsSource.position.coordinate
    zoomLevel: 0
    anchorPoint.x: 16
    anchorPoint.y: 16
    sourceItem: Image {
        source: "qrc:/icons/vector/network/antenna.svg"
        smooth: true
        antialiasing: true
        sourceSize.width: 32
        sourceSize.height: 32
        layer {
            enabled: true
            effect: ColorOverlay {
                color: theme.green
            }
        }
    }

    PositionSource {
        id: gpsSource
        updateInterval: 1000
        active: true
        preferredPositioningMethods: PositionSource.AllPositioningMethods
    }
}
