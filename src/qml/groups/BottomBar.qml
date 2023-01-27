import QtQuick 2.12
import UX 1.0
import RuntimeData 1.0
import Config 1.0
import SignalLinker 1.0
import DiskManager 1.0
import DynamicResolution 1.0
import DialogWindowBackend 1.0
import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels
import "qrc:/qml/ui/dropdowns" as Dropdowns
import "qrc:/qml/ui/layouts" as Layouts
import "qrc:/qml/ui/widgets" as CustomWidgets

Rectangle {
    property bool speedDisplayMode: false;
    id: base;
    height: 36 * DynamicResolution.kh;
    color: UX.primaryDark;
    FontLoader { id: fontRegular; source: "qrc:/fonts/SofiaSans-Regular.ttf" }
    FontLoader { id: fontMedium; source: "qrc:/fonts/SofiaSans-Medium.ttf" }
    FontLoader { id: fontSemiBold; source: "qrc:/fonts/SofiaSans-SemiBold.ttf" }
    FontLoader { id: fontBold; source: "qrc:/fonts/SofiaSans-Bold.ttf" }
    FontLoader { id: fontExtraBold; source: "qrc:/fonts/SofiaSans-ExtraBold.ttf" }
    Labels.FramedLabel
    {
        id: satsLabel;
        anchors.bottom: parent.bottom;  anchors.bottomMargin: 8 * DynamicResolution.kh;
        anchors.right: parent.right; anchors.rightMargin: 5 * DynamicResolution.kw;

        fixed_width: 16 * DynamicResolution.kw;
        fixed_height: 19 * DynamicResolution.kh;
        label_text: Number(RuntimeData.satellites);
        label_color: UX.textWhite;
        label_text_size: 16 * DynamicResolution.kh;
        label_text_family: fontBold.name;   label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        frame_radius: 2;                        frame_width: 0;
    }
    Image {
        id: satsIcon;
        width: 22 * DynamicResolution.kw;
        height: 22 * DynamicResolution.kh;
        source: "qrc:/icons/satellite.png";
        smooth: true;
        antialiasing: true;
        anchors.right: satsLabel.left;
        anchors.rightMargin: 2 * DynamicResolution.kw;
        anchors.verticalCenter: parent.verticalCenter;
    }
    Buttons.ImageButton
    {
        id: mapmodeSchemeButton;
        anchors.right: satsIcon.left; anchors.rightMargin: 8 * DynamicResolution.kw;
        anchors.top: parent.top; anchors.topMargin: 4 * DynamicResolution.kh;
        fixed_width: 60 * DynamicResolution.kw;
        fixed_height: 8 * DynamicResolution.kh;
        image_source: "qrc:/icons/map-layers/schema.png";
        frame_color: UX.textWhite;
        hover_color: UX.infoLight;
        frame_width: 1; frame_radius: 1;
        enabled: Config.onlineMaps;
        onClicked: { mapView.activeMapType = mapView.supportedMapTypes[5]; }
    }
    Buttons.ImageButton
    {
        id: mapmodeSatelliteButton;
        anchors.right: mapmodeSchemeButton.right;
        anchors.top: mapmodeSchemeButton.bottom; anchors.topMargin: 2 * DynamicResolution.kh;
        fixed_width: 60 * DynamicResolution.kw;    fixed_height: 8 * DynamicResolution.kh;
        image_source: "qrc:/icons/map-layers/satellite.png";
        frame_color: UX.textWhite;
        hover_color: UX.infoLight;
        frame_width: 1; frame_radius: 1;
        enabled: Config.onlineMaps;
		onClicked: { mapView.activeMapType = mapView.supportedMapTypes[1]; }
    }
    Buttons.ImageButton
    {
        id: mapmodeHybridButton;
        anchors.right: mapmodeSatelliteButton.right;
        anchors.top: mapmodeSatelliteButton.bottom;
        anchors.topMargin: 2 * DynamicResolution.kh;
        fixed_width: 60 * DynamicResolution.kw;
        fixed_height: 8 * DynamicResolution.kh;
        image_source: "qrc:/icons/map-layers/hybrid.png";
        frame_color: UX.textWhite;
        hover_color: UX.infoLight;
        frame_width: 1; frame_radius: 1;
        enabled: Config.onlineMaps;
        onClicked: { mapView.activeMapType = mapView.supportedMapTypes[4]; }
    }
    Labels.FramedLabel
    {
        id: mapLayersLabel;
        anchors.verticalCenter: mapmodeSatelliteButton.verticalCenter;
        anchors.right: mapmodeSatelliteButton.left;
        anchors.rightMargin: 3 * DynamicResolution.kw;

        fixed_width: 40 * DynamicResolution.kw;
        fixed_height: 26 * DynamicResolution.kh;
        label_text: "СЛОИ <br> КАРТЫ";
        label_color: UX.textWhite;
        label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontBold.name;       label_text_bold: true;
        label_textAlignment: Text.AlignRight;
        frame_radius: 2;                        frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: heightTerrainDisplayLabel;
        anchors.top: parent.top; anchors.topMargin: 2 * DynamicResolution.kh;
        anchors.right: mapLayersLabel.left;

        fixed_width: 65 * DynamicResolution.kw;
        fixed_height: 17 * DynamicResolution.kh;
        label_text: Number(RuntimeData.elevation - RuntimeData.seaLevel).toFixed(0) + " М";
        label_color: UX.textWhite;
        label_text_size: 16 * DynamicResolution.kh;
        label_text_family: fontExtraBold.name;       label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: heightSeaDisplayLabel;
        anchors.top: heightTerrainDisplayLabel.bottom;
        anchors.right: mapLayersLabel.left;

        fixed_width: 65 * DynamicResolution.kw;
        fixed_height: 12 * DynamicResolution.kh;
        label_text: Number(RuntimeData.elevation).toFixed(0) + " М";
        label_color: UX.textWhite;                  label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontExtraBold.name;      label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                            frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: heightTerrainLabel;
        anchors.top: parent.top;
        anchors.topMargin: 2 * DynamicResolution.kh;
        anchors.right: heightTerrainDisplayLabel.left;

        fixed_width: 130 * DynamicResolution.kw;
        fixed_height: 17 * DynamicResolution.kh;
        label_text: "ВЫСОТА: ";
        label_color: UX.textWhite;
        label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontExtraBold.name;       label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Image {
        id: terrainIcon;
        width: 16 * DynamicResolution.kw;
        height: 16 * DynamicResolution.kh;
        source: "qrc:/icons/mountain.png";
        smooth: true;
        antialiasing: true;
        anchors.right: heightTerrainLabel.left;  anchors.rightMargin: 2 * DynamicResolution.kw;
        anchors.verticalCenter: heightTerrainLabel.verticalCenter; anchors.verticalCenterOffset: -1 * DynamicResolution.kw;
    }
    Labels.FramedLabel
    {
        id: heightSeaLabel;
        anchors.top: heightTerrainDisplayLabel.bottom;
        anchors.right: heightSeaDisplayLabel.left;

        fixed_width: 130 * DynamicResolution.kw;
        fixed_height: 12 * DynamicResolution.kh;
        label_text: "НАД УРОВНЕМ МОРЯ: ";
        label_color: UX.textWhite;
        label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontBold.name;       label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Image {
        id: seaIcon;
        width: 16 * DynamicResolution.kw;
        height: 16 * DynamicResolution.kh;
        source: "qrc:/icons/water.png";
        smooth: true;
        antialiasing: true;
        anchors.right: heightSeaLabel.left;
        anchors.rightMargin: 2 * DynamicResolution.kw;
        anchors.verticalCenter: heightSeaLabel.verticalCenter;
        anchors.verticalCenterOffset: -1 * DynamicResolution.kh;
    }
    Labels.FramedLabel
    {
        id: latitudeLabel;
        anchors.top: parent.top; anchors.topMargin: 4 * DynamicResolution.kh;
        anchors.right: seaIcon.left; anchors.rightMargin: 17 * DynamicResolution.kw;

        fixed_width: 142 * DynamicResolution.kw;    fixed_height: 12 * DynamicResolution.kh;
        label_text: "<b>ШИРОТА:</b>     " + Number(RuntimeData.latitude).toFixed(5) + " °N";
        label_color: UX.textWhite;
        label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontBold.name;       label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: longitudeLabel;
        anchors.top: latitudeLabel.bottom; anchors.topMargin: 3 * DynamicResolution.kh;
        anchors.right: seaIcon.left; anchors.rightMargin: 17 * DynamicResolution.kw;

        fixed_width: 142 * DynamicResolution.kw;    fixed_height: 12 * DynamicResolution.kh;
        label_text: "<b>ДОЛГОТА:</b>     " + Number(RuntimeData.longitude).toFixed(5) + " °E";
        label_color: UX.textWhite;              label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontBold.name;       label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Buttons.LightButton
    {
        id: connectButton;
        anchors.bottom: parent.bottom; anchors.bottomMargin: 4 * DynamicResolution.kh;
        anchors.right: longitudeLabel.left; anchors.rightMargin: 19 * DynamicResolution.kw;
        fixed_width: 155 * DynamicResolution.kw;               fixed_height: 16 * DynamicResolution.kh;
        label_text: RuntimeData.connected ? "ОТКЛЮЧИТЬСЯ" : "ПОДКЛЮЧИТЬСЯ";
        label_color: UX.textWhite;  label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontBold.name;
        label_text_bold: true;         label_textAlignment: Text.AlignHCenter;
        highlight_color: RuntimeData.connected ? UX.errorDark : UX.successLighter;
        frame_radius: 2;                frame_width: 1;
        tooltip_text: "Подключение и отключение к РЛС";
        tooltip_enabled: true;
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
        anchors.bottom: parent.bottom;      anchors.bottomMargin: 8 * DynamicResolution.kh;
        anchors.right: connectButton.left;

        fixed_width: 101 * DynamicResolution.kw;    fixed_height: 17 * DynamicResolution.kh;
        label_text: RuntimeData.connected ? "ПОДКЛЮЧЕНО" : "НЕТ СВЯЗИ";
        label_color: RuntimeData.connected ? UX.successLighter : UX.errorLighter;
        label_text_size: 14 * DynamicResolution.kh;
        label_text_family: fontExtraBold.name; label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                    frame_width: 0;
    }
    Buttons.SmallRoundButton
    {
        id: checkConnectionButton;
        enabled: !RuntimeData.windowLock;
        fixed_width: 36 * DynamicResolution.kw;
        fixed_height: 11 * DynamicResolution.kh;
        anchors.left: connectButton.left;
        anchors.bottom: connectButton.top;
        anchors.bottomMargin: 3 * DynamicResolution.kh;

        background_color: UX.textFaded;
        background_radius: 8;
        label_text: "CHECK";
        label_color: UX.primaryDarker;
        label_text_size: 10 * DynamicResolution.kh;
        label_text_family: fontBold.name;
        label_text_bold: false;
        tooltip_text: "Проверка систем РЛС";
        tooltip_enabled: true;
        label_textAlignment: Text.AlignHCenter;
        highlight_color: UX.warningLight;
        onClicked: { console.log("check is not yet implemented!"); }
    }
    Buttons.SmallRoundButton
    {
		property bool waitingForDialogResponse: false;

        id: calibrateSeaLLevelButton;
        enabled: !RuntimeData.windowLock;
        fixed_width: 24 * DynamicResolution.kw;
        fixed_height: 11 * DynamicResolution.kh;
        anchors.left: checkConnectionButton.right;
        anchors.leftMargin: 3 * DynamicResolution.kw;
        anchors.bottom: connectButton.top;
		anchors.bottomMargin: 3 * DynamicResolution.kh;
        background_color: UX.textFaded;
        background_radius: 8;
        label_text: "CAL";
        label_color: UX.primaryDarker;
        label_text_size: 10 * DynamicResolution.kh;
        label_text_family: fontBold.name;
        label_text_bold: false;
        label_textAlignment: Text.AlignHCenter;
        highlight_color: UX.warningLight;
        tooltip_text: "Калибровка высоты относительно поверхности";
        tooltip_enabled: true;
		onClicked: {
			RuntimeData.windowLock = true;
			DialogWindowBackend.header = "КАЛИБРОВКА ВЫСОТЫ";
			DialogWindowBackend.icon = "qrc:/icons/dialog/warning.png";
			DialogWindowBackend.text = "Калибровка высоты должна проводиться на земле. Убедитесь, что беспилотник находится на стартовой площадке.";
			DialogWindowBackend.show();
			waitingForDialogResponse = true;
		}
		function handleResponse()
		{
			if(waitingForDialogResponse === true)
			{
				if(DialogWindowBackend.returnCode === 1)
				{
					RuntimeData.seaLevel = RuntimeData.elevation;
				}
			}
		}
		Component.onCompleted: {
			DialogWindowBackend.returnCodeChanged.connect(handleResponse)
		}
    }
    Buttons.SmallRoundButton
    {
        id: customCommandButton;
        enabled: !RuntimeData.windowLock;
        fixed_width: 89 * DynamicResolution.kw;
        fixed_height: 11 * DynamicResolution.kh;
        anchors.left: calibrateSeaLLevelButton.right;
        anchors.leftMargin: 3 * DynamicResolution.kw;
        anchors.bottom: connectButton.top;
        anchors.bottomMargin: 3 * DynamicResolution.kh;

        background_color: UX.textFaded;
        background_radius: 8;
        label_text: "COMMAND";
        label_color: UX.primaryDarker;
        label_text_size: 10 * DynamicResolution.kh;
        label_text_family: fontBold.name;
        label_text_bold: false;
        label_textAlignment: Text.AlignHCenter;
        highlight_color: UX.warningLight;
        tooltip_text: "Выполнить shell-команду на РЛС";
        tooltip_enabled: true;
        onClicked: { console.log("custom command is not yet implemented (needs custom window)!"); }
    }
    AnimatedImage
    {
        id: connectedAnimation;
        width: 24 * DynamicResolution.kw; height: 24 * DynamicResolution.kh;
        anchors.right: connectedLabel.left;
        anchors.bottom: connectedLabel.bottom; anchors.bottomMargin: -2 * DynamicResolution.kh;
        source: RuntimeData.connected ? "qrc:/icons/animated/gif_connected.gif" : "qrc:/icons/animated/gif_disconnected.gif";
    }
    Dropdowns.InverseDropdown
    {
        id: connectionInfoDropDown;
        anchors.left: connectedAnimation.left;
        anchors.bottom: parent.top; anchors.bottomMargin: -2 * DynamicResolution.kh;

        fixed_width: 20 * DynamicResolution.kw;
        fixed_height: 17 * DynamicResolution.kh;
        fixed_drop: 17*6  * DynamicResolution.kh;
        fixed_drop_width: 300  * DynamicResolution.kw;
        label_text: "";
        label_color: UX.textWhite;          label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontMedium.name; label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        highlight_color: UX.primaryLight;
        frame_radius: 3 * DynamicResolution.kw;                    frame_width: 0;
        frame_fill_color: UX.primaryDark;   frame_filled: true;
        container: Item {
            Labels.FramedLabel
            {
                id: connectionInfoLabel1;
                anchors.top: parent.top;
                anchors.left: parent.left; anchors.leftMargin: 5 * DynamicResolution.kw;

                fixed_width: 145 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: "IP-АДРЕС РЛС";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel2;
                anchors.top: parent.top;
                anchors.left: connectionInfoLabel1.right;

                fixed_width: 145 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: RuntimeData.sarIP;
                label_color: UX.infoDark;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel3;
                anchors.top: connectionInfoLabel1.bottom;
                anchors.left: parent.left; anchors.leftMargin: 5 * DynamicResolution.kw;

                fixed_width: 145 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: "IP-АДРЕС АРМ";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel4;
                anchors.top: connectionInfoLabel3.top;
                anchors.left: connectionInfoLabel3.right;

                fixed_width: 145 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: RuntimeData.pcIP;
                label_color: UX.infoDark;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel5;
                anchors.top: connectionInfoLabel3.bottom;
                anchors.left: parent.left; anchors.leftMargin: 5 * DynamicResolution.kw;

                fixed_width: 145 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: "ПОРТ ТЕЛЕМЕТРИИ:";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel6;
                anchors.top: connectionInfoLabel5.top;
                anchors.left: connectionInfoLabel5.right;

                fixed_width: 145 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: RuntimeData.telemetryPort;
                label_color: UX.accentDark;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel7;
                anchors.top: connectionInfoLabel6.bottom;
                anchors.left: parent.left; anchors.leftMargin: 5 * DynamicResolution.kw;

                fixed_width: 145 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: "ПОРТ ЗАГРУЗЧИКА:";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel8;
                anchors.top: connectionInfoLabel7.top;
                anchors.left: connectionInfoLabel7.right;

                fixed_width: 145 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: RuntimeData.loaderPort;
                label_color: UX.accentDark;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel9;
                anchors.top: connectionInfoLabel8.bottom;
                anchors.left: parent.left; anchors.leftMargin: 5 * DynamicResolution.kw;

                fixed_width: 145 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: "ПОРТ ОБРАТНОЙ СВЯЗИ:";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel10;
                anchors.top: connectionInfoLabel9.top;
                anchors.left: connectionInfoLabel9.right;

                fixed_width: 145 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: RuntimeData.listenPort;
                label_color: UX.accentDark;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel11;
                anchors.top: connectionInfoLabel10.bottom;
                anchors.left: parent.left; anchors.leftMargin: 5 * DynamicResolution.kw;

                fixed_width: 145 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: "ПОРТ ИНТЕРФЕЙСА ВЫПОЛНЕНИЯ КОМАНД:";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel12;
                anchors.top: connectionInfoLabel11.top;
                anchors.left: connectionInfoLabel11.right;

                fixed_width: 145 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: RuntimeData.commandPort;
                label_color: UX.accentDark;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
        }
    }
    Rectangle
    {
        id: attitudeFrame;
        width: 288 * DynamicResolution.kw;
        height: 168 * DynamicResolution.kh;
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
    Rectangle
    {
        id: speedFrame;
        width: 100 * DynamicResolution.kw;
        height: 31 * DynamicResolution.kh;
        color: UX.primaryDark;
        radius: 12;
        anchors.verticalCenter: attitudeFrame.top;
        anchors.horizontalCenter: attitudeFrame.horizontalCenter;
        Labels.FramedLabel
        {
            id: speedLabel;
            anchors.verticalCenter: speedFrame.verticalCenter;
            anchors.horizontalCenter: speedFrame.horizontalCenter;

            fixed_width: 137 * DynamicResolution.kw;
            fixed_height: 17 * DynamicResolution.kh;
            property real spd: speedDisplayMode ? RuntimeData.speed / 3.6 : RuntimeData.speed;
            label_text: Number(spd).toFixed(1);
            label_color: UX.textWhite;
            label_text_size: 24 * DynamicResolution.kh;
            label_text_family: fontExtraBold.name; label_text_bold: true;
            label_textAlignment: Text.AlignHCenter;
            frame_radius: 2;                    frame_width: 0;
        }
        Rectangle
        {
            id: speedTooltipFrame;
            width: 50 * DynamicResolution.kw;
            height: 22 * DynamicResolution.kh;
            color: UX.primaryDark;
            radius: 6;
            anchors.horizontalCenter: speedFrame.horizontalCenter;
            anchors.top: speedLabel.bottom; anchors.topMargin: 3 * DynamicResolution.kh;
            Labels.FramedLabel
            {
                id: speedTooltipLabel;
                anchors.centerIn: parent;

                fixed_width: 50 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: speedDisplayMode ? "М/С" : "КМ/Ч";
                label_color: UX.textWhite;
                label_text_size: 14 * DynamicResolution.kh;
                label_text_family: fontExtraBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignHCenter;
                frame_radius: 2;                    frame_width: 0;
            }
        }
        MouseArea
        {
            id: changeSpeedModeArea;
            propagateComposedEvents: true;
            anchors.fill: parent; anchors.bottomMargin: -22 * DynamicResolution.kh;
            onClicked:
            {
                if(speedDisplayMode === true)
                {
                    speedDisplayMode = false;
                } else {
                    speedDisplayMode = true;
                }
            }
        }
    }
    Rectangle
    {
        id: statusBar;
        height: 24 * DynamicResolution.kh;
        color: UX.primaryDarker;
        radius: 12;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4 * DynamicResolution.kh;
        anchors.left: parent.left;
        anchors.leftMargin: 4 * DynamicResolution.kw;
        anchors.right: connectedAnimation.left;
        anchors.rightMargin: 10 * DynamicResolution.kw;
        Rectangle
        {
            id: statusBarTooltip;
            width: 65 * DynamicResolution.kw;
            height: 10 * DynamicResolution.kh;
            radius: 3;
            color: UX.primaryDark;
            anchors.verticalCenter: parent.top;
            anchors.horizontalCenter: parent.horizontalCenter;
            Labels.FramedLabel
            {
                id: statusBarTooltipLabel;
                anchors.fill: parent;
                fixed_width: 60 * DynamicResolution.kw;
                fixed_height: 9 * DynamicResolution.kh;
                label_text: "СТАТУС";
                label_color: UX.textFaded;
                label_text_size: 9 * DynamicResolution.kh;
                label_text_family: fontBold.name;
                label_text_bold: true;
                label_textAlignment: Text.AlignHCenter;
                frame_radius: 2;
                frame_width: 0;
            }
        }
        Labels.FramedLabel
        {
            id: statusLabel;
            anchors.fill: parent;
            anchors.margins: 5 * DynamicResolution.kw; anchors.leftMargin: 8 * DynamicResolution.kw;
            fixed_height: 14 * DynamicResolution.kh;
            label_text: RuntimeData.formStatus;
            label_color: UX.textWhite;
            label_text_size: 14 * DynamicResolution.kh;
            label_text_family: fontBold.name;
            label_text_bold: false;
            label_textAlignment: Text.AlignLeft;
            frame_radius: 2;
            frame_width: 0;
        }
    }
}
