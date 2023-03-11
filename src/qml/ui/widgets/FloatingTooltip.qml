import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import Theme 1.0

Item {
    property int tooltipPadding: 0;

    property string label_text: "Sample text";
    property color label_color: "#de3857";
    property int label_text_size: 12 * Theme.scalingFactor.y;
    property string label_text_family: "Helvetica [Cronyx]";
    property bool label_text_bold: false;
    property int frame_radius: 8 * Theme.scalingFactor.x;
    property int frame_width: 1;
    property int label_textAlignment: Text.AlignHCenter;

    Rectangle {
        id: tooltipBase;
        width: toolTipText.paintedWidth + tooltipPadding * Theme.scalingFactor.x;
        height: toolTipText.paintedHeight - 2 * Theme.scalingFactor.y;
        opacity: 1;
        color: Theme.color("light1");
        radius: frame_radius;
        border.color: Theme.color("light1");
        z: 99;

        Text {
            id: toolTipText;
            color: label_color;
            text: label_text;
            anchors.fill: parent;
            anchors.bottomMargin: 1 * Theme.scalingFactor.y;
            font.pixelSize: label_text_size;
            horizontalAlignment: label_textAlignment;
            verticalAlignment: Text.AlignVCenter;
            anchors.rightMargin: 5 * Theme.scalingFactor.x;
            anchors.leftMargin: 5 * Theme.scalingFactor.x;
            z: 100;
            font.bold: label_text_bold;
            font.family: label_text_family;
        }
    }
}
