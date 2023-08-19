import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

MapItemView { id: orthodromSegments;
    property real fl_LastLatitude: 0;
    property real fl_LastLongitude: 0;

    z: 100;
    visible: true;
    model: c_RulerModel;
    delegate: MapItemGroup {
        id: orthodromSegmentsItems;

        MapPolyline {
            id: segmentItem;
            line.color: theme.sapphire
            line.width: 5;
            antialiasing: true;
            path: segment;
        }

        MapQuickItem {
            coordinate: QtPositioning.coordinate(fl_LastLatitude, fl_LastLongitude);
            visible: fl_LastLongitude !== 0;
            zoomLevel: 0;
            anchorPoint.x: 8;
            anchorPoint.y: 8;
            sourceItem: Rectangle {
                width: 16;
                height: 16;
                radius: 8;
                color: theme.sky
            }
        }

        MapQuickItem {
            coordinate: segment[0];
            zoomLevel: 0;
            anchorPoint.x: 8;
            anchorPoint.y: 8;
            sourceItem: Rectangle {
                width: 16;
                height: 16;
                radius: 8;
                color: theme.sky
            }
        }

        MapQuickItem {
            coordinate: segmentCenter;
            anchorPoint.x: segmentLegthItem.width / 2;
            anchorPoint.y: segmentLegthItem.height / 2;

            sourceItem: Rectangle {
                id: segmentLegthItem;
                width: segmentLengthText.width * 1.1;
                height: segmentLengthText.height * 1.1;
                radius: 4;
                border.width: 1;
                border.color: theme.sky
                color: theme.sky
                visible: true;

                Text {
                    id: segmentLengthText;
                    anchors.centerIn: parent;
                    text: segmentLength < 10000 ? Number(segmentLength).toFixed(0) + " м" : Number(segmentLength / 1000).toFixed(1) + " км"
                    font.family: root.mainfont;
                    font.bold: true;
                    color: theme.base
                }
            }
        }
    }
}
