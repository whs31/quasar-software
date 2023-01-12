import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtLocation 5.12
import QtPositioning 5.12
import "qrc:/qml/ui" as UI
import RuntimeData 1.0

Rectangle {
    id: base;
    color: "#dae1e5";
    anchors.centerIn: parent;
    width: 180;
    height: 90;
    opacity: 0;
    border.width: 2;
    border.color: "#b2b9bb";
    Rectangle
    {
        id: top;
        color: "#2B6781";
        anchors.bottom: parent.verticalCenter;
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.margins: 2;
        anchors.bottomMargin: 0;
    }
    Rectangle
    {
        id: bottom;
        color: "#7D5233";
        anchors.top: parent.verticalCenter;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.margins: 2;
        anchors.topMargin: 0;
    }
}
