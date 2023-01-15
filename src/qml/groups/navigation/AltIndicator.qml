import QtQuick 2.12
import RuntimeData 1.0
import "qrc:/qml/ui" as UI

Item {
    id: base;
    width: childrenRect.width;
    height: childrenRect.height;
    property bool altDisplayMode: true;

    Rectangle
    {
        id: bground;
        width: 22;
        height: 180;
        color: "#132623";
        border.color: "#204040";
        border.width: 2;
        radius: 12;
    }
    Rectangle
    {
        id: fground;
        width: 70;
        height: 52;
        radius: 2;
        color: "#27183d";
        border.width: 2;
        border.color: "#4b2e75";
        anchors.left: bground.left;
        anchors.verticalCenter: bground.verticalCenter;
        MouseArea
        {
            id: changeSpeedModeArea;
            propagateComposedEvents: true;
            anchors.fill: parent;
            onClicked:
            {
                altDisplayMode = !altDisplayMode;
            }
        }
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
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.horizontalCenterOffset: -4;
            color: "#dae1e5";
            font.capitalization: Font.MixedCase;
            font.pixelSize: 14;
            textFormat: Text.RichText
            text: altDisplayMode ? "<font color=\"#dae1e5\"><b>"
                                    + Number(RuntimeData.elevation - RuntimeData.seaLevel).toFixed(0) + "</font></b>" :
                                   "<font color=\"#dae1e5\"><b>"
                                   + Number(RuntimeData.elevation).toFixed(0) + "</font></b>";
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
        Rectangle
        {
            id: miscBG;
            width: 70;
            height: 2;
            radius: 2;
            color: "#4b2e75";
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 16;
            UI.ToolIcon {
                id: seaLevel;
                tooltipenabled: true;
                tooltiptext: "Отображение высоты относительно уровня моря";
                anchors.left: parent.left;
                anchors.leftMargin: 0;
                anchors.top: parent.top;
                anchors.topMargin: -4;
                iconsize: 16;
                iconsource: "qrc:/ui-resources/white/sea-water.png";
                primarycolor: altDisplayMode ? "#a385cf" : "#dae1e5";
                label: "";
                smooth: true;
                antialiasing: true;
            }
            UI.ToolIcon {
                id: groundLevel;
                tooltipenabled: true;
                tooltiptext: "Отображение высоты относительно уровня земли (необходима калибровка на земле)";
                anchors.left: seaLevel.right;
                anchors.leftMargin: -27;
                anchors.top: parent.top;
                anchors.topMargin: -4;
                iconsize: 16;
                iconsource: "qrc:/ui-resources/white/mountain.png";
                primarycolor: altDisplayMode ? "#dae1e5" : "#a385cf";
                label: "";
                smooth: true;
                antialiasing: true;
            }
        }
    }
}
