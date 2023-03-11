import QtQuick 2.12
import Theme 1.0
import RuntimeData 1.0
import Config 1.0
import SignalLinker 1.0
import DiskManager 1.0
import Theme 1.0
import DialogWindowBackend 1.0

import Telemetry 1.0

import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels
import "qrc:/qml/ui/dropdowns" as Dropdowns
import "qrc:/qml/ui/layouts" as Layouts
import "qrc:/qml/ui/widgets" as CustomWidgets

Rectangle {
    property bool speedDisplayMode: false;
    id: base;
	height: 36 * Theme.scalingFactor.y;
    color: Theme.color("dark1");
    FontLoader { id: fontRegular; source: "qrc:/fonts/SofiaSans-Regular.ttf" }
    FontLoader { id: fontMedium; source: "qrc:/fonts/SofiaSans-Medium.ttf" }
    FontLoader { id: fontSemiBold; source: "qrc:/fonts/SofiaSans-SemiBold.ttf" }
    FontLoader { id: fontBold; source: "qrc:/fonts/SofiaSans-Bold.ttf" }
    FontLoader { id: fontExtraBold; source: "qrc:/fonts/SofiaSans-ExtraBold.ttf" }
    Labels.FramedLabel
    {
        id: satsLabel;
		anchors.bottom: parent.bottom;  anchors.bottomMargin: 8 * Theme.scalingFactor.y;
		anchors.right: parent.right; anchors.rightMargin: 5 * Theme.scalingFactor.x;

		fixed_width: 16 * Theme.scalingFactor.x;
		fixed_height: 19 * Theme.scalingFactor.y;
        label_text: Number(Telemetry.satellites);
        label_color: Theme.color("light1");
		label_text_size: 16 * Theme.scalingFactor.y;
        label_text_family: fontBold.name;   label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        frame_radius: 2;                        frame_width: 0;
    }
    Image {
        id: satsIcon;
		width: 22 * Theme.scalingFactor.x;
		height: 22 * Theme.scalingFactor.y;
        source: "qrc:/icons/satellite.png";
        smooth: true;
        antialiasing: true;
        anchors.right: satsLabel.left;
		anchors.rightMargin: 2 * Theme.scalingFactor.x;
        anchors.verticalCenter: parent.verticalCenter;
    }
    Buttons.ImageButton
    {
        id: mapmodeSchemeButton;
		anchors.right: satsIcon.left; anchors.rightMargin: 8 * Theme.scalingFactor.x;
		anchors.top: parent.top; anchors.topMargin: 4 * Theme.scalingFactor.y;
		fixed_width: 60 * Theme.scalingFactor.x;
		fixed_height: 8 * Theme.scalingFactor.y;
        image_source: "qrc:/icons/map-layers/schema.png";
        frame_color: Theme.color("light1");
        hover_color: Theme.color("color1");
        frame_width: 1; frame_radius: 1;
        enabled: Config.onlineMaps;
        onClicked: { mapView.activeMapType = mapView.supportedMapTypes[5]; }
    }
    Buttons.ImageButton
    {
        id: mapmodeSatelliteButton;
        anchors.right: mapmodeSchemeButton.right;
		anchors.top: mapmodeSchemeButton.bottom; anchors.topMargin: 2 * Theme.scalingFactor.y;
		fixed_width: 60 * Theme.scalingFactor.x;    fixed_height: 8 * Theme.scalingFactor.y;
        image_source: "qrc:/icons/map-layers/satellite.png";
        frame_color: Theme.color("light1");
        hover_color: Theme.color("color1");
        frame_width: 1; frame_radius: 1;
        enabled: Config.onlineMaps;
		onClicked: { mapView.activeMapType = mapView.supportedMapTypes[1]; }
    }
    Buttons.ImageButton
    {
        id: mapmodeHybridButton;
        anchors.right: mapmodeSatelliteButton.right;
        anchors.top: mapmodeSatelliteButton.bottom;
		anchors.topMargin: 2 * Theme.scalingFactor.y;
		fixed_width: 60 * Theme.scalingFactor.x;
		fixed_height: 8 * Theme.scalingFactor.y;
        image_source: "qrc:/icons/map-layers/hybrid.png";
        frame_color: Theme.color("light1");
        hover_color: Theme.color("color1");
        frame_width: 1; frame_radius: 1;
        enabled: Config.onlineMaps;
        onClicked: { mapView.activeMapType = mapView.supportedMapTypes[4]; }
    }
    Labels.FramedLabel
    {
        id: mapLayersLabel;
        anchors.verticalCenter: mapmodeSatelliteButton.verticalCenter;
        anchors.right: mapmodeSatelliteButton.left;
		anchors.rightMargin: 3 * Theme.scalingFactor.x;

		fixed_width: 40 * Theme.scalingFactor.x;
		fixed_height: 26 * Theme.scalingFactor.y;
        label_text: "СЛОИ <br> КАРТЫ";
        label_color: Theme.color("light1");
		label_text_size: 12 * Theme.scalingFactor.y;
        label_text_family: fontBold.name;       label_text_bold: true;
        label_textAlignment: Text.AlignRight;
        frame_radius: 2;                        frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: heightTerrainDisplayLabel;
		anchors.top: parent.top; anchors.topMargin: 2 * Theme.scalingFactor.y;
        anchors.right: mapLayersLabel.left;

		fixed_width: 65 * Theme.scalingFactor.x;
		fixed_height: 17 * Theme.scalingFactor.y;
        label_text: Number(Telemetry.elevation - Telemetry.seaLevel).toFixed(0) + " М";
        label_color: Theme.color("light1");
		label_text_size: 16 * Theme.scalingFactor.y;
        label_text_family: fontExtraBold.name;       label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: heightSeaDisplayLabel;
        anchors.top: heightTerrainDisplayLabel.bottom;
        anchors.right: mapLayersLabel.left;

		fixed_width: 65 * Theme.scalingFactor.x;
		fixed_height: 12 * Theme.scalingFactor.y;
        label_text: Number(Telemetry.elevation).toFixed(0) + " М";
        label_color: Theme.color("light1");                label_text_size: 12 * Theme.scalingFactor.y;
        label_text_family: fontExtraBold.name;      label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                            frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: heightTerrainLabel;
        anchors.top: parent.top;
		anchors.topMargin: 2 * Theme.scalingFactor.y;
        anchors.right: heightTerrainDisplayLabel.left;

		fixed_width: 130 * Theme.scalingFactor.x;
		fixed_height: 17 * Theme.scalingFactor.y;
        label_text: "ВЫСОТА: ";
        label_color: Theme.color("light1");
		label_text_size: 12 * Theme.scalingFactor.y;
        label_text_family: fontExtraBold.name;       label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Image {
        id: terrainIcon;
		width: 16 * Theme.scalingFactor.x;
		height: 16 * Theme.scalingFactor.y;
        source: "qrc:/icons/mountain.png";
        smooth: true;
        antialiasing: true;
		anchors.right: heightTerrainLabel.left;  anchors.rightMargin: 2 * Theme.scalingFactor.x;
		anchors.verticalCenter: heightTerrainLabel.verticalCenter; anchors.verticalCenterOffset: -1 * Theme.scalingFactor.x;
    }
    Labels.FramedLabel
    {
        id: heightSeaLabel;
        anchors.top: heightTerrainDisplayLabel.bottom;
        anchors.right: heightSeaDisplayLabel.left;

		fixed_width: 130 * Theme.scalingFactor.x;
		fixed_height: 12 * Theme.scalingFactor.y;
        label_text: "НАД УРОВНЕМ МОРЯ: ";
        label_color: Theme.color("light1");
		label_text_size: 12 * Theme.scalingFactor.y;
        label_text_family: fontBold.name;       label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Image {
        id: seaIcon;
		width: 16 * Theme.scalingFactor.x;
		height: 16 * Theme.scalingFactor.y;
        source: "qrc:/icons/water.png";
        smooth: true;
        antialiasing: true;
        anchors.right: heightSeaLabel.left;
		anchors.rightMargin: 2 * Theme.scalingFactor.x;
        anchors.verticalCenter: heightSeaLabel.verticalCenter;
		anchors.verticalCenterOffset: -1 * Theme.scalingFactor.y;
    }
    Labels.FramedLabel
    {
        id: latitudeLabel;
		anchors.top: parent.top; anchors.topMargin: 4 * Theme.scalingFactor.y;
		anchors.right: seaIcon.left; anchors.rightMargin: 17 * Theme.scalingFactor.x;

		fixed_width: 142 * Theme.scalingFactor.x;    fixed_height: 12 * Theme.scalingFactor.y;
        label_text: "<b>ШИРОТА:</b>     " + Number(Telemetry.latitude).toFixed(5) + " °N";
        label_color: Theme.color("light1");
		label_text_size: 12 * Theme.scalingFactor.y;
        label_text_family: fontBold.name;       label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: longitudeLabel;
		anchors.top: latitudeLabel.bottom; anchors.topMargin: 3 * Theme.scalingFactor.y;
		anchors.right: seaIcon.left; anchors.rightMargin: 17 * Theme.scalingFactor.x;

		fixed_width: 142 * Theme.scalingFactor.x;    fixed_height: 12 * Theme.scalingFactor.y;
        label_text: "<b>ДОЛГОТА:</b>     " + Number(Telemetry.longitude).toFixed(5) + " °E";
        label_color: Theme.color("light1");              label_text_size: 12 * Theme.scalingFactor.y;
        label_text_family: fontBold.name;       label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                        frame_width: 0;
    }
    Buttons.LightButton
    {
        id: connectButton;
		anchors.bottom: parent.bottom; anchors.bottomMargin: 4 * Theme.scalingFactor.y;
		anchors.right: longitudeLabel.left; anchors.rightMargin: 19 * Theme.scalingFactor.x;
		fixed_width: 155 * Theme.scalingFactor.x;               fixed_height: 16 * Theme.scalingFactor.y;
        label_text: RuntimeData.connected ? "ОТКЛЮЧИТЬСЯ" : "ПОДКЛЮЧИТЬСЯ";
        label_color: Theme.color("light1");  label_text_size: 12 * Theme.scalingFactor.y;
        label_text_family: fontBold.name;
        label_text_bold: true;         label_textAlignment: Text.AlignHCenter;
        highlight_color: RuntimeData.connected ? Theme.color("red") : Theme.color("green");
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
		anchors.bottom: parent.bottom;      anchors.bottomMargin: 8 * Theme.scalingFactor.y;
        anchors.right: connectButton.left;

		fixed_width: 101 * Theme.scalingFactor.x;    fixed_height: 17 * Theme.scalingFactor.y;
        label_text: RuntimeData.connected ? "ПОДКЛЮЧЕНО" : "НЕТ СВЯЗИ";
        label_color: RuntimeData.connected ? Theme.color("green") : Theme.color("red");
		label_text_size: 14 * Theme.scalingFactor.y;
        label_text_family: fontExtraBold.name; label_text_bold: true;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2;                    frame_width: 0;
    }
    Buttons.SmallRoundButton
    {
        id: checkConnectionButton;
        enabled: !RuntimeData.windowLock;
		fixed_width: 36 * Theme.scalingFactor.x;
		fixed_height: 11 * Theme.scalingFactor.y;
        anchors.left: connectButton.left;
        anchors.bottom: connectButton.top;
		anchors.bottomMargin: 3 * Theme.scalingFactor.y;

        background_color: Theme.color("light0");
        background_radius: 8;
        label_text: "CHECK";
        label_color: Theme.color("dark1");
		label_text_size: 10 * Theme.scalingFactor.y;
        label_text_family: fontBold.name;
        label_text_bold: false;
        tooltip_text: "Проверка систем РЛС";
        tooltip_enabled: true;
        label_textAlignment: Text.AlignHCenter;
        highlight_color: Theme.color("yellow");
        onClicked: { console.log("check is not yet implemented!"); }
    }
    Buttons.SmallRoundButton
    {
		property bool waitingForDialogResponse: false;

        id: calibrateSeaLLevelButton;
        enabled: !RuntimeData.windowLock;
		fixed_width: 24 * Theme.scalingFactor.x;
		fixed_height: 11 * Theme.scalingFactor.y;
        anchors.left: checkConnectionButton.right;
		anchors.leftMargin: 3 * Theme.scalingFactor.x;
        anchors.bottom: connectButton.top;
		anchors.bottomMargin: 3 * Theme.scalingFactor.y;
        background_color: Theme.color("light0");
        background_radius: 8;
        label_text: "CAL";
        label_color: Theme.color("dark1");
		label_text_size: 10 * Theme.scalingFactor.y;
        label_text_family: fontBold.name;
        label_text_bold: false;
        label_textAlignment: Text.AlignHCenter;
        highlight_color: Theme.color("yellow");
        tooltip_text: "Калибровка высоты относительно поверхности";
        tooltip_enabled: true;
		onClicked: {
			RuntimeData.windowLock = true;
			DialogWindowBackend.header = "КАЛИБРОВКА ВЫСОТЫ";
			DialogWindowBackend.icon = "qrc:/icons/dialog/info.png";
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
					Telemetry.seaLevel = Telemetry.elevation;
                    waitingForDialogResponse = false;
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
		fixed_width: 89 * Theme.scalingFactor.x;
		fixed_height: 11 * Theme.scalingFactor.y;
        anchors.left: calibrateSeaLLevelButton.right;
		anchors.leftMargin: 3 * Theme.scalingFactor.x;
        anchors.bottom: connectButton.top;
		anchors.bottomMargin: 3 * Theme.scalingFactor.y;

        background_color: Theme.color("light0");
        background_radius: 8;
        label_text: "COMMAND";
        label_color: Theme.color("dark1");
		label_text_size: 10 * Theme.scalingFactor.y;
        label_text_family: fontBold.name;
        label_text_bold: false;
        label_textAlignment: Text.AlignHCenter;
        highlight_color: Theme.color("yellow");
        tooltip_text: "Выполнить shell-команду на РЛС";
        tooltip_enabled: true;
        onClicked: { console.log("custom command is not yet implemented (needs custom window)!"); }
    }
    AnimatedImage
    {
        id: connectedAnimation;
		width: 24 * Theme.scalingFactor.x; height: 24 * Theme.scalingFactor.y;
        anchors.right: connectedLabel.left;
		anchors.bottom: connectedLabel.bottom; anchors.bottomMargin: -2 * Theme.scalingFactor.y;
        source: RuntimeData.connected ? "qrc:/icons/animated/gif_connected.gif" : "qrc:/icons/animated/gif_disconnected.gif";
    }
    Dropdowns.InverseDropdown
    {
        id: connectionInfoDropDown;
        anchors.left: connectedAnimation.left;
		anchors.bottom: parent.top; anchors.bottomMargin: -2 * Theme.scalingFactor.y;

		fixed_width: 20 * Theme.scalingFactor.x;
		fixed_height: 17 * Theme.scalingFactor.y;
		fixed_drop: 17*6  * Theme.scalingFactor.y;
		fixed_drop_width: 300  * Theme.scalingFactor.x;
        label_text: "";
        label_color: Theme.color("light1");          label_text_size: 12 * Theme.scalingFactor.y;
        label_text_family: fontMedium.name; label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        highlight_color: Theme.color("dark3");
		frame_radius: 3 * Theme.scalingFactor.x;                    frame_width: 0;
        frame_fill_color: Theme.color("dark1");   frame_filled: true;
        container: Item {
            Labels.FramedLabel
            {
                id: connectionInfoLabel1;
                anchors.top: parent.top;
				anchors.left: parent.left; anchors.leftMargin: 5 * Theme.scalingFactor.x;

				fixed_width: 145 * Theme.scalingFactor.x;
				fixed_height: 17 * Theme.scalingFactor.y;
                label_text: "IP-АДРЕС РЛС";
                label_color: Theme.color("dark1");
				label_text_size: 12 * Theme.scalingFactor.y;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel2;
                anchors.top: parent.top;
                anchors.left: connectionInfoLabel1.right;

				fixed_width: 145 * Theme.scalingFactor.x;
				fixed_height: 17 * Theme.scalingFactor.y;
                label_text: RuntimeData.sarIP;
                label_color: Theme.color("color0");
				label_text_size: 12 * Theme.scalingFactor.y;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel3;
                anchors.top: connectionInfoLabel1.bottom;
				anchors.left: parent.left; anchors.leftMargin: 5 * Theme.scalingFactor.x;

				fixed_width: 145 * Theme.scalingFactor.x;
				fixed_height: 17 * Theme.scalingFactor.y;
                label_text: "IP-АДРЕС АРМ";
                label_color: Theme.color("dark1");
				label_text_size: 12 * Theme.scalingFactor.y;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel4;
                anchors.top: connectionInfoLabel3.top;
                anchors.left: connectionInfoLabel3.right;

				fixed_width: 145 * Theme.scalingFactor.x;
				fixed_height: 17 * Theme.scalingFactor.y;
                label_text: RuntimeData.pcIP;
                label_color: Theme.color("color0");
				label_text_size: 12 * Theme.scalingFactor.y;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel5;
                anchors.top: connectionInfoLabel3.bottom;
				anchors.left: parent.left; anchors.leftMargin: 5 * Theme.scalingFactor.x;

				fixed_width: 145 * Theme.scalingFactor.x;
				fixed_height: 17 * Theme.scalingFactor.y;
                label_text: "ПОРТ ТЕЛЕМЕТРИИ:";
                label_color: Theme.color("dark1");
				label_text_size: 12 * Theme.scalingFactor.y;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel6;
                anchors.top: connectionInfoLabel5.top;
                anchors.left: connectionInfoLabel5.right;

				fixed_width: 145 * Theme.scalingFactor.x;
				fixed_height: 17 * Theme.scalingFactor.y;
                label_text: RuntimeData.telemetryPort;
                label_color: Theme.color("accent");
				label_text_size: 12 * Theme.scalingFactor.y;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel7;
                anchors.top: connectionInfoLabel6.bottom;
				anchors.left: parent.left; anchors.leftMargin: 5 * Theme.scalingFactor.x;

				fixed_width: 145 * Theme.scalingFactor.x;
				fixed_height: 17 * Theme.scalingFactor.y;
                label_text: "ПОРТ ЗАГРУЗЧИКА:";
                label_color: Theme.color("dark1");
				label_text_size: 12 * Theme.scalingFactor.y;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel8;
                anchors.top: connectionInfoLabel7.top;
                anchors.left: connectionInfoLabel7.right;

				fixed_width: 145 * Theme.scalingFactor.x;
				fixed_height: 17 * Theme.scalingFactor.y;
                label_text: RuntimeData.loaderPort;
                label_color: Theme.color("accent");
				label_text_size: 12 * Theme.scalingFactor.y;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel9;
                anchors.top: connectionInfoLabel8.bottom;
				anchors.left: parent.left; anchors.leftMargin: 5 * Theme.scalingFactor.x;

				fixed_width: 145 * Theme.scalingFactor.x;
				fixed_height: 17 * Theme.scalingFactor.y;
                label_text: "ПОРТ ОБРАТНОЙ СВЯЗИ:";
                label_color: Theme.color("dark1");
				label_text_size: 12 * Theme.scalingFactor.y;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel10;
                anchors.top: connectionInfoLabel9.top;
                anchors.left: connectionInfoLabel9.right;

				fixed_width: 145 * Theme.scalingFactor.x;
				fixed_height: 17 * Theme.scalingFactor.y;
                label_text: RuntimeData.listenPort;
                label_color: Theme.color("accent");
				label_text_size: 12 * Theme.scalingFactor.y;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel11;
                anchors.top: connectionInfoLabel10.bottom;
				anchors.left: parent.left; anchors.leftMargin: 5 * Theme.scalingFactor.x;

				fixed_width: 145 * Theme.scalingFactor.x;
				fixed_height: 17 * Theme.scalingFactor.y;
                label_text: "ПОРТ ИНТЕРФЕЙСА ВЫПОЛНЕНИЯ КОМАНД:";
                label_color: Theme.color("dark1");
				label_text_size: 12 * Theme.scalingFactor.y;
                label_text_family: fontSemiBold.name; label_text_bold: false;
                label_textAlignment: Text.AlignLeft;
                frame_radius: 2;                    frame_width: 0;
            }
            Labels.FramedLabel
            {
                id: connectionInfoLabel12;
                anchors.top: connectionInfoLabel11.top;
                anchors.left: connectionInfoLabel11.right;

				fixed_width: 145 * Theme.scalingFactor.x;
				fixed_height: 17 * Theme.scalingFactor.y;
                label_text: RuntimeData.commandPort;
                label_color: Theme.color("accent");
				label_text_size: 12 * Theme.scalingFactor.y;
                label_text_family: fontSemiBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignRight;
                frame_radius: 2;                    frame_width: 0;
            }
        }
    }
    Rectangle
    {
        id: attitudeFrame;
		width: 208 * Theme.scalingFactor.x;
		height: 118 * Theme.scalingFactor.y;
        color: Theme.color("dark1");
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
		width: 100 * Theme.scalingFactor.x;
		height: 31 * Theme.scalingFactor.y;
        color: Theme.color("dark1");
        radius: 12;
        anchors.verticalCenter: attitudeFrame.top;
        anchors.horizontalCenter: attitudeFrame.horizontalCenter;
        Labels.FramedLabel
        {
            id: speedLabel;
            anchors.verticalCenter: speedFrame.verticalCenter;
            anchors.horizontalCenter: speedFrame.horizontalCenter;

			fixed_width: 137 * Theme.scalingFactor.x;
			fixed_height: 17 * Theme.scalingFactor.y;
            property real spd: speedDisplayMode ? Telemetry.speed / 3.6 : Telemetry.speed;
            label_text: Number(spd).toFixed(1);
            label_color: Theme.color("light1");
			label_text_size: 24 * Theme.scalingFactor.y;
            label_text_family: fontExtraBold.name; label_text_bold: true;
            label_textAlignment: Text.AlignHCenter;
            frame_radius: 2;                    frame_width: 0;
        }
        Rectangle
        {
            id: speedTooltipFrame;
			width: 50 * Theme.scalingFactor.x;
			height: 22 * Theme.scalingFactor.y;
            color: Theme.color("dark1");
            radius: 6;
            anchors.horizontalCenter: speedFrame.horizontalCenter;
			anchors.top: speedLabel.bottom; anchors.topMargin: 3 * Theme.scalingFactor.y;
            Labels.FramedLabel
            {
                id: speedTooltipLabel;
                anchors.centerIn: parent;

				fixed_width: 50 * Theme.scalingFactor.x;
				fixed_height: 17 * Theme.scalingFactor.y;
                label_text: speedDisplayMode ? "М/С" : "КМ/Ч";
                label_color: Theme.color("light1");
				label_text_size: 14 * Theme.scalingFactor.y;
                label_text_family: fontExtraBold.name; label_text_bold: true;
                label_textAlignment: Text.AlignHCenter;
                frame_radius: 2;                    frame_width: 0;
            }
        }
        MouseArea
        {
            id: changeSpeedModeArea;
            propagateComposedEvents: true;
			anchors.fill: parent; anchors.bottomMargin: -22 * Theme.scalingFactor.y;
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
		height: 24 * Theme.scalingFactor.y;
        color: Theme.color("dark1");
        radius: 12;
        anchors.bottom: parent.bottom;
		anchors.bottomMargin: 4 * Theme.scalingFactor.y;
        anchors.left: parent.left;
		anchors.leftMargin: 4 * Theme.scalingFactor.x;
        anchors.right: connectedAnimation.left;
		anchors.rightMargin: 10 * Theme.scalingFactor.x;
        Rectangle
        {
            id: statusBarTooltip;
			width: 65 * Theme.scalingFactor.x;
			height: 10 * Theme.scalingFactor.y;
            radius: 3;
            color: Theme.color("dark1");
            anchors.verticalCenter: parent.top;
            anchors.horizontalCenter: parent.horizontalCenter;
            Labels.FramedLabel
            {
                id: statusBarTooltipLabel;
                anchors.fill: parent;
				fixed_width: 60 * Theme.scalingFactor.x;
				fixed_height: 9 * Theme.scalingFactor.y;
                label_text: "СТАТУС";
                label_color: Theme.color("light0");
				label_text_size: 9 * Theme.scalingFactor.y;
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
			anchors.margins: 5 * Theme.scalingFactor.x; anchors.leftMargin: 8 * Theme.scalingFactor.x;
			fixed_height: 14 * Theme.scalingFactor.y;
            label_text: RuntimeData.formStatus;
            label_color: Theme.color("light1");
			label_text_size: 14 * Theme.scalingFactor.y;
            label_text_family: fontBold.name;
            label_text_bold: false;
            label_textAlignment: Text.AlignLeft;
            frame_radius: 2;
            frame_width: 0;
        }
    }
}
