import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Item {
    property bool tooltipenabled: false;
    property string tooltiptext: "Tooltip text!";
    property color primarycolor: "#204040";
    property color textcolor: "#dae1e5";
    property int iconsize: 20;
    property string iconsource: "qrc:/ui-resources/white/close.png";
    property int basewidth: 50;
    property string label: "00";
    
    id: control;

    Rectangle {
        id: toolrect;
        color: primarycolor;
        opacity: 0.75;
        //anchors.fill: parent;
        width: basewidth;
        height: iconsize + 9;
        radius: 15;

        Image {
            id: ico;
            width: iconsize;
            height: iconsize;
            source: iconsource;
            smooth: true;
            antialiasing: true;
            anchors.left: parent.left;
            anchors.leftMargin: 5;
            anchors.verticalCenter: parent.verticalCenter;
            MouseArea
            {
                id: mouseAreaIco;
                anchors.fill: parent;
                hoverEnabled: tooltipenabled ? true : false;
            }
            ToolTip {
                id: m_tooltip;
                delay: 250;
                timeout: 15000;
                visible: mouseAreaIco.containsMouse;
                text: tooltiptext;
                font.capitalization: Font.MixedCase;
                font.pixelSize: 11;
                // contentItem: Text {
                //     color: "#21be2b"
                // }
                // background: Rectangle {
                //     color: "#21be2b"
                // }
            }
        }
        Text {
            id: m_text;
            font.capitalization: Font.MixedCase;
            font.pixelSize: 14;
            font.bold: true;
            color: textcolor;
            text: label;
            opacity: enabled ? 1.0 : 0.3
            verticalAlignment: Text.AlignVCenter
            anchors.left: ico.right;
            anchors.verticalCenter: ico.verticalCenter;
            anchors.leftMargin: 3;
        }
    }
}
