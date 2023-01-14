import QtQuick 2.12
import RuntimeData 1.0

Item {
    id: base;
    width: childrenRect.width;
    height: childrenRect.height;
    Rectangle
    {
        id: bground;
        width: 300;
        height: 22;
        color: "#173846";
        border.color: "#2B6781";
        border.width: 2;
        radius: 5;
        Text {
            id: latitudeText;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: -1;
            anchors.left: parent.left;
            anchors.leftMargin: 9;
            color: "#dae1e5";
            font.capitalization: Font.MixedCase;
            font.pixelSize: 12;
            textFormat: Text.RichText
            text: "Широта: " + "<font color=\"#43a1ca\"><b>" + Number(RuntimeData.latitude).toFixed(6) + "°N";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Text {
            id: longitudeText;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: -1;
            anchors.right: parent.right;
            anchors.rightMargin: 9;
            color: "#dae1e5";
            font.capitalization: Font.MixedCase;
            font.pixelSize: 12;
            textFormat: Text.RichText
            text: "Долгота: " + "<font color=\"#43a1ca\"><b>" + Number(RuntimeData.longitude).toFixed(6) + "°E";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
    }
    Rectangle
    {
        id: fground;
        width: childrenRect.width + 15;
        height: 12;
        color: "#2B6781";
        anchors.horizontalCenter: bground.horizontalCenter;
        anchors.verticalCenter: bground.bottom;
        Text {
            id: fgroundText
            text: "ПОЛОЖЕНИЕ БОРТА";
            font.bold: true;
            font.pointSize: 7;
            horizontalAlignment: Text.AlignHCenter;
            anchors.centerIn: parent;
            color: "#dae1e5";
        }
    }
}
