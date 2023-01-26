import QtQuick 2.12
import QtQuick.Controls 2.12
import DynamicResolution 1.0

Rectangle {

    property bool frame_enabled: true;
    property int fixed_width: 100 * DynamicResolution.kw;
    property int fixed_height: 25 * DynamicResolution.kh;

    property string label_text: "Sample text";
    property color label_color: "#de3857";
    property int label_text_size: 12 * DynamicResolution.kh;
    property string label_text_family: "Helvetica [Cronyx]";
    property bool label_text_bold: false;
    property int label_textAlignment: Text.AlignHCenter;

    property color highlight_color: "#7D5233";
    property color selection_color: "#FF0000";
    property int frame_radius: 0 * DynamicResolution.kw;
    property int frame_width: 1;
    property string input_text: "sample";
    property string input_text_postfix: " gj";

    property real lower_bound: 0;
    property real upper_bound: 100;
    property int decimal_precision: 5;

    signal txtChanged();

    id: control;
    color: "transparent";
    radius: frame_radius;
    border.width: frame_width;
    border.color: frame_enabled ? label_color : "transparent";
    width: fixed_width;
    height: fixed_height;

    ColorAnimation {
            id: animation_hoverOn;
            target: control;
            property: "color";
            to: highlight_color;
            duration: 100;
        }
    ColorAnimation {
        id: animation_hoverOff;
        target: control;
        property: "color";
        to: "transparent";
        duration: 100;
    }
    Item {
        id: container;
        anchors.fill: parent;
        Text {
            id: label;
            text: label_text;
            font.capitalization: Font.MixedCase;
            font.pixelSize: label_text_size;
            font.family: label_text_family;
            font.bold: label_text_bold;
            color: label_color;
            opacity: enabled ? 1.0 : 0.3;
            verticalAlignment: Text.AlignVCenter;
            horizontalAlignment: label_textAlignment;
            anchors.right: input.left;
            anchors.leftMargin: 5 * DynamicResolution.kw;
            anchors.rightMargin: 5 * DynamicResolution.kw;
        }
        TextInput {
            id: input;
            anchors.right: postfix.left;
            text: input_text;
            color : label_color;
            opacity: enabled ? 1.0 : 0.3;
            font.capitalization: Font.MixedCase;
            font.pixelSize: label_text_size;
            font.family: label_text_family;
            font.bold: label_text_bold;
            maximumLength: 7;
            cursorVisible: false;
            readOnly: false;
            selectByMouse: true;
            selectedTextColor: highlight_color;
            selectionColor: selection_color;
            onTextEdited: input_text = text;
            validator: DoubleValidator { locale: "en_EN"; bottom: lower_bound; top: upper_bound; decimals: decimal_precision; }
        }
        Text {
            id: postfix;
            text: input_text_postfix;
            font.capitalization: Font.MixedCase;
            font.pixelSize: label_text_size;
            font.family: label_text_family;
            font.bold: label_text_bold;
            color: label_color;
            opacity: enabled ? 1.0 : 0.3;
            verticalAlignment: Text.AlignVCenter;
            horizontalAlignment: label_textAlignment;
            anchors.right: parent.right;
            anchors.rightMargin: 5 * DynamicResolution.kw;
        }
    }
    Component.onCompleted: {
        input.textEdited.connect(txtChanged);
    }
}
