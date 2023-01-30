import QtQuick 2.15
import QtGraphicalEffects 1.15

import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels
import "qrc:/qml/ui/input" as Input
import "qrc:/qml/ui/checkboxes" as Checkboxes

import UX 1.0
import RuntimeData 1.0
import Config 1.0

import MarkerWindowBackend 1.0

Rectangle {
	id: window;
	visible: width > 0;
	enabled: MarkerWindowBackend.shown;
	height: MarkerWindowBackend.shown ? 382 : 0;
	width: MarkerWindowBackend.shown ? 260 : 0;
	radius: 35;
	color: UX.primaryDark;
	Behavior on width { NumberAnimation { duration: 150; easing.type: Easing.InOutCubic; } }
	Behavior on height { NumberAnimation { duration: 150; easing.type: Easing.InOutCubic; } }

	FontLoader { id: fontSemiBold; source: "qrc:/fonts/SofiaSans-SemiBold.ttf" }
	FontLoader { id: fontExtraBold; source: "qrc:/fonts/SofiaSans-ExtraBold.ttf" }
	Item {
		id: content;
		anchors.fill: parent;
		visible: MarkerWindowBackend.shown;
		opacity: MarkerWindowBackend.shown ? 1 : 0;
		Behavior on opacity { NumberAnimation { duration: 350; easing.type: Easing.InOutCubic; } }

		Labels.FramedLabel
		{
			id: headerText;
			anchors.top: parent.top;
			anchors.topMargin: 16;
			anchors.horizontalCenter: parent.horizontalCenter;
			fixed_width: 219;
			fixed_height: 16;
			label_text: "УСТАНОВКА ГЕОМЕТКИ";
			label_color: UX.textWhite;
			label_text_size: 15;
			label_text_family: fontExtraBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignHCenter;
			frame_radius: 2;
			frame_width: 0;
		}
		Labels.FramedLabel
		{
			id: nameText;
			anchors.top: parent.top;
			anchors.topMargin: 48;
			anchors.left: parent.left;
			anchors.leftMargin: 10;
			fixed_width: 76;
			fixed_height: 20;
			label_text: "НАЗВАНИЕ";
			label_color: UX.textWhite;
			label_text_size: 14;
			label_text_family: fontSemiBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignLeft;
			frame_radius: 2;
			frame_width: 0;
			label_wrapping: true;
		}
		Input.FramedLineEdit
		{
			id: nameInput;
			fixed_width: 164;
			fixed_height: 22;
			anchors.bottom: nameText.bottom;
			anchors.left: nameText.right;
			label_color: UX.textWhite;
			label_text_size: 14;
			label_text_family: fontExtraBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignRight;
			highlight_color: UX.primaryDarker;
			frame_radius: 5;
			frame_width: 0;
			frame_enabled: false;
			frame_color: UX.primaryDarker;
			selection_color: UX.warningLight;
			input_text: MarkerWindowBackend.name;
			input_text_postfix: "";
			onTxtChanged: {
				MarkerWindowBackend.name = input_text;
			}
		}
		Labels.FramedLabel
		{
			id: latText;
			anchors.top: nameInput.bottom;
			anchors.topMargin: 11;
			anchors.horizontalCenter: parent.horizontalCenter;
			fixed_width: 67;
			fixed_height: 20;
			label_text: "ШИРОТА";
			label_color: UX.textWhite;
			label_text_size: 14;
			label_text_family: fontSemiBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignLeft;
			frame_radius: 2;
			frame_width: 0;
			label_wrapping: true;
		}
		Input.FramedLineEdit
		{
			id: latInput;
			fixed_width: 91;
			fixed_height: 22;
			anchors.bottom: latText.bottom;
			anchors.left: latText.right;
			label_color: UX.textWhite;
			label_text_size: 14;
			label_text_family: fontExtraBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignRight;
			highlight_color: UX.primaryDarker;
			frame_radius: 5;
			frame_width: 0;
			frame_enabled: false;
			frame_color: UX.primaryDarker;
			selection_color: UX.warningLight;
			input_text: Number(MarkerWindowBackend.latitude).toFixed(5);
			input_text_postfix: "°";
			label_length: 10;
			onTxtChanged: {
				MarkerWindowBackend.latitude = parseFloat(input_text);
			}
		}
		Labels.FramedLabel
		{
			id: lonText;
			anchors.top: latInput.bottom;
			anchors.topMargin: 11;
			anchors.horizontalCenter: parent.horizontalCenter;
			fixed_width: 67;
			fixed_height: 20;
			label_text: "ДОЛГОТА";
			label_color: UX.textWhite;
			label_text_size: 14;
			label_text_family: fontSemiBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignLeft;
			frame_radius: 2;
			frame_width: 0;
			label_wrapping: true;
		}
		Input.FramedLineEdit
		{
			id: lonInput;
			fixed_width: 91;
			fixed_height: 22;
			anchors.bottom: lonText.bottom;
			anchors.left: lonText.right;
			label_color: UX.textWhite;
			label_text_size: 14;
			label_text_family: fontExtraBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignRight;
			highlight_color: UX.primaryDarker;
			frame_radius: 5;
			frame_width: 0;
			frame_enabled: false;
			frame_color: UX.primaryDarker;
			selection_color: UX.warningLight;
			input_text: Number(MarkerWindowBackend.longitude).toFixed(5);
			input_text_postfix: "°";
			label_length: 10;
			onTxtChanged: {
				MarkerWindowBackend.longitude = parseFloat(input_text);
			}
		}
		Checkboxes.LightCheckbox
		{
			id: saveToFileCheckbox;
			fixed_width: 240;
			fixed_height: 20;
			anchors.top: lonInput.bottom;
			anchors.topMargin: 9;
			anchors.horizontalCenter: parent.horizontalCenter;
			label_text: "СОХРАНИТЬ ГЕОМЕТКУ В ФАЙЛ";
			label_color: UX.textWhite;
			label_text_size: 14;
			label_text_family: fontSemiBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignLeft;
			contrast_color: UX.primaryDarker;
			highlight_color: UX.warningLight;
			checked: true;
			onCheckedChanged: {
				MarkerWindowBackend.record = checked;
			}
		}
		Checkboxes.LightCheckbox
		{
			id: screenAnchorCheckbox;
			fixed_width: 240;
			fixed_height: 20;
			anchors.top: saveToFileCheckbox.bottom;
			anchors.topMargin: 9;
			anchors.horizontalCenter: parent.horizontalCenter;
			label_text: "ПРИВЯЗКА РАЗМЕРА К ЭКРАНУ";
			label_color: UX.textWhite;
			label_text_size: 14;
			label_text_family: fontSemiBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignLeft;
			contrast_color: UX.primaryDarker;
			highlight_color: UX.warningLight;
			checked: true;
			onCheckedChanged: {
				MarkerWindowBackend.screenAnchor = checked;
			}
		}
		Labels.FramedLabel
		{
			id: colorText;
			anchors.top: screenAnchorCheckbox.bottom;
			anchors.topMargin: 9;
			anchors.horizontalCenter: parent.horizontalCenter;
			fixed_width: 240;
			fixed_height: 20;
			label_text: "ЦВЕТ ГЕОМЕТКИ";
			label_color: UX.textWhite;
			label_text_size: 14;
			label_text_family: fontSemiBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignLeft;
			frame_radius: 2;
			frame_width: 0;
			label_wrapping: true;
		}
		Buttons.ClassicButton
		{
			id: color_redButton;
			display_mode: Buttons.ClassicButton.Mode.IconOnly;
			anchors.top: colorText.bottom;
			anchors.left: colorText.left;
			fixed_width: 24;
			fixed_height: 24;
			icon_px_size: 0;
			background_color: "#F06292";
			background_secondary_color: Qt.lighter(background_color, 1.5);
			background_radius: 5;
			onClicked: {
				MarkerWindowBackend.colorCode = 7;
			}
		}
		Buttons.ClassicButton
		{
			id: color_orangeButton;
			display_mode: Buttons.ClassicButton.Mode.IconOnly;
			anchors.top: color_redButton.top;
			anchors.left: color_redButton.right;
			anchors.leftMargin: 7;
			fixed_width: 24;
			fixed_height: 24;
			icon_px_size: 0;
			background_color: "#FF8A65";
			background_secondary_color: Qt.lighter(background_color, 1.5);
			background_radius: 5;
			onClicked: {
				MarkerWindowBackend.colorCode = 6;
			}
		}
		Buttons.ClassicButton
		{
			id: color_yellowButton;
			display_mode: Buttons.ClassicButton.Mode.IconOnly;
			anchors.top: color_orangeButton.top;
			anchors.left: color_orangeButton.right;
			anchors.leftMargin: 7;
			fixed_width: 24;
			fixed_height: 24;
			icon_px_size: 0;
			background_color: "#FFF176";
			background_secondary_color: Qt.lighter(background_color, 1.5);
			background_radius: 5;
			onClicked: {
				MarkerWindowBackend.colorCode = 5;
			}
		}
		Buttons.ClassicButton
		{
			id: color_greenButton;
			display_mode: Buttons.ClassicButton.Mode.IconOnly;
			anchors.top: color_yellowButton.top;
			anchors.left: color_yellowButton.right;
			anchors.leftMargin: 7;
			fixed_width: 24;
			fixed_height: 24;
			icon_px_size: 0;
			background_color: "#81C784";
			background_secondary_color: Qt.lighter(background_color, 1.5);
			background_radius: 5;
			onClicked: {
				MarkerWindowBackend.colorCode = 4;
			}
		}
		Buttons.ClassicButton
		{
			id: color_tealButton;
			display_mode: Buttons.ClassicButton.Mode.IconOnly;
			anchors.top: color_greenButton.top;
			anchors.left: color_greenButton.right;
			anchors.leftMargin: 7;
			fixed_width: 24;
			fixed_height: 24;
			icon_px_size: 0;
			background_color: "#80CBC4";
			background_secondary_color: Qt.lighter(background_color, 1.5);
			background_radius: 5;
			onClicked: {
				MarkerWindowBackend.colorCode = 3;
			}
		}
		Buttons.ClassicButton
		{
			id: color_blueButton;
			display_mode: Buttons.ClassicButton.Mode.IconOnly;
			anchors.top: color_tealButton.top;
			anchors.left: color_tealButton.right;
			anchors.leftMargin: 7;
			fixed_width: 24;
			fixed_height: 24;
			icon_px_size: 0;
			background_color: "#90CAF9";
			background_secondary_color: Qt.lighter(background_color, 1.5);
			background_radius: 5;
			onClicked: {
				MarkerWindowBackend.colorCode = 2;
			}
		}
		Buttons.ClassicButton
		{
			id: color_brownButton;
			display_mode: Buttons.ClassicButton.Mode.IconOnly;
			anchors.top: color_blueButton.top;
			anchors.left: color_blueButton.right;
			anchors.leftMargin: 7;
			fixed_width: 24;
			fixed_height: 24;
			icon_px_size: 0;
			background_color: "#BCAAA4";
			background_secondary_color: Qt.lighter(background_color, 1.5);
			background_radius: 5;
			onClicked: {
				MarkerWindowBackend.colorCode = 1;
			}
		}
		Buttons.ClassicButton
		{
			id: color_grayButton;
			display_mode: Buttons.ClassicButton.Mode.IconOnly;
			anchors.top: color_brownButton.top;
			anchors.left: color_brownButton.right;
			anchors.leftMargin: 7;
			fixed_width: 24;
			fixed_height: 24;
			icon_px_size: 0;
			background_color: "#B0BEC5";
			background_secondary_color: Qt.lighter(background_color, 1.5);
			background_radius: 5;
			onClicked: {
				MarkerWindowBackend.colorCode = 0;
			}
		}
		Labels.FramedLabel
		{
			id: iconText;
			anchors.top: color_grayButton.bottom;
			anchors.topMargin: 17;
			anchors.horizontalCenter: parent.horizontalCenter;
			fixed_width: 240;
			fixed_height: 20;
			label_text: "ЗНАЧОК ГЕОМЕТКИ";
			label_color: UX.textWhite;
			label_text_size: 14;
			label_text_family: fontSemiBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignLeft;
			frame_radius: 2;
			frame_width: 0;
			label_wrapping: true;
		}

		Image {
			property int markerIconState: 1;
			property int maxMarkerIconEnumState: 3;

			id: icon;
			source: "qrc:/map/markers/flag.png";
			fillMode: Image.PreserveAspectFit;
			width: 43;
			height: 43;
			anchors.horizontalCenter: parent.horizontalCenter;
			anchors.top: iconText.bottom
			anchors.topMargin: 9;
			smooth: true;
			antialiasing: true;
			mipmap: true;
		}
		Buttons.ClassicButton
		{
			id: rightButton;
			display_mode: Buttons.ClassicButton.Mode.IconOnly;
			anchors.verticalCenter: icon.verticalCenter;
			anchors.left: icon.right;
			anchors.leftMargin: 11;
			fixed_width: 30;
			fixed_height: 30;
			icon_px_size: 24;
			icon_source: "qrc:/icons/right.png";
			background_color: UX.primaryDark;
			background_secondary_color: Qt.lighter(background_color, 1.5);
			background_radius: 5;
			onClicked: {
				if(icon.markerIconState < icon.maxMarkerIconEnumState)
				{
					icon.markerIconState += 1;
				} else {
					icon.markerIconState = 0;
				}
				MarkerWindowBackend.iconCode = icon.markerIconState;
				if(icon.markerIconState === 0) { icon.source = "qrc:/map/markers/default.png"; }
				if(icon.markerIconState === 1) { icon.source = "qrc:/map/markers/flag.png"; }
				if(icon.markerIconState === 2) { icon.source = "qrc:/map/markers/radar.png"; }
				if(icon.markerIconState === 3) { icon.source = "qrc:/map/markers/autocapture.png"; }
			}
		}
		Buttons.ClassicButton
		{
			id: leftButton;
			display_mode: Buttons.ClassicButton.Mode.IconOnly;
			anchors.verticalCenter: icon.verticalCenter;
			anchors.right: icon.left;
			anchors.rightMargin: 8;
			fixed_width: 30;
			fixed_height: 30;
			icon_px_size: 24;
			icon_source: "qrc:/icons/left.png";
			background_color: UX.primaryDark;
			background_secondary_color: Qt.lighter(background_color, 1.5);
			background_radius: 5;
			onClicked: {
				if(icon.markerIconState > 0)
				{
					icon.markerIconState -= 1;
				} else {
					icon.markerIconState = icon.maxMarkerIconEnumState;
				}
				MarkerWindowBackend.iconCode = icon.markerIconState;
				if(icon.markerIconState === 0) { icon.source = "qrc:/map/markers/default.png"; }
				if(icon.markerIconState === 1) { icon.source = "qrc:/map/markers/flag.png"; }
				if(icon.markerIconState === 2) { icon.source = "qrc:/map/markers/radar.png"; }
				if(icon.markerIconState === 3) { icon.source = "qrc:/map/markers/autocapture.png"; }
			}
		}

		Buttons.LightButton
		{
			id: okButton;
			anchors.bottom: parent.bottom;
			anchors.bottomMargin: 14;
			anchors.right: parent.horizontalCenter;
			anchors.rightMargin: 10;
			fixed_width: 70;
			fixed_height: 20;
			label_text: "ОК";
			label_color: UX.textWhite;
			label_text_size: 14;
			label_text_family: fontBold.name;
			label_text_bold: true;         label_textAlignment: Text.AlignHCenter;
			highlight_color: UX.successLighter;
			frame_radius: 6;
			frame_width: 1;
			frame_enabled: true;
			onClicked: {
				MarkerWindowBackend.accept();
			}
		}
		Buttons.LightButton
		{
			id: cancelButton;
			anchors.bottom: parent.bottom;
			anchors.bottomMargin: 14;
			anchors.left: parent.horizontalCenter;
			anchors.leftMargin: 10;
			fixed_width: 70
			fixed_height: 20;
			label_text: "ОТМЕНА";
			label_color: UX.textWhite;
			label_text_size: 14;
			label_text_family: fontBold.name;
			label_text_bold: true;         label_textAlignment: Text.AlignHCenter;
			highlight_color: UX.errorDark;
			frame_radius: 6;
			frame_width: 1;
			frame_enabled: true;
			onClicked: {
				MarkerWindowBackend.cancel();
			}
		}
	}
}
