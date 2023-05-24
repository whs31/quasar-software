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

        Rectangle { id: panel_MarkerTooltip;
            color: marker_color;
            width: (text_MarkerName.paintedWidth + 5);
            height: (text_MarkerName.paintedHeight + 1);
            anchors.top: imageSource.bottom;
            anchors.topMargin: 4;
            anchors.horizontalCenter: imageSource.horizontalCenter;
            radius: width / 2;
            Text { id: text_MarkerName;
                color: "black";
                enabled: true;
                anchors.fill: parent;
                font.pointSize: 8;
                font.family: root.mainfont;
                font.weight: Font.Bold;
                textFormat: Text.RichText;
                text: "\u00A0" + marker_name + "\u00A0";
                horizontalAlignment: Text.AlignHCenter;
                verticalAlignment: Text.AlignVCenter;
            }
        }
    }
}
