import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import UX 1.0

Item {
    property alias transparency: tooltipBase.opacity;
    property int tooltipPadding: 0;
    property alias tooltipText: toolTipText.text;

    Rectangle {
        id: tooltipBase;
        width: toolTipText.paintedWidth + 10 + tooltipPadding;
        height: toolTipText.paintedHeight + 3;
        opacity: 0.8;
        color: UX.primaryDarker;
        radius: 5;
        border.color: UX.primaryDarkest;
        z: 99;

        Text {
            id: toolTipText;
            color: UX.textWhite;
            text: qsTr("Sample tooltip text: e.g. latitude, longitude");
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
            font.pixelSize: 12;
            horizontalAlignment: Text.AlignRight;
            verticalAlignment: Text.AlignVCenter;
            anchors.rightMargin: 5;
            anchors.leftMargin: 0;
            font.wordSpacing: 1;
            z: 100;
            font.bold: true;
            font.family: "Arial";
        }
    }
}
