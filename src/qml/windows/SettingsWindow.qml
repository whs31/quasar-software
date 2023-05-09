import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Config 1.0

/*
            {"remoteIP", "127.0.0.1"}, // network
            {"localIP", "127.0.0.1"},
            {"telemetryPort", "9955"},
            {"lfsPort", "10000"},
            {"stripPort", "48455"},
            {"execdPort", "9845"},
            {"feedbackPort", "9846"},
            {"telemetryFrequency", "0.1"},
            {"proxyEnabled", "false"},
            {"storedLatitude", "60"},  // map
            {"storedLongitude", "30"},
            {"storedZoomLevel", "6"},
            {"storedCatalogue", "C:/"},
            {"antennaAlignment", "false"}, // uav
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
                height: 500;
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
            }

            Pane { id: panel_Map;
                x: 25;
                height: 200;
                width: view.width - 50;
                Material.elevation: 50;

                Rectangle { id: header2;
                    anchors.top: parent.top;
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                    anchors.margins: -12;
                    color: Theme.color("dark2");
                    height: 24;

                    Text {
                        anchors.fill: parent;
                        anchors.leftMargin: 3;
                        text: "КАРТА";
                        font.family: root.mainfont;
                        color: Theme.color("light1");
                        font.bold: true;
                        font.pixelSize: 15;
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

                RowLayout {
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
                height: 250;
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
            }
        }
    }

    Row { id: buttonGroup;
        anchors.bottom: parent.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;

        RoundButton { id: button_Save;
            width: 200;
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
                hide();
            }
        }
    }
}
