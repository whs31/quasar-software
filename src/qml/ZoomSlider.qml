import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtLocation 5.12
import QtPositioning 5.12

Item {
    
    property alias zoomSliderValue: zoomSlider.value;
    
    RoundButton
    {
        id: zoomOut;
        icon.source: "qrc:/ui-resources/white/zoom-out.png";
        icon.color: "black";
        icon.width: 32;
        icon.height: 32;
        width: 40;
        height: 40;
        radius: 10;
        opacity: 1;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        highlighted: true;
        flat: false;
        hoverEnabled: true;
        enabled: true;
        display: AbstractButton.IconOnly;
        onClicked: mapView.zoomLevel -= 0.5;
        z: 100;
    }
    Slider
    {
        id: zoomSlider;
        width: 40;
        height: 200;
        z: 100;
        live: true;
        anchors.bottom: zoomOut.top;
        anchors.horizontalCenter: zoomOut.horizontalCenter;
        snapMode: Slider.NoSnap;
        to: 0;
        from: 1;
        wheelEnabled: false;
        clip: false;
        orientation: Qt.Vertical;
        value: 1;
        onMoved: mapView.zoomLevel = (1-value)*18;
    }
    RoundButton
    {
        id: zoomIn;
        icon.source: "qrc:/ui-resources/white/zoom-in.png";
        icon.color: "black";
        icon.width: 32;
        icon.height: 32;
        width: 40;
        z: 100;
        height: 40;
        radius: 10;
        opacity: 1;
        anchors.horizontalCenter: zoomOut.horizontalCenter
        anchors.bottom: zoomSlider.top;
        highlighted: true;
        flat: false;
        anchors.bottomMargin: -5;
        hoverEnabled: true;
        enabled: true;
        display: AbstractButton.IconOnly;
        onClicked: mapView.zoomLevel += 0.5;
    }
}