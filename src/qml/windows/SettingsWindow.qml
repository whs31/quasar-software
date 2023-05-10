import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Config 1.0

/*
            {"angleCorrection", "0"}, // geopositioning
            {"useRadians", "false"},
            {"useDriftAngle", "true"},
            {"thetaAzimuthCorrection", "5"}
*/

Window {
    Material.theme: Material.Dark;
    Material.accent: Theme.color("color1");
    Material.primary: Theme.color("accent");
    Material.foreground: Theme.color("light0");
    Material.background: Theme.color("dark1");

    width: 700;
    height: 800;

    color: Theme.color("dark0");
    modality: Qt.NonModal;
    title: "Параметры";

    Text { id: text_Header;
        text: "НАСТРОЙКИ ПРОГРАММЫ";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        horizontalAlignment: Text.AlignHCenter;
        font.family: root.mainfont;
        color: Theme.color("light1");
        font.bold: true;
        font.pixelSize: 15;
    }

    ScrollView { id: view;
        property bool b_GlobalValid: validator_1.b_Valid && validator_2.b_Valid && validator_3.b_Valid && validator_4.b_Valid &&
                                     validator_5.b_Valid && validator_6.b_Valid && validator_7.b_Valid;

        width: parent.width;
        height : parent.height;
        contentWidth: column.width;
        contentHeight: column.height;
        clip : true;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: text_Header.bottom;
        anchors.topMargin: 15;
        anchors.bottom: buttonGroup.top;
        anchors.bottomMargin: 5;

        Column { id: column;
            width: parent.width;
            spacing: 30;

            Pane { id: panel_Network;
                x: 25;
                height: 490;
                Material.elevation: 50;
                width: view.width - 50;

                Rectangle { id: header1;
                    anchors.top: parent.top;
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                    anchors.margins: -12;
                    color: Theme.color("dark2");
                    height: 24;

                    Text {
                        anchors.fill: parent;
                        anchors.leftMargin: 3;
                        text: "СЕТЕВЫЕ ПОДКЛЮЧЕНИЯ";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.bold: true;
                        font.pixelSize: 15;
                    }
                }

                GridLayout {
                    columns: 2;
                    anchors.top: header1.bottom;
                    anchors.margins: 5;
                    anchors.left: parent.left;
                    anchors.right: parent.right;

                    Text {
                        text: "IP-адрес РЛС:";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.pixelSize: 14;
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField { id: validator_1;
                        property bool b_Valid: text.split(".").length === 4 && /^[0-9.]*$/.test(text);

                        font.family: root.mainfont;
                        font.weight: Font.Bold;
                        font.pixelSize: 14;
                        text: Config.remoteIP;
                        Layout.alignment: Qt.AlignRight;
                        color: b_Valid ? Theme.color("light1") : Theme.color("red");

                        onEditingFinished: Config.remoteIP = text;
                    }

                    Text {
                        text: "IP-адрес АРМ:";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.pixelSize: 14;
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField { id: validator_2;
                        property bool b_Valid: text.split(".").length === 4 && /^[0-9.]*$/.test(text);

                        font.family: root.mainfont;
                        font.weight: Font.Bold;
                        font.pixelSize: 14;
                        text: Config.localIP;
                        Layout.alignment: Qt.AlignRight;
                        color: b_Valid ? Theme.color("light1") : Theme.color("red");

                        onEditingFinished: Config.localIP = text;
                    }

                    Text {
                        text: "Порт сокета телеметрии:";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.pixelSize: 14;
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField { id: validator_3;
                        property bool b_Valid: /^[0-9]*$/.test(text);

                        font.family: root.mainfont;
                        font.weight: Font.Bold;
                        font.pixelSize: 14;
                        text: Config.telemetryPort;
                        Layout.alignment: Qt.AlignRight;
                        color: b_Valid ? Theme.color("light1") : Theme.color("red");

                        onEditingFinished: Config.telemetryPort = text;
                    }

                    Text {
                        text: "Порт сокета выполнения команд:";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.pixelSize: 14;
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField { id: validator_4;
                        property bool b_Valid: /^[0-9]*$/.test(text);

                        font.family: root.mainfont;
                        font.weight: Font.Bold;
                        font.pixelSize: 14;
                        text: Config.execdPort;
                        Layout.alignment: Qt.AlignRight;
                        color: b_Valid ? Theme.color("light1") : Theme.color("red");

                        onEditingFinished: Config.execdPort = text;
                    }

                    Text {
                        text: "Порт сокета обратной связи:";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.pixelSize: 14;
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField { id: validator_5;
                        property bool b_Valid: /^[0-9]*$/.test(text);

                        font.family: root.mainfont;
                        font.weight: Font.Bold;
                        font.pixelSize: 14;
                        text: Config.feedbackPort;
                        Layout.alignment: Qt.AlignRight;
                        color: b_Valid ? Theme.color("light1") : Theme.color("red");

                        onEditingFinished: Config.feedbackPort = text;
                    }

                    Text {
                        text: "Порт TCP-загрузчика:";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.pixelSize: 14;
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField { id: validator_6;
                        property bool b_Valid: /^[0-9]*$/.test(text);

                        font.family: root.mainfont;
                        font.weight: Font.Bold;
                        font.pixelSize: 14;
                        text: Config.tcpLFSPort;
                        Layout.alignment: Qt.AlignRight;
                        color: b_Valid ? Theme.color("light1") : Theme.color("red");

                        onEditingFinished: Config.tcpLFSPort = text;
                    }

                    Text {
                        text: "Порт UDP-загрузчика:";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.pixelSize: 14;
                        Layout.alignment: Qt.AlignLeft;
                    }

                    TextField { id: validator_7;
                        property bool b_Valid: /^[0-9]*$/.test(text);

                        font.family: root.mainfont;
                        font.weight: Font.Bold;
                        font.pixelSize: 14;
                        text: Config.udpLFSPort;
                        Layout.alignment: Qt.AlignRight;
                        color: b_Valid ? Theme.color("light1") : Theme.color("red");

                        onEditingFinished: Config.udpLFSPort = text;
                    }

                    Text {
                        text: "Частота запроса телеметрии:";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.pixelSize: 14;
                        Layout.alignment: Qt.AlignLeft;
                    }

                    SpinBox { id: sb_1;
                        Layout.alignment: Qt.AlignRight;
                        font.family: root.mainfont;
                        font.pixelSize: 14;
                        font.bold: true;
                        from: 0;
                        to: 2 * 1000;
                        stepSize: 10;
                        value: 0;
                        property real fl_ValueReal: value / 1000;
                        onValueChanged: Config.telemetryFrequency = fl_ValueReal;
                        validator: DoubleValidator {
                            bottom: Math.min(sb_1.from, sb_1.to);
                            top:  Math.max(sb_1.from, sb_1.to);
                        }
                        textFromValue: function(value, locale) { return Number(value / 1000).toLocaleString(locale, 'f', 2) + " с"; }
                        valueFromText: function(text, locale) {
                            return Number.fromLocaleString(locale, text) * 1000
                        }

                        Component.onCompleted: value = Config.telemetryFrequency;
                    }

                    CheckBox {
                        checked: Config.proxyEnabled;
                        text: "Использовать прокси";
                        font.family: root.mainfont;
                        font.pixelSize: 14;
                        onCheckedChanged: Config.proxyEnabled = checked;
                    }
                }
            }

            Pane { id: panel_UAV;
                x: 25;
                Material.elevation: 50;
                width: view.width - 50;
                height: 80;

                Rectangle { id: header3;
                    anchors.top: parent.top;
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                    anchors.margins: -12;
                    color: Theme.color("dark2");
                    height: 24;

                    Text {
                        anchors.fill: parent;
                        anchors.leftMargin: 3;
                        text: "ПАРАМЕТРЫ НОСИТЕЛЯ";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.bold: true;
                        font.pixelSize: 15;
                    }
                }

                GridLayout {
                    columns: 2;
                    anchors.top: header3.bottom;
                    anchors.margins: 5;
                    anchors.left: parent.left;
                    anchors.right: parent.right;

                    Text {
                        text: "Положение антенны:";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.pixelSize: 14;
                        Layout.alignment: Qt.AlignLeft;
                    }

                    ComboBox { id: control_AntennaPosition;
                        font.family: root.mainfont;
                        font.weight: Font.Bold;
                        font.pixelSize: 14;
                        width: 250;
                        currentIndex: Config.antennaAlignment ? 1 : 0;
                        model: [ "Слева", "Справа" ];
                        Layout.alignment: Qt.AlignRight;

                        onCurrentValueChanged: {
                            if(currentValue === "Слева")
                                Config.antennaAlignment = 0;
                            else
                                Config.antennaAlignment = 1;
                        }
                    }
                }
            }

            Pane { id: panel_Geopositioning;
                x: 25;
                height: 180;
                Material.elevation: 50;
                width: view.width - 50;

                Rectangle { id: header4;
                    anchors.top: parent.top;
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                    anchors.margins: -12;
                    color: Theme.color("dark2");
                    height: 24;

                    Text {
                        anchors.fill: parent;
                        anchors.leftMargin: 3;
                        text: "ПАРАМЕТРЫ ГЕОПРИВЯЗКИ";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.bold: true;
                        font.pixelSize: 15;
                    }
                }

                GridLayout {
                    columns: 2;
                    anchors.top: header4.bottom;
                    anchors.margins: 5;
                    anchors.left: parent.left;
                    anchors.right: parent.right;

                    Text {
                        text: "Общая коррекция угла:";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.pixelSize: 14;
                        Layout.alignment: Qt.AlignLeft;
                    }

                    SpinBox {
                        Layout.alignment: Qt.AlignRight;
                        font.family: root.mainfont;
                        font.pixelSize: 14;
                        font.bold: true;
                        from: -180;
                        to: 180;
                        value: Config.angleCorrection;
                        onValueChanged: Config.angleCorrection = value;
                        textFromValue: function(value, locale) { return Number(value).toLocaleString(locale, 'f', 0) + "°"; }
                    }

                    Text {
                        text: "Коррекция тета-азимута:";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.pixelSize: 14;
                        Layout.alignment: Qt.AlignLeft;
                    }

                    SpinBox {
                        Layout.alignment: Qt.AlignRight;
                        font.family: root.mainfont;
                        font.bold: true;
                        font.pixelSize: 14;
                        from: 0;
                        to: 30;
                        value: Config.thetaAzimuthCorrection;
                        onValueChanged: Config.thetaAzimuthCorrection = value;
                        textFromValue: function(value, locale) { return Number(value).toLocaleString(locale, 'f', 0) + "°"; }
                    }

                    CheckBox {
                        checked: Config.useRadians;
                        text: "Телеметрия в радианах";
                        font.family: root.mainfont;
                        font.pixelSize: 14;
                        onCheckedChanged: Config.useRadians = checked;
                    }

                    CheckBox {
                        checked: Config.useDriftAngle;
                        text: "Учитывать угол сноса";
                        font.family: root.mainfont;
                        font.pixelSize: 14;
                        onCheckedChanged: Config.useDriftAngle = checked;
                    }
                }
            }
        }
    }

    Row { id: buttonGroup;
        anchors.bottom: parent.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;

        RoundButton { id: button_Save;
            width: 200;
            enabled: view.b_GlobalValid;
            font.family: root.s_FontMain;
            font.weight: Font.Bold;
            height: 44;
            radius: 4;
            Material.elevation: 30;
            Material.background: Theme.color("dark1");
            text: "Применить";
            onPressed: {
                Config.save();
                hide();
            }
        }

        RoundButton { id: button_Cancel;
            width: 200;
            font.family: root.s_FontMain;
            font.weight: Font.Bold;
            height: 44;
            radius: 4;
            Material.elevation: 30;
            Material.background: Theme.color("dark1");
            text: "Отмена";
            onPressed: {
                Config.revert();
                sb_1.value = Config.telemetryFrequency;
                hide();
            }
        }
    }
}
