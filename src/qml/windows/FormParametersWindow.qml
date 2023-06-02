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
                text: "Режим формирования:  ";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
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
                text: "Смещение по времени, с: ";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
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
                text: "Яркость РЛИ:  ";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
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

            Text {
                text: "Начальная высота, м:  ";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            TextField { id: validator_3;
                property bool valid: /^[0-9]*$/.test(text);

                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                text: "120";
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                color: valid ? Theme.color("light1") : Theme.color("red");
                //onEditingFinished:
            }

            Text {
                text: "Высота БПЛА, м (ручной режим):  ";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            TextField { id: validator_4;
                property bool valid: /^[0-9-]*$/.test(text);

                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                text: "-";
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                color: valid ? Theme.color("light1") : Theme.color("red");
                //onEditingFinished:
            }

            Text {
                text: "Скорость БПЛА, м/с (ручной режим):  ";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            TextField { id: validator_5;
                property bool valid: /^[0-9.-]*$/.test(text);

                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                text: "-";
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                color: valid ? Theme.color("light1") : Theme.color("red");
                //onEditingFinished:
            }

            Text {
                text: "Оконная функция:";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            ComboBox {
                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                currentIndex: 0;
                model: [ "Хэмминг", "Блэкман" ];
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
//                onCurrentValueChanged: if(currentValue === "Слева") Config.antennaAlignment = 0;
            }

            Text {
                text: "Интерполяция:";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            TextField { id: validator_6;
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

            Text {
                text: "Время синтезирования, с:";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            TextField { id: validator_7;
                property bool valid: /^[0-9.]*$/.test(text);

                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                text: "10";
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                color: valid ? Theme.color("light1") : Theme.color("red");
                //onEditingFinished:
            }

            Text {
                text: "Время полосового синтезирования, с:";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            TextField { id: validator_8;
                property bool valid: /^[0-9.]*$/.test(text);

                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                text: "10";
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                color: valid ? Theme.color("light1") : Theme.color("red");
                //onEditingFinished:
            }

            Text {
                text: "Интерполяция по гор. дальности:  ";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            TextField { id: validator_9;
                property bool valid: /^[0-9]*$/.test(text);

                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                text: "1";
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                color: valid ? Theme.color("light1") : Theme.color("red");
                //onEditingFinished:
            }

            Text {
                text: "Интерполяция по путевой дальности:  ";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            TextField { id: validator_10;
                property bool valid: /^[0-9]*$/.test(text);

                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                text: "1";
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                color: valid ? Theme.color("light1") : Theme.color("red");
                //onEditingFinished:
            }

            Text {
                text: "Качество изображения:";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            Slider {
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                Layout.alignment: Qt.AlignRight;
                from: 1;
                to: 100;
                value: 95;
                //onValueChanged: transparency = value;
            }

            Text {
                text: "Шаг по дальности, м:  ";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            TextField { id: validator_11;
                property bool valid: /^[0-9.]*$/.test(text);

                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                text: "1";
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                color: valid ? Theme.color("light1") : Theme.color("red");
                //onEditingFinished:
            }

            Text {
                text: "Ближняя граница, м:  ";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            TextField { id: validator_12;
                property bool valid: /^[0-9]*$/.test(text);

                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                text: "100";
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                color: valid ? Theme.color("light1") : Theme.color("red");
                //onEditingFinished:
            }

            Text {
                text: "Смещение кадра, м:  ";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            TextField { id: validator_13;
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

            Text {
                text: "Размер РЛИ по горизонтали, м:  ";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            TextField { id: validator_14;
                property bool valid: /^[0-9]*$/.test(text);

                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                text: "2500";
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                color: valid ? Theme.color("light1") : Theme.color("red");
                //onEditingFinished:
            }

            Text {
                text: "Размер РЛИ по вертикали, м:  ";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            TextField { id: validator_15;
                property bool valid: /^[0-9]*$/.test(text);

                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                text: "800";
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                color: valid ? Theme.color("light1") : Theme.color("red");
                //onEditingFinished:
            }

            Text {
                text: "Время записи, с:  ";
                font.family: root.mainfont;
                color: Theme.color("light1");
                font.pixelSize: 14;
                Layout.alignment: Qt.AlignLeft;
            }

            TextField { id: validator_16;
                property bool valid: /^[0-9]*$/.test(text);

                font.family: root.mainfont;
                font.weight: Font.Bold;
                font.pixelSize: 14;
                text: "15";
                Layout.alignment: Qt.AlignRight;
                Layout.fillWidth: true;
                color: valid ? Theme.color("light1") : Theme.color("red");
                //onEditingFinished:
            }

//                {"remote_directory", execdargument_t("--ip", execd_string)},
//                {"im", execdargument_t("--im", execd_string)},
//                {"timeshift2", execdargument_t("--Tshift", execd_float)},
//                {"remote_address", execdargument_t("--remote", execd_string)},
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
