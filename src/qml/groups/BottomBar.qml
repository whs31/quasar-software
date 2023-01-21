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
        label_text: RuntimeData.connected ? "ПОДКЛЮЧЕНО" : "НЕТ СВЯЗИ";
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
    Dropdowns.InverseDropdown
    {
        id: connectionInfoDropDown;
        anchors.left: connectedAnimation.left;
        anchors.bottom: parent.top; anchors.bottomMargin: -2;

        fixed_width: 24;       fixed_height: 17;           fixed_drop: 17*6; fixed_drop_width: 300;
        label_text: "";
        label_color: UX.textWhite;          label_text_size: 12;
        label_text_family: fontMedium.name; label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        highlight_color: UX.primaryLight;
        frame_radius: 2;                    frame_width: 0;
        frame_fill_color: UX.primaryDark;   frame_filled: true;
        container: Item {
            Labels.FramedLabel
            {
                id: connectionInfoLabel1;
                anchors.top: parent.top;
                anchors.left: parent.left; anchors.leftMargin: 5;

                fixed_width: 145;    fixed_height: 17;
                label_text: "IP-АДРЕС РЛС";
                label_color: UX.primaryDarker;
                label_text_size: 12;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel2;
                anchors.top: parent.top;
                anchors.left: connectionInfoLabel1.right;

                fixed_width: 145;    fixed_height: 17;
                label_text: RuntimeData.sarIP;
                label_color: UX.infoDark;
                label_text_size: 12;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel3;
                anchors.top: connectionInfoLabel1.bottom;
                anchors.left: parent.left; anchors.leftMargin: 5;

                fixed_width: 145;    fixed_height: 17;
                label_text: "IP-АДРЕС АРМ";
                label_color: UX.primaryDarker;
                label_text_size: 12;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel4;
                anchors.top: connectionInfoLabel3.top;
                anchors.left: connectionInfoLabel3.right;

                fixed_width: 145;    fixed_height: 17;
                label_text: RuntimeData.pcIP;
                label_color: UX.infoDark;
                label_text_size: 12;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel5;
                anchors.top: connectionInfoLabel3.bottom;
                anchors.left: parent.left; anchors.leftMargin: 5;

                fixed_width: 145;    fixed_height: 17;
                label_text: "ПОРТ ТЕЛЕМЕТРИИ:";
                label_color: UX.primaryDarker;
                label_text_size: 12;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel6;
                anchors.top: connectionInfoLabel5.top;
                anchors.left: connectionInfoLabel5.right;

                fixed_width: 145;    fixed_height: 17;
                label_text: RuntimeData.telemetryPort;
                label_color: UX.accentDark;
                label_text_size: 12;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel7;
                anchors.top: connectionInfoLabel6.bottom;
                anchors.left: parent.left; anchors.leftMargin: 5;

                fixed_width: 145;    fixed_height: 17;
                label_text: "ПОРТ ЗАГРУЗЧИКА:";
                label_color: UX.primaryDarker;
                label_text_size: 12;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel8;
                anchors.top: connectionInfoLabel7.top;
                anchors.left: connectionInfoLabel7.right;

                fixed_width: 145;    fixed_height: 17;
                label_text: RuntimeData.loaderPort;
                label_color: UX.accentDark;
                label_text_size: 12;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel9;
                anchors.top: connectionInfoLabel8.bottom;
                anchors.left: parent.left; anchors.leftMargin: 5;

                fixed_width: 145;    fixed_height: 17;
                label_text: "ПОРТ ОБРАТНОЙ СВЯЗИ:";
                label_color: UX.primaryDarker;
                label_text_size: 12;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel10;
                anchors.top: connectionInfoLabel9.top;
                anchors.left: connectionInfoLabel9.right;

                fixed_width: 145;    fixed_height: 17;
                label_text: RuntimeData.listenPort;
                label_color: UX.accentDark;
                label_text_size: 12;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel11;
                anchors.top: connectionInfoLabel10.bottom;
                anchors.left: parent.left; anchors.leftMargin: 5;

                fixed_width: 145;    fixed_height: 17;
                label_text: "ПОРТ ИНТЕРФЕЙСА ВЫПОЛНЕНИЯ КОМАНД:";
                label_color: UX.primaryDarker;
                label_text_size: 12;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel12;
                anchors.top: connectionInfoLabel11.top;
                anchors.left: connectionInfoLabel11.right;

                fixed_width: 145;    fixed_height: 17;
                label_text: RuntimeData.commandPort;
                label_color: UX.accentDark;
                label_text_size: 12;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
        }
    }
    Rectangle
    {
        id: attitudeFrame;
        width: 288;
        height: 168;
        color: UX.primaryDark;
        radius: 5;
        anchors.left: parent.left;
        anchors.bottom: parent.top;
        CustomWidgets.AttitudeIndicator
        {
            id: attitudeIndicator;
            anchors.centerIn: parent;
        }
    }
}
