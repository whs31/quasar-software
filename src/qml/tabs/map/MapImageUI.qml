import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtLocation 5.15
import QtPositioning 5.15

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
        RoundButton { id: button_openImageDialog;
            icon.source: "qrc:/map/items/image.png";
            height: 44;
            width: 44;
            radius: 15;
            Material.elevation: 30;
            Material.background: Theme.color("dark0");
            icon.color: Theme.color("light1");
        }

        Rectangle { id: panel_SARImageTooltip;
            color: Theme.color("dark0");
            width: (text_ImageIndex.paintedWidth + 5);
            height: (text_ImageIndex.paintedHeight + 3);
            anchors.top: button_openImageDialog.bottom;
            anchors.horizontalCenter: button_openImageDialog.horizontalCenter;
            radius: width / 2;
            Text { id: text_ImageIndex;
                color: Theme.color("light0");
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
    }
}
