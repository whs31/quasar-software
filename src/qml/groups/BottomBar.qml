import QtQuick 2.12
import UX 1.0
import RuntimeData 1.0
import SignalLinker 1.0
import DiskManager 1.0
import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels
import "qrc:/qml/ui/dropdowns" as Dropdowns
import "qrc:/qml/ui/layouts" as Layouts
import "qrc:/qml/ui/widgets" as CustomWidgets

Rectangle {
    id: base;
    height: 36;
    color: UX.primaryDark;

    FontLoader { id: fontRegular; source: "qrc:/fonts/SofiaSans-Regular.ttf" }
    FontLoader { id: fontMedium; source: "qrc:/fonts/SofiaSans-Medium.ttf" }
    FontLoader { id: fontSemiBold; source: "qrc:/fonts/SofiaSans-SemiBold.ttf" }
    FontLoader { id: fontBold; source: "qrc:/fonts/SofiaSans-Bold.ttf" }
    FontLoader { id: fontExtraBold; source: "qrc:/fonts/SofiaSans-ExtraBold.ttf" }

    Labels.FramedLabel
    {
        id: satsLabel;
        anchors.bottom: parent.bottom;  anchors.bottomMargin: 8;
        anchors.right: parent.right; anchors.rightMargin: 5;

        fixed_width: 16;    fixed_height: 19;
        label_text: Number(RuntimeData.satellites);
        label_color: UX.textWhite;              label_text_size: 16;
        label_text_family: fontBold.name;   label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        frame_radius: 2;                        frame_width: 0;
    }
    Image {
        id: satsIcon;
        width: 22;
        height: 22;
        source: "qrc:/icons/satellite.png";
        smooth: true;
        antialiasing: true;
        anchors.right: satsLabel.left;  anchors.rightMargin: 2;
        anchors.verticalCenter: parent.verticalCenter;
    }
    Buttons.ImageButton
    {
        id: mapmodeSchemeButton;
        anchors.right: satsIcon.left; anchors.rightMargin: 8;
        anchors.top: parent.top; anchors.topMargin: 4;
        fixed_width: 60;    fixed_height: 8;
        image_source: "qrc:/icons/map-layers/schema.png";
        frame_color: UX.textWhite;
        hover_color: UX.infoLight;
        frame_width: 1; frame_radius: 1;
        onClicked: { mapView.activeMapType = mapView.supportedMapTypes[5]; }
    }
    Buttons.ImageButton
    {
        id: mapmodeSatelliteButton;
        anchors.right: mapmodeSchemeButton.right;
        anchors.top: mapmodeSchemeButton.bottom; anchors.topMargin: 2;
        fixed_width: 60;    fixed_height: 8;
        image_source: "qrc:/icons/map-layers/satellite.png";
        frame_color: UX.textWhite;
        hover_color: UX.infoLight;
        frame_width: 1; frame_radius: 1;
        onClicked: { mapView.activeMapType = mapView.supportedMapTypes[1]; }
    }
    Buttons.ImageButton
    {
        id: mapmodeHybridButton;
        anchors.right: mapmodeSatelliteButton.right;
        anchors.top: mapmodeSatelliteButton.bottom; anchors.topMargin: 2;
        fixed_width: 60;    fixed_height: 8;
        image_source: "qrc:/icons/map-layers/hybrid.png";
        frame_color: UX.textWhite;
        hover_color: UX.infoLight;
        frame_width: 1; frame_radius: 1;
        onClicked: { mapView.activeMapType = mapView.supportedMapTypes[4]; }
    }
    Labels.FramedLabel
    {
        id: mapLayersLabel;
        anchors.verticalCenter: mapmodeSatelliteButton.verticalCenter;
        anchors.right: mapmodeSatelliteButton.left; anchors.rightMargin: 3;

        fixed_width: 40;    fixed_height: 26;
        label_text: "СЛОИ <br> КАРТЫ";
        label_color: UX.textWhite;              label_text_size: 12;
        label_text_family: fontBold.name;       label_text_bold: true;
        label_textAlignment: Text.AlignRight;
        frame_radius: 2;                        frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: heightTerrainDisplayLabel;
        anchors.top: parent.top; anchors.topMargin: 2;
        anchors.right: mapLayersLabel.left;

        fixed_width: 65;    fixed_height: 17;
        label_text: Number(RuntimeData.elevation - RuntimeData.seaLevel).toFixed(0) + " М";
        label_color: UX.textWhite;              label_text_size: 16;
        label_text_family: fontExtraBold.name;       label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: heightSeaDisplayLabel;
        anchors.top: heightTerrainDisplayLabel.bottom;
        anchors.right: mapLayersLabel.left;

        fixed_width: 65;    fixed_height: 12;
        label_text: Number(RuntimeData.elevation).toFixed(0) + " М";
        label_color: UX.textWhite;                  label_text_size: 12;
        label_text_family: fontExtraBold.name;      label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                            frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: heightTerrainLabel;
        anchors.top: parent.top; anchors.topMargin: 2;
        anchors.right: heightTerrainDisplayLabel.left;

        fixed_width: 130;    fixed_height: 17;
        label_text: "ВЫСОТА: ";
        label_color: UX.textWhite;              label_text_size: 12;
        label_text_family: fontExtraBold.name;       label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Image {
        id: terrainIcon;
        width: 16;
        height: 16;
        source: "qrc:/icons/mountain.png";
        smooth: true;
        antialiasing: true;
        anchors.right: heightTerrainLabel.left;  anchors.rightMargin: 2;
        anchors.verticalCenter: heightTerrainLabel.verticalCenter; anchors.verticalCenterOffset: -1;
    }
    Labels.FramedLabel
    {
        id: heightSeaLabel;
        anchors.top: heightTerrainDisplayLabel.bottom;
        anchors.right: heightSeaDisplayLabel.left;

        fixed_width: 130;    fixed_height: 12;
        label_text: "НАД УРОВНЕМ МОРЯ: ";
        label_color: UX.textWhite;              label_text_size: 12;
        label_text_family: fontBold.name;       label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Image {
        id: seaIcon;
        width: 16;
        height: 16;
        source: "qrc:/icons/water.png";
        smooth: true;
        antialiasing: true;
        anchors.right: heightSeaLabel.left;  anchors.rightMargin: 2;
        anchors.verticalCenter: heightSeaLabel.verticalCenter; anchors.verticalCenterOffset: -1;
    }
    Labels.FramedLabel
    {
        id: latitudeLabel;
        anchors.top: parent.top; anchors.topMargin: 4;
        anchors.right: seaIcon.left; anchors.rightMargin: 17;

        fixed_width: 142;    fixed_height: 12;
        label_text: "<b>ШИРОТА:</b>     " + Number(RuntimeData.latitude).toFixed(5) + " °N";
        label_color: UX.textWhite;              label_text_size: 12;
        label_text_family: fontBold.name;       label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: longitudeLabel;
        anchors.top: latitudeLabel.bottom; anchors.topMargin: 3;
        anchors.right: seaIcon.left; anchors.rightMargin: 17;

        fixed_width: 142;    fixed_height: 12;
        label_text: "<b>ДОЛГОТА:</b>     " + Number(RuntimeData.longitude).toFixed(5) + " °E";
        label_color: UX.textWhite;              label_text_size: 12;
        label_text_family: fontBold.name;       label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Buttons.LightButton
    {
        id: connectButton;
        anchors.bottom: parent.bottom; anchors.bottomMargin: 4;
        anchors.right: longitudeLabel.left; anchors.rightMargin: 19;
        fixed_width: 155;               fixed_height: 16;
        label_text: RuntimeData.connected ? "ОТКЛЮЧИТЬСЯ" : "ПОДКЛЮЧИТЬСЯ";
        label_color: UX.textWhite;  label_text_size: 12;
        label_text_family: fontBold.name;
        label_text_bold: true;         label_textAlignment: Text.AlignHCenter;
        highlight_color: RuntimeData.connected ? UX.errorDark : UX.successLighter;
        frame_radius: 2;                frame_width: 1;
        frame_enabled: true;
        onClicked: {
            if(RuntimeData.connected) //TODO: if button pressed and not connected in 3 seconds -> disconnect!
            {
                ioHandler.disconnect();
            } else {
                ioHandler.reconnect();
            }
        }
    }
    Labels.FramedLabel
    {
        id: connectedLabel;
        anchors.bottom: parent.bottom;      anchors.bottomMargin: 8;
        anchors.right: connectButton.left;  anchors.rightMargin: 0;

        fixed_width: 101;    fixed_height: 17;
        label_text: RuntimeData.connected ? "ПОДКЛЮЧЕНО" : " НЕТ СВЯЗИ";
        label_color: RuntimeData.connected ? UX.successLighter : UX.errorLighter;
        label_text_size: 14;
        label_text_family: fontExtraBold.name; label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                    frame_width: 0;
    }
    AnimatedImage
    {
        id: connectedAnimation;
        width: 24; height: 24;
        anchors.right: connectedLabel.left; anchors.rightMargin: 0;
        anchors.bottom: connectedLabel.bottom; anchors.bottomMargin: -2;
        source: RuntimeData.connected ? "qrc:/icons/animated/gif_connected.gif" : "qrc:/icons/animated/gif_disconnected.gif";
    }
}
