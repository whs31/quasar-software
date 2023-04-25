import QtQuick 2.15
import QtQuick.Layouts 1.15
import Telemetry 1.0

Rectangle {
    property real latitude: Telemetry.latitude;
    property real longitude: Telemetry.longitude;
    property real altitude: Telemetry.altitude;
    property real velocity: Telemetry.velocity_horizontal;
    property real velocity_vertical: Telemetry.velocity_vertical;
    property real pitch: Telemetry.pitch;
    property real roll: Telemetry.roll;
    property real course: Telemetry.course;
    property string time: Telemetry.time;

    border.color: "#3b4252";
    border.width: 3;
    color: "#2e3440";
    radius: 6;

    Component.onCompleted: Telemetry.start(60, 30, 500, 10);

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
            color: "#ebcb8b";
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
            color: "#ebcb8b";
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
            color: "#8fbcbb";
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
            color: "#d08770";
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
            color: "#d08770";
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
            color: "#a3be8c";
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
            color: "#a3be8c";
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
            color: "#a3be8c";
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
            color: "#bf616a";
            font.family: root.s_FontMain;
            font.weight: Font.ExtraBold;
            font.pixelSize: 12;
            text: time;
        }
    }
}
