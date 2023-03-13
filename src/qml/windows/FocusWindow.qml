import QtQuick 2.15
import RuntimeData 1.0
import Config 1.0
import Theme 1.0
import QtGraphicalEffects 1.15

import FocusWindowBackend 1.0

import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels
import "qrc:/qml/ui/input" as Input

Rectangle {
	id: window;
	visible: FocusWindowBackend.shown;
	enabled: FocusWindowBackend.shown;
	height: FocusWindowBackend.shown ? root.tabWorkspaceHeight : 0;
	width: FocusWindowBackend.shown ? root.tabWorkspaceWidth : 0;
    color: Theme.color("dark0");

	FontLoader { id: fontBold; source: "qrc:/fonts/SofiaSans-Bold.ttf" }
	FontLoader { id: fontExtraBold; source: "qrc:/fonts/SofiaSans-ExtraBold.ttf" }
	Item {
		id: content;
		anchors.fill: parent;
		visible: FocusWindowBackend.shown;
		opacity: FocusWindowBackend.shown ? 1 : 0;
		Behavior on opacity { NumberAnimation { duration: 350; easing.type: Easing.InOutCubic; } }
		Labels.FramedLabel
		{
			id: headerText;
			anchors.top: parent.top;
			anchors.topMargin: 8;
			anchors.left: parent.left;
			anchors.leftMargin: 3;
			fixed_width: 282;
			fixed_height: 13;
			label_text: "ФОКУСИРОВКА ИЗОБРАЖЕНИЯ";
            label_color: Theme.color("light1");
			label_text_size: 17;
			label_text_family: fontExtraBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignLeft;
			frame_radius: 2;
			frame_width: 0;
		}

		Buttons.LightToolButton
		{
			id: areaOutButton;
			anchors.bottom: parent.bottom;
			anchors.bottomMargin: 13;
			anchors.left: parent.left;
			anchors.leftMargin: 23;

			fixed_width: 18;
			fixed_height: 18;
            frame_color: Theme.color("light1");
            highlight_color: Theme.color("accent");
			frame_radius: 2;
			frame_enabled: true;
			icon_px_size: 12;
			icon_source: "qrc:/icons/minus.png";
			tooltip_text: "Уменьшить размер области для фокусировки";
			tooltip_enabled: true;
			label_text_family: fontMedium.name;
			onClicked: {
				if(FocusWindowBackend.sideLength > 10) { FocusWindowBackend.sideLength -= 5; }
			}
		}
		Input.FramedSlider
		{
			id: areaSlider;
			anchors.top: areaOutButton.top;
			anchors.left: areaOutButton.right;
			anchors.leftMargin: 2;
			fixed_width: 167;
			fixed_height: 18;
            fill_color: Theme.color("light1");
            highlight_color: Theme.color("light1");
			frame_radius: 2;
			slider_fromvalue: 5;
			slider_tovalue: 1000;
			slider_horizontal: true;
			slider_value: FocusWindowBackend.sideLength;
			onMoved: { FocusWindowBackend.sideLength = slider_value; }
		}
		Buttons.LightToolButton
		{
			id: areaInButton;
			anchors.top: areaSlider.top;
			anchors.left: areaSlider.right;
			anchors.leftMargin: 2;

			fixed_width: 18;
			fixed_height: 18;
            frame_color: Theme.color("light1");
            highlight_color: Theme.color("accent");
			frame_radius: 2;
			frame_enabled: true;
			icon_px_size: 12;
			icon_source: "qrc:/icons/plus.png";
			tooltip_text: "Увеличить размер области для фокусировки";
			tooltip_enabled: true;
			label_text_family: fontMedium.name;
			onClicked: {
				if(FocusWindowBackend.sideLength < 995) { FocusWindowBackend.sideLength += 5; }
			}
		}

		Labels.FramedLabel
		{
			id: areaLabel;
			anchors.bottom: areaOutButton.top;
			anchors.bottomMargin: 4;
			anchors.left: areaOutButton.left;

			fixed_width: 152;
			fixed_height: 14;
			label_text: "РАЗМЕР ОБЛАСТИ";
            label_color: Theme.color("light1");
			label_text_size: 12;
			label_text_family: fontSemiBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignLeft;
			frame_radius: 2;
			frame_width: 0;
		}
		Labels.FramedLabel
		{
			id: areaLabelValue;
			anchors.top: areaLabel.top;
			anchors.left: areaLabel.right;

			fixed_width: 114;
			fixed_height: 14;
			label_text: Number(FocusWindowBackend.sideLength).toFixed(0) + " м";
            label_color: Theme.color("light1");
			label_text_size: 12;
			label_text_family: fontExtraBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignRight;
			frame_radius: 2;
			frame_width: 0;
		}

		Labels.FramedLabel
		{
			id: coordsLabel;
			anchors.bottom: areaLabel.top;
			anchors.bottomMargin: 2;
			anchors.left: areaLabel.left;

			fixed_width: 152;
			fixed_height: 14;
			label_text: "ВЫБРАННЫЕ КООРДИНАТЫ";
            label_color: Theme.color("light1");
			label_text_size: 12;
			label_text_family: fontSemiBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignLeft;
			frame_radius: 2;
			frame_width: 0;
		}
		Labels.FramedLabel
		{
			id: coordsLabelValue;
			anchors.top: coordsLabel.top;
			anchors.left: coordsLabel.right;

			fixed_width: 114;
			fixed_height: 14;
			label_text: "X: " + Number(FocusWindowBackend.x).toFixed(0) + " m,   Y: " + Number(FocusWindowBackend.y).toFixed() + " m";
            label_color: Theme.color("light1");
			label_text_size: 12;
			label_text_family: fontExtraBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignRight;
			frame_radius: 2;
			frame_width: 0;
		}

		Buttons.LightButton
		{
			id: cancelButton;
			anchors.bottom: parent.bottom;
			anchors.bottomMargin: 14;
			anchors.right: parent.right;
			anchors.rightMargin: 15;
			fixed_width: 103;
			fixed_height: 20;
			label_text: "ОТМЕНА";
            label_color: Theme.color("light1");
			label_text_size: 14;
			label_text_family: fontBold.name;
			label_text_bold: true;         label_textAlignment: Text.AlignHCenter;
            highlight_color: Theme.color("red");
			frame_radius: 6;
			frame_width: 1;
			frame_enabled: true;
			onClicked: {
				FocusWindowBackend.cancel();
				imageView.returnToBounds();
				imageSource.zoom = 0;
			}
		}
		Buttons.LightButton
		{
			id: okButton;
			anchors.bottom: parent.bottom;
			anchors.bottomMargin: 14;
			anchors.right: cancelButton.left;
			anchors.rightMargin: 15;
			fixed_width: 103 ;
			fixed_height: 20;
			label_text: "ОК";
            label_color: Theme.color("light1");
			label_text_size: 14;
			label_text_family: fontBold.name;
			label_text_bold: true;         label_textAlignment: Text.AlignHCenter;
            highlight_color: Theme.color("green");
			frame_radius: 6;
			frame_width: 1;
			frame_enabled: true;
			onClicked: {
				FocusWindowBackend.accept();
				imageSource.zoom = 0;
				imageView.returnToBounds();
			}
		}

		Labels.FramedLabel
		{
			id: timeText;
			anchors.bottom: okButton.top;
			anchors.bottomMargin: 8;
			anchors.left: okButton.left;
			fixed_width: 174;
			fixed_height: 20;
			label_text: "ВРЕМЯ СИНТЕЗИРОВАНИЯ";
            label_color: Theme.color("light1");
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
			id: timeInput;
			fixed_width: 55;
			fixed_height: 22;
			anchors.verticalCenter: timeText.verticalCenter;
			anchors.left: timeText.right;
            label_color: Theme.color("light1");
			label_text_size: 14;
			label_text_family: fontExtraBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignRight;
            highlight_color: Theme.color("dark2");
			frame_radius: 5;
			frame_width: 0;
			frame_enabled: false;
            frame_color: Theme.color("dark1");
            selection_color: Theme.color("yellow");
			input_text: Number(FocusWindowBackend.time).toFixed(1);
			input_text_postfix: " с";
			onTxtChanged: {
				FocusWindowBackend.time = parseFloat(input_text);
			}
		}

		Flickable
		{
			id: imageView;
			anchors.right: parent.right;
			anchors.left: parent.left;
			anchors.top: headerText.bottom;
			anchors.bottom: timeText.top;
			anchors.margins: 10;

			boundsBehavior: Flickable.StopAtBounds
			clip: true;
			pixelAligned: true;
			interactive: true;
			contentWidth: imageBackground.width; //TODO
			contentHeight: imageBackground.height; //TODO
			flickDeceleration: 100000;

			Rectangle
			{
				id: imageBackground;
                width: imageSource.sourceSize.width * imageSource.scale;
                height: imageSource.sourceSize.height * imageSource.scale;
                color: Theme.color("dark1");
				anchors.centerIn: parent;

				Image {
					id: imageSource;
					anchors.fill: parent;
					smooth: true;
					source: "qrc:/icons/debug.png";
					visible: true;
					cache: false;
					anchors.centerIn: parent;
					fillMode: Image.PreserveAspectFit
					transformOrigin: Item.Center
					scale: Math.min(window.width / width, window.height / height, 1) + zoom

					property real zoom: 0.0;
					property real zoomStep: 0.1;

					MouseArea
					{
						id: mouseArea;
						anchors.fill: parent;
						hoverEnabled: true;
						propagateComposedEvents: true;
						acceptedButtons: Qt.RightButton;
						function adjustCoordinates()
						{
                            FocusWindowBackend.x = (mouseArea.mouseX / width) * FocusWindowBackend.lx * FocusWindowBackend.step + FocusWindowBackend.offset;
							FocusWindowBackend.y = ((mouseArea.mouseY / height) - 0.5) * FocusWindowBackend.ly * FocusWindowBackend.step;
						}
						onPositionChanged: adjustCoordinates();
						onWheel: {
							if (wheel.angleDelta.y > 0)
								imageSource.zoom = Number((imageSource.zoom + imageSource.zoomStep).toFixed(1))
							else
							{
								if (imageSource.zoom > 0) imageSource.zoom = Number((imageSource.zoom - imageSource.zoomStep).toFixed(1));
								imageView.returnToBounds();
							}

							mouseArea.hoverEnabled = true;
							//adjustCoordinates();
							wheel.accepted = true;
						}
						onClicked: hoverEnabled = !hoverEnabled;
						Rectangle { id: crosshair;
							width: (FocusWindowBackend.sideLength * FocusWindowBackend.step) * imageSource.width / FocusWindowBackend.lx;
							height: width;
							x: mouseArea.mouseX - width / 2;
							y: mouseArea.mouseY - height / 2;
							opacity: 1;
							color: "#00000000";
							border.width: 2;
                            border.color: Theme.color("light0");
							Image { id: pattern;
								anchors.fill: parent;
								source: "qrc:/map/patterns/diagonal.png";
								fillMode: Image.Tile;
								sourceSize.width: 64;
								sourceSize.height: 64;
							}
						}
					}
				}
			}
		}


		Labels.FramedLabel
		{
			id: filenameLabel;
			anchors.horizontalCenter: parent.horizontalCenter;
			anchors.bottom: imageView.bottom;
			anchors.bottomMargin: 6;
			fixed_width: 281;
			fixed_height: 12;
			label_text: "ИМЯ ФАЙЛА: " + FocusWindowBackend.filename;
            label_color: Theme.color("light1");
			label_text_size: 12;
			label_text_family: fontExtraBold.name;
			label_text_bold: true;
			label_textAlignment: Text.AlignHCenter;
			frame_radius: 2;
			frame_width: 0;
			label_wrapping: true;
		}
		property bool shownAlias: FocusWindowBackend.shown;
		onShownAliasChanged: {
			if(shownAlias)
			{
				imageSource.source = "";
				imageSource.source = "data:image/png;base64," + FocusWindowBackend.base64;
			}
		}
	}
}
