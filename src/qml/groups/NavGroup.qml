import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "navigation" as Nav

Rectangle {
    id: mainGroup;
    width: 406;
    height: 250;
    color: "transparent";
    z: 98;
    Rectangle { id: mask1; width: 2; anchors.left: parent.left; anchors.bottom: parent.bottom; anchors.top: parent.top; color: "#dae1e5"; z: 99; opacity: 0.5; }
    Rectangle { id: mask2; width: 2; anchors.right: parent.right; anchors.bottom: parent.bottom; anchors.top: parent.top; color: "#dae1e5"; z: 99; opacity: 0.5; }
    Rectangle { id: mask3; width: 12; height: 2; anchors.left: parent.left; anchors.bottom: parent.bottom; color: "#dae1e5"; z: 99; opacity: 0.5; }
    Rectangle { id: mask4; width: 12; height: 2; anchors.left: parent.left; anchors.top: parent.top; color: "#dae1e5"; z: 99; opacity: 0.5; }
    Rectangle { id: mask5; width: 12; height: 2; anchors.right: parent.right; anchors.bottom: parent.bottom; color: "#dae1e5"; z: 99; opacity: 0.5; }
    Rectangle { id: mask6; width: 12; height: 2; anchors.right: parent.right; anchors.top: parent.top; color: "#dae1e5"; z: 99; opacity: 0.5; }

    Nav.AttitudeIndicator
    {
        id: attitudeIndicator;
        anchors.centerIn: parent;
        visible: false;
    }

    Nav.CoordinateIndicator
    {
        id: coordinateIndicator;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
    }

    Nav.SpeedIndicator
    {
        id: speedIndicator;
        anchors.left: parent.left;
        anchors.leftMargin: 54;
        anchors.bottom: coordinateIndicator.top;
        anchors.bottomMargin: 5;
    }

    Nav.AltIndicator
    {
        id: altIndicator;
        anchors.right: parent.right;
        anchors.rightMargin: 5;
        anchors.bottom: coordinateIndicator.top;
        anchors.bottomMargin: 5;
    }

    Nav.ConnectionBar
    {
        id: connectionbar;
        anchors.bottom: coordinateIndicator.top;
        anchors.bottomMargin: 3;
        anchors.horizontalCenter: parent.horizontalCenter;
    }


}
