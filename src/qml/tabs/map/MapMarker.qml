import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtGraphicalEffects 1.15

MapQuickItem  {
    anchorPoint.x: imageSource.sourceSize.width / 2;
    anchorPoint.y: imageSource.sourceSize.height;
    z: 2;
    visible: true;
    zoomLevel: 0;
    property real m_opacity: 1;
    opacity: m_opacity;
    coordinate: QtPositioning.coordinate(latitude, longitude);
    sourceItem: Item {
        Image { id: imageSource;
            asynchronous: true;
            smooth: true;
            antialiasing: true;
            source: marker_icon;
            visible: false;
            sourceSize.width: 40;
            sourceSize.height: 40;
        }

        ColorOverlay {
            color: marker_color;
            layer.enabled: true;
            layer.smooth: true;
            layer.samples: 8;
            anchors.fill: imageSource;
            source: imageSource;
        }
    }
}
