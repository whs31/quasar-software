import QtQuick 2.15
import Theme 1.0

Rectangle {
    property int fixed_width: 100 * Theme.scalingFactor.x;
    property int fixed_height: 25 * Theme.scalingFactor.y;

    property string label_text: "Sample text";
    property color label_color: "#de3857";
    property color round_color: "#FDFDFD";
    property int label_text_size: 12 * Theme.scalingFactor.y;
    property string label_text_family: "Helvetica [Cronyx]";
    property bool label_text_bold: false;
    property int round_radius: 8 * Theme.scalingFactor.x;
    property int label_textAlignment: Text.AlignHCenter;

    id: frame;
    color: round_color;
    radius: round_radius;
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
        anchors.fill: parent;
    }
}
