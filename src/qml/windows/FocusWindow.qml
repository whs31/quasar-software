import QtQuick 2.15
import UX 1.0
import RuntimeData 1.0
import Config 1.0
import DynamicResolution 1.0
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
    color: UX.primaryDark;

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
            anchors.horizontalCenter: parent.horizontalCenter;
            fixed_width: 282;
            fixed_height: 13;
            label_text: "ФОКУСИРОВКА ИЗОБРАЖЕНИЯ";
            label_color: UX.textWhite;
            label_text_size: 17;
            label_text_family: fontExtraBold.name;
            label_text_bold: true;
            label_textAlignment: Text.AlignHCenter;
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
            frame_color: UX.textWhite;
            highlight_color: UX.accentLight;
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
            fill_color: UX.textWhite;
            highlight_color: UX.textWhite;
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
            frame_color: UX.textWhite;
            highlight_color: UX.accentLight;
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
            label_color: UX.textWhite;
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
            label_color: UX.textWhite;
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
            label_color: UX.textWhite;
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
            label_color: UX.textWhite;
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
            label_color: UX.textWhite;
            label_text_size: 14;
            label_text_family: fontBold.name;
            label_text_bold: true;         label_textAlignment: Text.AlignHCenter;
            highlight_color: UX.errorDark;
            frame_radius: 6;
            frame_width: 1;
            frame_enabled: true;
            onClicked: {
                FocusWindowBackend.cancel();
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
            label_color: UX.textWhite;
            label_text_size: 14;
            label_text_family: fontBold.name;
            label_text_bold: true;         label_textAlignment: Text.AlignHCenter;
            highlight_color: UX.successLighter;
            frame_radius: 6;
            frame_width: 1;
            frame_enabled: true;
            onClicked: {
                FocusWindowBackend.accept();
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
            id: timeInput;
            fixed_width: 55;
            fixed_height: 22;
            anchors.verticalCenter: timeText.verticalCenter;
            anchors.left: timeText.right;
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
            input_text: Number(FocusWindowBackend.time).toFixed(1);
            input_text_postfix: " с";
            onTxtChanged: {
                FocusWindowBackend.time = parseFloat(input_text);
            }
        }

        WheelHandler { id: wheelHandler;
            property real maxZoom: 100;
            property real zoom: 1;
            readonly property real zoom_sensivity: 3;
        }

        Flickable
        {
            id: imageView;
            width: 752;
            height: 280;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: parent.top;
            anchors.topMargin: 33;
            boundsMovement: Flickable.StopAtBounds
            clip: true;
            pixelAligned: true;
            contentWidth: imageView.width; //TODO
            contentHeight: imageView.height; //TODO

            Rectangle
            {
                id: imageBackground;
                width: 752 * wheelHandler.zoom;
                height: 280 * wheelHandler.zoom;
                radius: 15;
                color: UX.primaryDarkest;
                Image {
                    id: imageSource;
                    anchors.fill: parent;
                    smooth: true;
                    source: "qrc:/icons/debug.png";
                    visible: true;
                    cache: false;
                }
                MouseArea
                {
                    id: mouseArea;
                    anchors.fill: parent;
                    hoverEnabled: true;
                    propagateComposedEvents: true;
                    onPositionChanged:
                    {
                        FocusWindowBackend.x = (mouseX / width) * FocusWindowBackend.lx * FocusWindowBackend.step + FocusWindowBackend.offset;
                        FocusWindowBackend.y = ((mouseY / height) - 0.5) * FocusWindowBackend.ly * FocusWindowBackend.step;
                        mouseCross.requestPaint();
                    }
                    onClicked: hoverEnabled = !hoverEnabled;
                    Canvas
                    {
                        id: mouseCross;
                        anchors.fill: parent;
                        onPaint:
                        {
                            // ❮❮❮ Mouse cross ❯❯❯
                            let ctx = getContext('2d');

                            ctx.clearRect(0, 0, width, height);
                            ctx.beginPath();
                            ctx.strokeStyle = UX.textFaded;
                            ctx.fillStyle = UX.textFaded;
                            ctx.lineWidth = 1.5;
                            ctx.globalAlpha = 0.7;
                            ctx.moveTo(mouseArea.mouseX, 0);
                            ctx.lineTo(mouseArea.mouseX, height);
                            ctx.moveTo(0, mouseArea.mouseY);
                            ctx.lineTo(width, mouseArea.mouseY);
                            let kx = width / FocusWindowBackend.lx;
                            let ky = height / FocusWindowBackend.ly;
                            ctx.moveTo(mouseArea.mouseX - (FocusWindowBackend.sideLength * FocusWindowBackend.step) * kx, mouseArea.mouseY - (FocusWindowBackend.sideLength * FocusWindowBackend.step) * ky);
                            ctx.lineTo(mouseArea.mouseX + (FocusWindowBackend.sideLength * FocusWindowBackend.step) * kx, mouseArea.mouseY - (FocusWindowBackend.sideLength * FocusWindowBackend.step) * ky);
                            ctx.lineTo(mouseArea.mouseX + (FocusWindowBackend.sideLength * FocusWindowBackend.step) * kx, mouseArea.mouseY + (FocusWindowBackend.sideLength * FocusWindowBackend.step) * ky);
                            ctx.lineTo(mouseArea.mouseX - (FocusWindowBackend.sideLength * FocusWindowBackend.step) * kx, mouseArea.mouseY + (FocusWindowBackend.sideLength * FocusWindowBackend.step) * ky);
                            ctx.lineTo(mouseArea.mouseX - (FocusWindowBackend.sideLength * FocusWindowBackend.step) * kx, mouseArea.mouseY - (FocusWindowBackend.sideLength * FocusWindowBackend.step) * ky);
                            ctx.stroke();
                            ctx.fill();
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
            label_color: UX.textWhite;
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
