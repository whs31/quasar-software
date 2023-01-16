import QtQuick 2.12
import RuntimeData 1.0

Item {
    id: base;
    width: childrenRect.width;
    height: childrenRect.height;
    property bool speedDisplayMode: false;

    Rectangle
    {
        id: bground;
        width: 26;
        height: 180;
        color: "#132623";
        border.color: "#204040";
        border.width: 2;
        radius: 13;
    }
    Rectangle
    {
        id: fground;
        width: 80;
        height: 40;
        radius: 2;
        color: "#372b07";
        border.width: 2;
        border.color: "#886911";
        anchors.right: bground.right;
        anchors.verticalCenter: bground.verticalCenter;
        MouseArea
        {
            id: changeSpeedModeArea;
            propagateComposedEvents: true;
            anchors.fill: parent;
            onClicked:
            {
                if(speedDisplayMode === true)
                {
                    speedDisplayMode = false;
                } else {
                    speedDisplayMode = true;
                }
            }
        }

        Rectangle
        {
            id: labelBG;
            width: 80;
            height: 13;
            radius: 2;
            color: "#886911";
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: parent.top;
            Text {
                id: labelText
                text: "СКОРОСТЬ";
                font.bold: true;
                font.pointSize: 8;
                horizontalAlignment: Text.AlignHCenter;
                anchors.centerIn: parent;
                color: "#dae1e5";
            }
        }
        Text {
            id: speedText;
            anchors.top: labelBG.bottom;
            anchors.topMargin: 1;
            //anchors.verticalCenterOffset: -1;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.horizontalCenterOffset: -8;
            color: "#dae1e5";
            font.capitalization: Font.MixedCase;
            font.pixelSize: 20;
            textFormat: Text.RichText
            property real spd: speedDisplayMode ? RuntimeData.speed / 3.6 : RuntimeData.speed;
            text: "<font color=\"#dae1e5\"><b>" + Number(spd).toFixed(1) + "</font></b>";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
        }
        Text {
            id: speedTextTooltip1;
            anchors.verticalCenter: speedText.verticalCenter;
            anchors.verticalCenterOffset: -5;
            anchors.left: speedText.right;
            anchors.leftMargin: 2;
            color: "#c7a750";
            font.capitalization: Font.MixedCase;
            font.pixelSize: 12;
            textFormat: Text.RichText;
            font.bold: true;
            text: !speedDisplayMode ? "км" : " \u00A0м";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
        }
        Text {
            id: speedTextTooltip2;
            anchors.verticalCenter: speedText.verticalCenter;
            anchors.verticalCenterOffset: 3;
            anchors.left: speedText.right;
            anchors.leftMargin: 5;
            color: "#c7a750";
            font.capitalization: Font.MixedCase;
            font.pixelSize: 12;
            textFormat: Text.RichText;
            font.bold: true;
            text: !speedDisplayMode ? "ч" : "с";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
        }
    }
}
