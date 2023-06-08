import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Network 1.0
import Config 1.0

Pane {
    property int mode: control_FormModeCombo.currentIndex; // 0 = telescopic, 1 = strip

    Material.elevation: 30;
    Behavior on implicitWidth { NumberAnimation { easing.type: Easing.InOutQuad; duration: 200; } }

    ColumnLayout {
        RowLayout {
            Layout.fillWidth: true;

            RoundButton { id: button_FormImage;
                Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }
                font.family: root.mainfont;
                height: 40;
                radius: 4;
                icon.source: "qrc:/icons/google-material/take-photo.png";
                icon.color: Theme.color("dark0");
                text: mode === 0 ? "Формирование изображения"
                                 : checked
                                 ? "Остановка записи"
                                 : "Начало записи";
                checkable: mode === 1;
                Material.elevation: 30;
                Material.foreground: Theme.color("dark0");
                Material.background: mode === 0 ? Theme.color("accent")
                                                : checked
                                                ? Theme.color("orange")
                                                : Theme.color("color0");
                onPressed: {
                    if(!checkable)
                        Network.executeCommand(Network.FormImage);
                }

                onCheckedChanged: {
                    if(checked)
                        console.error("Starting strip form... (not implemented)");
                    else
                        console.error("Stopping strip form... (not implemented)");
                }
            }

            RoundButton { id: button_Connect;
                Layout.fillWidth: true;
                font.family: root.mainfont;
                height: 40;
                radius: 4;
                icon.source: Network.connected ? "qrc:/icons/google-material/unlink.png"
                                               : "qrc:/icons/google-material/link.png";
                icon.color: Theme.color("dark0");
                text: Network.connected ? "Отключиться от РЛС" : "Подключиться к РЛС";
                Material.elevation: 30;
                Material.foreground: Theme.color("dark0");
                Material.background: Network.connected ? Theme.color("red") : Theme.color("color3");
                onPressed: {
                    if(Network.connected)
                    {
                        Network.stopExecdSocket();
                        Network.stopTelemetrySocket();
                        Network.stopTCPSocket();
                        Network.networkDelay = 100;
                    }
                    else
                    {
                        Network.startExecdSocket(Config.remoteIP + ":" + Config.execdPort,
                                                 Config.localIP + ":" + Config.feedbackPort);
                        Network.startTelemetrySocket(Config.remoteIP + ":" + Config.telemetryPort,
                                                     Config.telemetryFrequency);
                        Network.startTCPSocket(Config.localIP + ":" + Config.tcpLFSPort);
                        Network.executeCommand(Network.Ping);
                        Network.executeCommand(Network.RemoteStorageStatus);
                        disconnect_timer.start();
                    }
                }

                Timer { id: disconnect_timer; running: false; repeat: false; interval: 10000; onTriggered: {
                        if(!Network.connected)
                        {
                            Network.stopExecdSocket();
                            Network.stopTelemetrySocket();
                            Network.stopTCPSocket();
                            Network.networkDelay = 100;
                        }
                    }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true;

            ComboBox { id: control_FormModeCombo;
                font {
                    family: root.mainfont;
                    pixelSize: 14;
                    weight: Font.Bold;
                }

                implicitWidth: 250;
                currentIndex: 0;
                model: ["Телескопический режим", "Полосовой режим", ];
            }

            ComboBox {
                font {
                    family: root.mainfont;
                    pixelSize: 14;
                    weight: Font.Bold;
                }

                currentIndex: 0;
                model: [ "М1", "М2", "М3", "М4",
                    "М6", "М7", ];
                onCurrentValueChanged: {
                    let val = (currentIndex + 1);
                    if(val === 6)
                        val = 7;
                    if(val === 5)
                        val = 6;
                    Network.setArgument("-m", val, Network.Form);
                }
            }

            RoundButton { id: button_Calibrate;
                font.family: root.mainfont;
                height: 40;
                radius: 4;
                icon.source: "qrc:/icons/google-material/water.png"
                icon.color: Theme.color("light0");
                Material.elevation: 30;
                Material.foreground: Theme.color("light0");
                Material.background: Theme.color("dark2");
                onPressed: dialogwindow.open("Калибровка высоты", "Выполнить калибровку высоты? Убедитесь, что БПЛА находится на земле.", "info", 17);

                Connections {
                    target: dialogwindow;
                    function onClosed(status, uid) {
                        if(uid === 17 && status === true) {
                            console.log("[GUI] Calibrating altitude");
                            Network.telemetry.seaLevel = Network.telemetry.altitude;
                        }
                    }
                }

                ToolTip { id: tt1; visible: parent.hovered; font { family: root.mainfont; pixelSize: 13; }
                          contentItem: Text { text: tt1.text; font: tt1.font;  color: Theme.color("dark0"); }
                          background: Rectangle { color: Theme.color("light1"); radius: 3; } delay: 500;
                          text: "Выполнить калибровку высоты над уровнем моря"; }
            }

            RoundButton { id: button_Ping;
                font.family: root.mainfont;
                height: 40;
                radius: 4;
                icon.source: "qrc:/icons/google-material/storage.png"
                icon.color: Theme.color("light0");
                Material.elevation: 30;
                Material.foreground: Theme.color("light0");
                Material.background: Theme.color("dark2");
                onPressed: {
                    Network.executeCommand(Network.Ping);
                    Network.executeCommand(Network.RemoteStorageStatus);
                }

                ToolTip { id: tt2; visible: parent.hovered; font { family: root.mainfont; pixelSize: 13; }
                          contentItem: Text { text: tt2.text; font: tt2.font;  color: Theme.color("dark0"); }
                          background: Rectangle { color: Theme.color("light1"); radius: 3; } delay: 500;
                          text: "Проверить соединение и состояние хранилища на РЛС"; }
            }

            RoundButton { id: button_ClearDisk;
                font.family: root.mainfont;
                height: 40;
                radius: 4;
                icon.source: "qrc:/icons/google-material/delete.png"
                icon.color: Theme.color("dark0");
                Material.elevation: 30;
                Material.foreground: Theme.color("dark0");
                Material.background: Theme.color("red");
                onPressed: dialogwindow.open("Очистка удаленного диска", "Вы уверены, что хотите очистить удаленное хранилище на РЛС?", "error", 27);

                Connections {
                    target: dialogwindow;
                    function onClosed(status, uid) {
                        if(uid === 27 && status === true) {
                            console.log("[GUI] Clearing remote storage");
                            Network.executeCommand(Network.ClearRemoteStorage);
                        }
                    }
                }

                ToolTip { id: tt3; visible: parent.hovered; font { family: root.mainfont; pixelSize: 13; }
                          contentItem: Text { text: tt3.text; font: tt3.font;  color: Theme.color("dark0"); }
                          background: Rectangle { color: Theme.color("light1"); radius: 3; } delay: 500;
                          text: "Очистить хранилище на РЛС"; }
            }
        }
    }
}

