import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "navigation" as Nav

Rectangle {
    id: mainGroup;
    width: 370;
    height: 250;
    color: "transparent";
    z: 98;
    Rectangle { id: shadowbackground; anchors.fill: parent; color: "#132623"; opacity: 0.2; anchors.margins: 2; }
    Rectangle { id: mask1; width: 2; anchors.left: parent.left; anchors.bottom: parent.bottom; anchors.top: parent.top; color: "#dae1e5"; z: 99; opacity: 0.75; }
    Rectangle { id: mask2; width: 2; anchors.right: parent.right; anchors.bottom: parent.bottom; anchors.top: parent.top; color: "#dae1e5"; z: 99; opacity: 0.75; }
    Rectangle { id: mask3; width: 12; height: 2; anchors.left: parent.left; anchors.bottom: parent.bottom; color: "#dae1e5"; z: 99; opacity: 0.75; }
    Rectangle { id: mask4; width: 12; height: 2; anchors.left: parent.left; anchors.top: parent.top; color: "#dae1e5"; z: 99; opacity: 0.75; }
    Rectangle { id: mask5; width: 12; height: 2; anchors.right: parent.right; anchors.bottom: parent.bottom; color: "#dae1e5"; z: 99; opacity: 0.75; }
    Rectangle { id: mask6; width: 12; height: 2; anchors.right: parent.right; anchors.top: parent.top; color: "#dae1e5"; z: 99; opacity: 0.75; }  

    Nav.AttitudeIndicator
    {
        id: attitudeIndicator;
        anchors.bottom: coordinateIndicator.top;
        anchors.bottomMargin: -2;
        anchors.horizontalCenter: parent.horizontalCenter;
        visible: true;
    }
    Nav.SpeedIndicator
    {
        id: speedIndicator;
        anchors.left: parent.left;
        anchors.leftMargin: 29;
        anchors.bottom: coordinateIndicator.top;
        anchors.bottomMargin: -13;
    }
    Nav.AltIndicator
    {
        id: altIndicator;
        anchors.right: parent.right;
        anchors.rightMargin: -25;
        anchors.bottom: coordinateIndicator.top;
        anchors.bottomMargin: -13;
    }
    Nav.CoordinateIndicator
    {
        id: coordinateIndicator;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
    }
    Nav.ConnectionBar
    {
        id: connectionbar;
        anchors.bottom: coordinateIndicator.top;
        anchors.bottomMargin: 3;
        anchors.horizontalCenter: parent.horizontalCenter;
        opacity: 0.65;
    }

}
