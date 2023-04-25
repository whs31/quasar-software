import QtQuick 2.15
import QtQuick.Layouts 1.15

Rectangle {
    property real latitude: 0.0;
    property real longitude: 0.0;
    property real altitude: 0.0;
    property real velocity: 0.0;
    property real velocity_vertical: 0.0;
    property real pitch: 0.0;
    property real roll: 0.0;
    property real course: 0.0;
    property string time: "--";

    border.color: "#3b4252";
    border.width: 3;
    color: "#2e3440";
    radius: 6;

    GridLayout {
        anchors.fill: parent;
        anchors.margins: 6;
        columns: 2;

        Text {
            Layout.alignment: Qt.AlignTop;
            color: "#d8dee9";
            font.family: root.s_FontMain;
            font.weight: Font.Bold;
            font.pixelSize: 12;
            text: "ШИРОТА";
        }
        Text {
            Layout.alignment: Qt.AlignTop;
            horizontalAlignment: Text.AlignRight;
            Layout.fillWidth: true;
            color: "#5e81ac";
            font.family: root.s_FontMain;
            font.weight: Font.ExtraBold;
            font.pixelSize: 12;
            text: Number(latitude).toFixed(8) + "° N";
        }

        Text {
            Layout.alignment: Qt.AlignTop;
            color: "#d8dee9";
            font.family: root.s_FontMain;
            font.weight: Font.Bold;
            font.pixelSize: 12;
            text: "ДОЛГОТА";
        }
        Text {
            Layout.alignment: Qt.AlignTop;
            horizontalAlignment: Text.AlignRight;
            Layout.fillWidth: true;
            color: "#5e81ac";
            font.family: root.s_FontMain;
            font.weight: Font.ExtraBold;
            font.pixelSize: 12;
            text: Number(longitude).toFixed(8) + "° E";
        }

        Text {
            Layout.alignment: Qt.AlignTop;
            color: "#d8dee9";
            font.family: root.s_FontMain;
            font.weight: Font.Bold;
            font.pixelSize: 12;
            text: "ВЫСОТА";
        }
        Text {
            Layout.alignment: Qt.AlignTop;
            horizontalAlignment: Text.AlignRight;
            Layout.fillWidth: true;
            color: "#5e81ac";
            font.family: root.s_FontMain;
            font.weight: Font.ExtraBold;
            font.pixelSize: 12;
            text: Number(altitude).toFixed(1) + " м";
        }

        Text {
            Layout.alignment: Qt.AlignTop;
            color: "#d8dee9";
            font.family: root.s_FontMain;
            font.weight: Font.Bold;
            font.pixelSize: 12;
            text: "ГОРИЗОНТАЛЬНАЯ СКОРОСТЬ";
        }

        Text {
            Layout.alignment: Qt.AlignTop;
            horizontalAlignment: Text.AlignRight;
            Layout.fillWidth: true;
            color: "#5e81ac";
            font.family: root.s_FontMain;
            font.weight: Font.ExtraBold;
            font.pixelSize: 12;
            text: Number(velocity).toFixed(2) + " м/с";
        }

        Text {
            Layout.alignment: Qt.AlignTop;
            color: "#d8dee9";
            font.family: root.s_FontMain;
            font.weight: Font.Bold;
            font.pixelSize: 12;
            text: "ВЕРТИКАЛЬНАЯ СКОРОСТЬ";
        }

        Text {
            Layout.alignment: Qt.AlignTop;
            horizontalAlignment: Text.AlignRight;
            Layout.fillWidth: true;
            color: "#5e81ac";
            font.family: root.s_FontMain;
            font.weight: Font.ExtraBold;
            font.pixelSize: 12;
            text: Number(velocity_vertical).toFixed(2) + " м/с";
        }

        Text {
            Layout.alignment: Qt.AlignTop;
            color: "#d8dee9";
            font.family: root.s_FontMain;
            font.weight: Font.Bold;
            font.pixelSize: 12;
            text: "ТАНГАЖ";
        }

        Text {
            Layout.alignment: Qt.AlignTop;
            horizontalAlignment: Text.AlignRight;
            Layout.fillWidth: true;
            color: "#5e81ac";
            font.family: root.s_FontMain;
            font.weight: Font.ExtraBold;
            font.pixelSize: 12;
            text: Number(pitch).toFixed(1) + "°";
        }

        Text {
            Layout.alignment: Qt.AlignTop;
            color: "#d8dee9";
            font.family: root.s_FontMain;
            font.weight: Font.Bold;
            font.pixelSize: 12;
            text: "КРЕН";
        }

        Text {
            Layout.alignment: Qt.AlignTop;
            horizontalAlignment: Text.AlignRight;
            Layout.fillWidth: true;
            color: "#5e81ac";
            font.family: root.s_FontMain;
            font.weight: Font.ExtraBold;
            font.pixelSize: 12;
            text: Number(roll).toFixed(1) + "°";
        }

        Text {
            Layout.alignment: Qt.AlignTop;
            color: "#d8dee9";
            font.family: root.s_FontMain;
            font.weight: Font.Bold;
            font.pixelSize: 12;
            text: "КУРС";
        }

        Text {
            Layout.alignment: Qt.AlignTop;
            horizontalAlignment: Text.AlignRight;
            Layout.fillWidth: true;
            color: "#5e81ac";
            font.family: root.s_FontMain;
            font.weight: Font.ExtraBold;
            font.pixelSize: 12;
            text: Number(course).toFixed(1) + "°";
        }

        Text {
            Layout.alignment: Qt.AlignTop;
            color: "#d8dee9";
            font.family: root.s_FontMain;
            font.weight: Font.Bold;
            font.pixelSize: 12;
            text: "ВРЕМЯ НА БОРТУ";
        }

        Text {
            Layout.alignment: Qt.AlignTop;
            horizontalAlignment: Text.AlignRight;
            Layout.fillWidth: true;
            color: "#5e81ac";
            font.family: root.s_FontMain;
            font.weight: Font.ExtraBold;
            font.pixelSize: 12;
            text: time;
        }
    }
}
