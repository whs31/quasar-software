import QtQuick 2.15
import DynamicResolution 1.0

Rectangle {
    property int fixed_width: 100 * DynamicResolution.kw;
    property int fixed_height: 25 * DynamicResolution.kh;

    property string label_text: "Sample text";
    property color label_color: "#de3857";
    property int label_text_size: 12 * DynamicResolution.kh;
    property string label_text_family: "Helvetica [Cronyx]";
    property bool label_text_bold: false;
    property int frame_radius: 8 * DynamicResolution.kw;
    property int frame_width: 1;
    property int label_textAlignment: Text.AlignHCenter;
	property bool label_wrapping: false;

    id: frame;
    color: "transparent";
    border.width: frame_width;
    border.color: label_color;
    radius: frame_radius;
    width: fixed_width;
    height: fixed_height;
    Text {
        text: label_text;
        font.capitalization: Font.MixedCase;
        font.pixelSize: label_text_size;
        font.family: label_text_family;
        font.bold: label_text_bold;
        color: label_color;
        opacity: enabled ? 1.0 : 0.3;
        verticalAlignment: Text.AlignVCenter;
        horizontalAlignment: label_textAlignment;
		lineHeight: label_wrapping ? 1 : 0.75;
        anchors.fill: parent;
		wrapMode: label_wrapping ? Text.WordWrap : Text.NoWrap;
    }
}
