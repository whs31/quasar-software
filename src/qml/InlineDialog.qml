import QtQuick 2.12
//import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Rectangle {
    id: dialogBase;
    width: 50
    height: 20
    opacity: 0.6;
    color: "#132623";
    radius: 5;
    border.color: "#204040";
    z: 100;

    RoundButton {
        id: roundButton
        width: 28
        height: 28
        radius: 2
        text: "X"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        rightPadding: 0
        leftPadding: 0
        bottomPadding: 0
        topPadding: 0
        icon.cache: true
        font.pointSize: 7
        font.family: "Arial"
        font.bold: true
        Material.background: "#b16573"
        hoverEnabled: false;
        scale: 1
        z: 100
        display: AbstractButton.IconOnly
        icon.color: "#fff5ee"
        icon.source: "../ui-resources/white/close.png"
        icon.width: 8
        icon.height: 8
        flat: true
        highlighted: false
        anchors.rightMargin: -2;
        onClicked: {
            remove();
        }
    }
}
