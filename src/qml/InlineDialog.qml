import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Rectangle {
    id: dialogBase;
    width: 45
    height: 15
    opacity: 0.6;
    color: "#121212";
    radius: 5;
    border.color: "#777777";
    z: 100;

    RoundButton {
        id: roundButton
        width: 22
        height: 22
        radius: 2
        text: "X"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        rightPadding: 0
        leftPadding: 0
        bottomPadding: 0
        topPadding: 0
        icon.cache: true
        font.pointSize: 5
        font.family: "Arial"
        font.bold: true
        Material.background: Material.Red

        scale: 1
        z: 100
        display: AbstractButton.IconOnly
        icon.color: "#ffffff"
        icon.source: "../ui-resources/white/close.png"
        icon.width: 8
        icon.height: 8
        flat: true
        highlighted: false
        anchors.rightMargin: -2;
        onClicked: {
            //marker
        }
    }
}
