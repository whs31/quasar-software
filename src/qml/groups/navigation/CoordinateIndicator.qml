import QtQuick 2.12
import RuntimeData 1.0
import UX 1.0

Item {
    id: base;
    width: childrenRect.width;
    height: childrenRect.height;
    Rectangle
    {
        id: bground;
        width: 325;
        height: 30;
        color: UX.infoDarker;
        border.color: UX.infoDark;
        border.width: 2;
        radius: 15;
        Text {
            id: latitudeText;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: -1;
            anchors.left: parent.left;
            anchors.leftMargin: 9;
            color: UX.textWhite;
            font.capitalization: Font.MixedCase;
            font.pixelSize: 13;
            textFormat: Text.RichText
            text: "<font color=\"#43a1ca\"><b>Широта: </font><b>"  + Number(RuntimeData.latitude).toFixed(6) + "<font color=\"#b2b9bb\"><b>°N";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
        Text {
            id: longitudeText;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: -1;
            anchors.right: parent.right;
            anchors.rightMargin: 9;
            color: UX.textWhite;
            font.capitalization: Font.MixedCase;
            font.pixelSize: 13;
            textFormat: Text.RichText
            text: "<font color=\"#43a1ca\"><b>Долгота: </font><b>"  + Number(RuntimeData.longitude).toFixed(6) + "<font color=\"#b2b9bb\"><b>°E";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
    }
    Rectangle
    {
        id: fground;
        width: fgroundText.paintedWidth + 15;
        height: 14;
        color: UX.infoDark;
        anchors.horizontalCenter: bground.horizontalCenter;
        anchors.verticalCenter: bground.bottom;
        anchors.verticalCenterOffset: 1;
        Text {
            id: fgroundText
            text: "ПОЛОЖЕНИЕ БОРТА";
            font.bold: true;
            font.pointSize: 8;
            horizontalAlignment: Text.AlignHCenter;
            anchors.centerIn: parent;
            color: UX.textWhite;
        }
    }
}
