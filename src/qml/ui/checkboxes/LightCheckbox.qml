import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    property int fixed_width: 100;
    property int fixed_height: 25;

    property string label_text: "Sample text";
    property color label_color: "#de3857";
    property int label_text_size: 12;
    property string label_text_family: "Helvetica [Cronyx]";
    property bool label_text_bold: false;
    property int label_textAlignment: Text.AlignHCenter;

    property color contrast_color: "#00FFFF";
    property color highlight_color: "#7D5233";

    property bool checked: false;

    width: fixed_width;
    height: fixed_height;

    id: control;

    Rectangle {
        id: checkboxIndicator;
        color: label_color;
        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.rightMargin: 3;
        implicitWidth: 16;
        implicitHeight: 16;
        radius: 4;
        Rectangle {
            color: contrast_color;
            visible: control.checked;
            width: parent.width / 1.5;
            height: parent.height / 1.5;
            anchors.centerIn: parent;
            radius: 4;
        }
        SequentialAnimation {
            id: animation_scalebounce;
            PropertyAnimation {
                target: checkboxIndicator
                property: "scale"
                to: 1.2
                duration: 100;
                easing.type: Easing.InOutQuad
            }
            PropertyAnimation {
                target: checkboxIndicator
                property: "scale"
                to: 1.0
                duration: 100;
                easing.type: Easing.InOutQuad
            }
        }
        SequentialAnimation {
            id: animation_colorfadeinout;
            ColorAnimation {
                target: checkboxIndicator;
                property: "color";
                to: highlight_color;
                duration: 100;
            }
            ColorAnimation {
                target: checkboxIndicator;
                property: "color";
                to: label_color;
                duration: 100;
            }
        }
    }

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
        anchors.right: checkboxIndicator.left;
        anchors.rightMargin: 7;
        anchors.verticalCenter: parent.verticalCenter;
        width: fixed_width - 10 - checkboxIndicator.width;
    }

    MouseArea {
        id: controlMouseArea;
        hoverEnabled: true;
        anchors.fill: parent
        onEntered: { checkboxIndicator.color = Qt.lighter(label_color, 1.5); }
        onExited: { checkboxIndicator.color = label_color; }
        onClicked: { checked = !checked; animation_scalebounce.start(); animation_colorfadeinout.start(); forceActiveFocus(); }
    }
}
