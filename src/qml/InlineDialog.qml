import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Item {
    property alias transparency: dialogBase.opacity;

    Rectangle {
        id: dialogBase;
        width: 100
        height: 25
        opacity: 0.8;
        color: "#121212";
        radius: 5;
        border.color: "#777777";
        z: 100;

        RoundButton {
            id: roundButton
            width: 25
            radius: 3
            text: "+"
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            highlighted: true
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            anchors.rightMargin: 0
        }
    }
}
