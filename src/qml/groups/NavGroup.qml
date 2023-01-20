import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "navigation" as Nav
import UX 1.0

Rectangle {
    id: mainGroup;
    width: 370;
    height: 250;
    color: "transparent";
    z: 98;

    Nav.AttitudeIndicator
    {
        id: attitudeIndicator;
        anchors.bottomMargin: -2;
        anchors.horizontalCenter: parent.horizontalCenter;
        visible: true;
    }
    Nav.SpeedIndicator
    {
        id: speedIndicator;
        anchors.left: parent.left;
        anchors.leftMargin: 29;
        anchors.bottomMargin: -13;
    }
    Nav.ConnectionBar
    {
        id: connectionbar;
        anchors.bottomMargin: 3;
        anchors.horizontalCenter: parent.horizontalCenter;
        opacity: 0.65;
    }

}
