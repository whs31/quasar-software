import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import UX 1.0
import DynamicResolution 1.0

Item {
    property int tooltipPadding: 0;

    property string label_text: "Sample text";
    property color label_color: "#de3857";
    property int label_text_size: 12 * DynamicResolution.kh;
    property string label_text_family: "Helvetica [Cronyx]";
    property bool label_text_bold: false;
    property int frame_radius: 8 * DynamicResolution.kw;
    property int frame_width: 1;
    property int label_textAlignment: Text.AlignHCenter;

    Rectangle {
        id: tooltipBase;
        width: toolTipText.paintedWidth + tooltipPadding * DynamicResolution.kw;
        height: toolTipText.paintedHeight - 2 * DynamicResolution.kh;
        opacity: 1;
        color: UX.textWhite;
        radius: frame_radius;
        border.color: UX.textWhite;
        z: 99;

        Text {
            id: toolTipText;
            color: label_color;
            text: label_text;
            anchors.fill: parent;
            anchors.bottomMargin: 1 * DynamicResolution.kh;
            font.pixelSize: label_text_size;
            horizontalAlignment: label_textAlignment;
            verticalAlignment: Text.AlignVCenter;
            anchors.rightMargin: 5 * DynamicResolution.kw;
            anchors.leftMargin: 5 * DynamicResolution.kw;
            z: 100;
            font.bold: label_text_bold;
            font.family: label_text_family;
        }
    }
}
