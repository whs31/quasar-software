import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtLocation 5.12
import QtPositioning 5.12
import UX 1.0

Item {
    property alias tiltSliderValue: tiltSlider.value;

    RoundButton
    {
        icon.source: "qrc:/ui-resources/white/down.png";
        icon.color: UX.textWhite;
        icon.width: 24;
        icon.height: 24;
        id: tiltDown;
        width: 30;
        height: 30;
        radius: 8;
        opacity: 1;
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        highlighted: true;
        flat: false;
        hoverEnabled: true;
        enabled: true;
        display: AbstractButton.IconOnly;
        onClicked: { if(mapView.tilt >= 2) { mapView.tilt -= 2; } }
        z: 100;
    }
    Slider
    {
        id: tiltSlider;
        width: 25;
        height: 120;
        z: 100;
        live: true;
        anchors.bottom: tiltDown.top;
        anchors.horizontalCenter: tiltDown.horizontalCenter;
        snapMode: Slider.NoSnap;
        to: 0;
        from: 1;
        wheelEnabled: false;
        clip: false;
        orientation: Qt.Vertical;
        value: 1;
        onMoved: mapView.tilt = (1 - value) * 45;
    }
    RoundButton
    {
        icon.source: "qrc:/ui-resources/white/up.png";
        icon.color: UX.textWhite;
        icon.width: 24;
        icon.height: 24;
        id: tiltUp;
        width: 30;
        z: 100;
        height: 30;
        radius: 8;
        opacity: 1;
        anchors.horizontalCenter: tiltDown.horizontalCenter;
        anchors.bottom: tiltSlider.top;
        highlighted: true;
        flat: false;
        anchors.bottomMargin: -5;
        hoverEnabled: true;
        enabled: true;
        display: AbstractButton.IconOnly;
        onClicked: { if(mapView.tilt <= (89.5 / 2) - 2) { mapView.tilt += 2; } }
    }
}
