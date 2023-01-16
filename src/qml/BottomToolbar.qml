import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtLocation 5.12
import QtPositioning 5.12

Item {
    RoundButton
    {
        id: panButton;
        icon.source: "qrc:/ui-resources/white/plane.png";
        icon.color: "#dae1e5";
        icon.width: 32;
        icon.height: 32;
        width: 40;
        height: 40;
        radius: 10;
        opacity: 1;
        z: 100;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        highlighted: true;
        flat: false;
        hoverEnabled: true;
        enabled: true;
        display: AbstractButton.IconOnly;
        onClicked: panGPS();
    }
    RoundButton
    {
        id: panImageButton;
        icon.source: "qrc:/ui-resources/white/image.png";
        icon.color: "#dae1e5";
        icon.width: 32;
        icon.height: 32;
        width: 40;
        height: 40;
        radius: 10;
        z: 100;
        opacity: 1;
        anchors.right: panButton.left;
        anchors.verticalCenter: panButton.verticalCenter;
        highlighted: true;
        flat: false;
        anchors.rightMargin: 0;
        hoverEnabled: true;
        enabled: true;
        display: AbstractButton.IconOnly;
        onClicked:
        {
            panImage();
            if(FDynamicVariables.followPlane)
            {
                FDynamicVariables.followPlane = false;
            }
        }
    }

    RoundButton
    {
        id: rulerButton;
        icon.source: "qrc:/ui-resources/white/ruler.png";
        icon.color: "#dae1e5";
        icon.width: 32;
        icon.height: 32;
        width: 40;
        height: 40;
        radius: 10;
        opacity: 1;
        z: 100;
        anchors.right: panImageButton.left;
        anchors.verticalCenter: panImageButton.verticalCenter;
        highlighted: true;
        flat: false;
        anchors.rightMargin: 20;
        hoverEnabled: true;
        enabled: true;
        display: AbstractButton.IconOnly;
        onClicked:
        {
            if(r_currentstate !== 0) { r_currentstate = 1;
                clearRuler(); } else {
                r_currentstate = 1;
            }
        }
    }
    RoundButton
    {
        id: markerButton;
        icon.source: "qrc:/ui-resources/white/marker-blank.png";
        icon.color: "#dae1e5";
        icon.width: 40;
        icon.height: 40;
        width: 40;
        height: 40;
        radius: 10;
        opacity: 1;
        z: 100;
        anchors.right: rulerButton.left;
        anchors.verticalCenter: rulerButton.verticalCenter;
        highlighted: true;
        flat: false;
        anchors.rightMargin: 20;
        hoverEnabled: true;
        enabled: true;
        display: AbstractButton.IconOnly;
        onClicked: { ioHandler.placeMarker(); }
    }
}
