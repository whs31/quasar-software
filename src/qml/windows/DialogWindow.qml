import QtQuick 2.15
import QtGraphicalEffects 1.15

import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels

import UX 1.0
import RuntimeData 1.0
import Config 1.0

import DialogWindowBackend 1.0

Rectangle {
	id: window;
	visible: width > 0;
	enabled: DialogWindowBackend.shown;
	height: DialogWindowBackend.shown ? 165 : 0;
	width: DialogWindowBackend.shown ? 473 : 0;
	radius: 35;
	color: UX.primaryDark;
	Behavior on width { NumberAnimation { duration: 150; easing.type: Easing.InOutCubic; } }
	Behavior on height { NumberAnimation { duration: 150; easing.type: Easing.InOutCubic; } }

	FontLoader { id: fontSemiBold; source: "qrc:/fonts/SofiaSans-SemiBold.ttf" }
	FontLoader { id: fontExtraBold; source: "qrc:/fonts/SofiaSans-ExtraBold.ttf" }
	Item {
		id: content;
		anchors.fill: parent;
		visible: DialogWindowBackend.shown;
		opacity: DialogWindowBackend.shown ? 1 : 0;
		Behavior on opacity { NumberAnimation { duration: 350; easing.type: Easing.InOutCubic; } }
		Image {
			id: icon;
			source: DialogWindowBackend.icon;
			fillMode: Image.PreserveAspectFit;
			width: 68;
			height: 68;
			anchors.left: parent.left;
			anchors.leftMargin: 28;
			anchors.verticalCenter: parent.verticalCenter;
			smooth: true;
			antialiasing: true;
			mipmap: true;
		}
		Labels.FramedLabel
		{
			id: headerText;
			anchors.top: parent.top;
			anchors.topMargin: 8;
			anchors.horizontalCenter: parent.horizontalCenter;
			fixed_width: 176;
			fixed_height: 16;
			label_text: DialogWindowBackend.header;
			label_color: UX.textWhite;
			label_text_size: 17;
			label_text_family: fontExtraBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignHCenter;
			frame_radius: 2;
			frame_width: 0;
		}
		Labels.FramedLabel
		{
			id: mainText;
			anchors.verticalCenter: parent.verticalCenter;
			anchors.right: parent.right;
			anchors.rightMargin: 30;
			fixed_width: 324;
			fixed_height: 68;
			label_text: DialogWindowBackend.text;
			label_color: UX.textWhite;
			label_text_size: 14;
			label_text_family: fontSemiBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignLeft;
			frame_radius: 2;
			frame_width: 0;
			label_wrapping: true;
		}
		Buttons.LightButton
		{
			id: okButton;
			anchors.bottom: parent.bottom;
			anchors.bottomMargin: 14;
			anchors.right: parent.horizontalCenter;
			anchors.rightMargin: 15;
			fixed_width: 103;
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
				DialogWindowBackend.accept();
			}
		}
		Buttons.LightButton
		{
			id: cancelButton;
			anchors.bottom: parent.bottom;
			anchors.bottomMargin: 14;
			anchors.left: parent.horizontalCenter;
			anchors.leftMargin: 15;
			fixed_width: 103;
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
				DialogWindowBackend.cancel();
			}
		}
	}
}
