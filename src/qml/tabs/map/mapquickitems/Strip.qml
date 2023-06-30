import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

MapQuickItem  {
    required property int index;
    required property string filename;
    required property real latitude;
    required property real longitude;
    required property real dx;
    required property real azimuth;
    required property real lx;
    required property real ly;
    required property real offset_x;
    required property real offset_y;
    required property bool valid;
    required property string lod1;
    required property string lod0;
    required property real transparency;
    required property bool shown;
    required property real mercator_zoom_level;
    required property bool marked_for_export;

    z: 2
    anchorPoint.x: offset_x
    anchorPoint.y: offset_y

    zoomLevel: mercator_zoom_level
    coordinate: QtPositioning.coordinate(latitude, longitude)
    sourceItem: Item {
        Loader {
            active: maptab_root.zoomLevel > 15 ||
                    maptab_root.visibleRegion.contains(QtPositioning.coordinate(latitude, longitude));
            asynchronous: true
            sourceComponent: Image {
                layer {
                    enabled: true
                    smooth: true
                    samples: 8
                }
                asynchronous: true

                // точка вращения
                transform: Rotation {
                    origin.x: 0
                    origin.y: 0
                    angle: azimuth
                }

                smooth: true
                antialiasing: true
                source: "file:" + lod0
            }
        }
    }
}
