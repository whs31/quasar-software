import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtGraphicalEffects 1.15

import Theme 1.0

MapQuickItem  {
    z: 50;
//    visible: shown;
    anchorPoint.x: 16;
    anchorPoint.y: 16;
    zoomLevel: 0;
    property real m_opacity: 0.85;
    opacity: m_opacity;
    coordinate: QtPositioning.coordinate(latitude, longitude);
    sourceItem: Item {
        Image { id: image_SARImageIcon;
            width: 32;
            height: 32;
            transformOrigin: Item.Center;
            smooth: true;
            source: "qrc:/map/markers/image.png";
            visible: false;
        }

        Rectangle { id: panel_SARImageTooltip;
            color: Theme.color("light0");
            width: (text_ImageIndex.paintedWidth);
            height: (text_ImageIndex.paintedHeight + 3);
            anchors.top: image_SARImageIcon.bottom;
            anchors.topMargin: 5;
            anchors.horizontalCenter: image_SARImageIcon.horizontalCenter;
            radius: width / 2;
            Text { id: text_ImageIndex;
                color: Theme.color("dark0");
                enabled: true;
                anchors.fill: parent;
                font.pointSize: 8;
                font.family: root.mainfont;
                font.weight: Font.Bold;
                textFormat: Text.RichText;
                text: "\u00A0РЛИ №" + Number(index + 1) + "\u00A0";
                horizontalAlignment: Text.AlignHCenter;
                verticalAlignment: Text.AlignVCenter;
            }
        }

        DropShadow {
            anchors.fill: image_SARImageIcon;
            horizontalOffset: 5;
            verticalOffset: 5;
            radius: 8.0;
            samples: 16;
            color: "#000000";
            source: image_SARImageIcon;
        }

    }
}
