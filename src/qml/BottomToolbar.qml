import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtLocation 5.12
import QtPositioning 5.12
import UX 1.0

Item {
    RoundButton
    {
        id: rulerButton;
        icon.source: "qrc:/ui-resources/white/ruler.png";
        icon.color: UX.textWhite;
        icon.width: 32;
        icon.height: 32;
        width: 40;
        height: 40;
        radius: 10;
        opacity: 1;
        z: 100;
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
        icon.color: UX.textWhite;
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
