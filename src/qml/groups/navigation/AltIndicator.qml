import QtQuick 2.12
import RuntimeData 1.0

Item {
    id: base;
    width: childrenRect.width;
    height: childrenRect.height;
    Rectangle
    {
        id: bground;
        width: 22;
        height: 180;
        color: "#132623";
        border.color: "#204040";
        border.width: 2;
        radius: 3;
    }
    Rectangle
    {
        id: fground;
        width: 70;
        height: 36;
        radius: 2;
        color: "#27183d";
        border.width: 2;
        border.color: "#4b2e75";
        anchors.left: bground.left;
        anchors.verticalCenter: bground.verticalCenter;
        Rectangle
        {
            id: labelBG;
            width: 70;
            height: 13;
            radius: 2;
            color: "#4b2e75";
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: parent.top;
            Text {
                id: labelText
                text: "ВЫСОТА";
                font.bold: true;
                font.pointSize: 7;
                horizontalAlignment: Text.AlignHCenter;
                anchors.centerIn: parent;
                color: "#dae1e5";
            }
        }
        Text {
            id: altText;
            anchors.top: labelBG.bottom;
            anchors.topMargin: 2;
            //anchors.verticalCenterOffset: -1;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.horizontalCenterOffset: -4;
            color: "#dae1e5";
            font.capitalization: Font.MixedCase;
            font.pixelSize: 14;
            textFormat: Text.RichText
            text: "<font color=\"#dae1e5\"><b>" + Number(RuntimeData.elevation).toFixed(0) + "</font></b>";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
        }
        Text {
            id: altTextTooltip;
            anchors.verticalCenter: altText.verticalCenter;
            anchors.left: altText.right;
            anchors.leftMargin: 2;
            color: "#a385cf";
            font.capitalization: Font.MixedCase;
            font.pixelSize: 10;
            textFormat: Text.RichText;
            font.bold: true;
            text: "м";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
        }
    }
}
