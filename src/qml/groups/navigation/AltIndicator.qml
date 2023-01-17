import QtQuick 2.12
import RuntimeData 1.0
import "qrc:/qml/ui" as UI
import UX 1.0

Item {
    id: base;
    width: childrenRect.width;
    height: childrenRect.height;
    property bool altDisplayMode: true;

    Rectangle
    {
        id: bground;
        width: 26;
        height: 200;
        color: UX.accentDarker;
        border.color: UX.accentDark;
        border.width: 2;
        radius: 13;
    }
    Rectangle
    {
        id: fground;
        width: 80;
        height: 52;
        radius: 12;
        color: UX.accentDarker;
        border.width: 2;
        border.color: UX.accentDark;
        anchors.horizontalCenter: bground.horizontalCenter;
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
            width: 80;
            height: 13;
            radius: 6;
            color: UX.accentDark;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: parent.top;
            Text {
                id: labelText
                text: "ВЫСОТА";
                font.bold: true;
                font.pointSize: 7;
                horizontalAlignment: Text.AlignHCenter;
                anchors.centerIn: parent;
                color: UX.textWhite;
            }
        }
        Text {
            id: altText;
            anchors.top: labelBG.bottom;
            anchors.topMargin: -1;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.horizontalCenterOffset: -4;
            color: UX.textWhite;
            font.capitalization: Font.MixedCase;
            font.pixelSize: 20;
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
            color: UX.accentLight;
            font.capitalization: Font.MixedCase;
            font.pixelSize: 12;
            textFormat: Text.RichText;
            font.bold: true;
            text: "м";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
        }
        Rectangle
        {
            id: miscBG;
            width: 80;
            height: 2;
            radius: 2;
            color: UX.accentDark;
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
                primarycolor: altDisplayMode ? UX.accentLight : UX.textWhite;
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
                primarycolor: altDisplayMode ? UX.textWhite : UX.accentLight;
                label: "";
                smooth: true;
                antialiasing: true;
            }
        }
    }
}
