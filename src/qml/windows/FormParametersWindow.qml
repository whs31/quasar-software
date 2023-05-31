import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Config 1.0

Window {
    property bool all_valid: validator_1.valid;

    Material.theme: Material.Dark;
    Material.accent: Theme.color("color1");
    Material.primary: Theme.color("accent");
    Material.foreground: Theme.color("light0");
    Material.background: Theme.color("dark1");

    width: 500;
    height: 700;

    color: Theme.color("dark1");
    modality: Qt.NonModal;
    title: "Параметры формирования";

    ScrollView { id: view;
        width: parent.width;
        height : parent.height;
        contentWidth: column.width;
        contentHeight: column.height;
        clip : true;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.topMargin: 20;
        anchors.bottom: buttonGroup.top;
        anchors.bottomMargin: 5;
        anchors.leftMargin: 10;
        anchors.rightMargin: 10;

        GridLayout { id: column;
            width: view.width;
            columns: 2;

            Text {
                text: "Режим формирования:";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
                Layout.fillWidth: true;
            }

            ComboBox {
                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                currentIndex: 0;
                model: [ "Телескопический М1", "Телескопический M2", "Телескопический M3", "Телескопический M4",
                         "Телескопический M5", "Телескопический M6", "Телескопический M7", "Полосовой режим" ];
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
//                onCurrentValueChanged: if(currentValue === "Слева") Config.antennaAlignment = 0;
            }

            Text {
                text: "Смещение по времени, с:";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
                Layout.fillWidth: true;
            }

            TextField { id: validator_1;
                property bool valid: /^[0-9.]*$/.test(text);

                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                text: "1.0";
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                color: valid ? Theme.color("light1") : Theme.color("red");
                //onEditingFinished:
            }

            Text {
                text: "Яркость РЛИ:";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
                Layout.fillWidth: true;
            }

            TextField { id: validator_2;
                property bool valid: /^[0-9]*$/.test(text);

                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                text: "0";
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                color: valid ? Theme.color("light1") : Theme.color("red");
                //onEditingFinished:
            }

//                {"timeshift", execdargument_t("-t", execd_float, 1, "Смещение по времени, с")},
//                {"brightness", execdargument_t("-b", execd_int, 0, "Яркость РЛИ")},
//                {"sea_level", execdargument_t("--e0", execd_int, 120, "Начальная высота в точке старта")},
//                {"altitude", execdargument_t("-e", execd_int, )},
//                {"velocity", execdargument_t("-v", execd_float)},
//                {"window_function", execdargument_t("-w", execd_string)},
//                {"interpolation", execdargument_t("-i", execd_int)},
//                {"synthesis_time", execdargument_t("--Ts", execd_float)},
//                {"strip_time", execdargument_t("--Tstrip", execd_float)},
//                {"frequency_interpolation_x", execdargument_t("--kR", execd_int)},
//                {"frequency_interpolation_y", execdargument_t("--kL", execd_int)},
//                {"jpeg_quality", execdargument_t("--jq", execd_int)},

//                {"dx", execdargument_t("--dx", execd_float)},
//                {"dy", execdargument_t("--dy", execd_float)},
//                {"x0", execdargument_t("--x0", execd_int)},
//                {"y0", execdargument_t("--y0", execd_int)},
//                {"lx", execdargument_t("--lx", execd_int)},
//                {"ly", execdargument_t("--ly", execd_int)},
//                {"remote_directory", execdargument_t("--ip", execd_string)},
//                {"im", execdargument_t("--im", execd_string)},
//                {"timeshift2", execdargument_t("--Tshift", execd_float)},
//                {"remote_address", execdargument_t("--remote", execd_string)},
//                {"record_duration", execdargument_t("--td", execd_int)},
        }
    }

    Row { id: buttonGroup;
        anchors.bottom: parent.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;

        RoundButton { id: button_OK;
            enabled: all_valid;
            width: 200;
            font.family: root.mainfont;
            font.weight: Font.Bold;
            height: 44;
            radius: 4;
            Material.elevation: 30;
            Material.background: Theme.color("dark1");
            text: "OK";
            onPressed: hide();
        }
    }
}
