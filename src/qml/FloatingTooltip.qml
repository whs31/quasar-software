import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Item {
    property alias transparency: tooltipBase.opacity;
    property int tooltipPadding: 0;
    property alias tooltipText: toolTipText.text;

    Rectangle {
        id: tooltipBase;
        width: toolTipText.paintedWidth + 10 + tooltipPadding;
        height: toolTipText.paintedHeight + 3;
        opacity: 0.8;
        color: "#132623";
        radius: 5;
        border.color: "#777777";
        z: 99;

        Text {
            id: toolTipText;
            color: "#dae1e5"
            text: qsTr("Sample tooltip text: e.g. latitude, longitude");
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
            font.pixelSize: 10;
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
