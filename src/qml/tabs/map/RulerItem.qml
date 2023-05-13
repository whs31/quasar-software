import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15
import Theme 1.0

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
            line.color: Theme.color("color3");
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
                color: Theme.color("color2");
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
                color: Theme.color("color2");
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
                border.color: Theme.color("color2");
                color: Theme.color("color2");
                visible: true;

                Text {
                    id: segmentLengthText;
                    anchors.centerIn: parent;
                    text: segmentLength < 10000 ? Number(segmentLength).toFixed(0) + " м" : Number(segmentLength / 1000).toFixed(1) + " км"
                    font.family: root.mainfont;
                    font.bold: true;
                    color: Theme.color("dark0");
                }
            }
        }
    }
}
