import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

MapQuickItem  {
    required property int    index
    required property var    chunkCoordinate
    required property real   chunkAzimuth
    required property point  chunkOffset
    required property size   chunkSize
    required property real   chunkZoomLevel
    required property real   chunkOpacity
    required property bool   chunkVisibility
    required property string base64

    z: 2
    anchorPoint: chunkOffset
    zoomLevel: chunkZoomLevel
    coordinate: chunkCoordinate
    visible: chunkVisibility
    opacity: chunkOpacity
    sourceItem: Item {
        Loader {
            active: maptab_root.zoomLevel > 15 ||
                    maptab_root.visibleRegion.contains(chunkCoordinate);
            asynchronous: true
            sourceComponent: Image {
                asynchronous: true

                // точка вращения
                //rotation: chunkAzimuth
                transform: Rotation {
                    origin: chunkOffset
                    angle: chunkAzimuth
                }

                smooth: true
                antialiasing: true
                source: "data:image/png;base64," + base64
            }
        }
    }
}
