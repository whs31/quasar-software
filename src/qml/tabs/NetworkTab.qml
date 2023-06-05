import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import Network 1.0
import Config 1.0

import "network" as NetworkTab

Pane {
    Material.background: Theme.color("dark0");

    Flickable {
        anchors.fill: parent;
        clip: true;
        interactive: true;
        flickableDirection: Flickable.HorizontalAndVerticalFlick;
        contentHeight: 1000;
        contentWidth: 1896;

        NetworkTab.SocketConsole { id: panel_TelemetryConsole;
            anchors {
                left: parent.left;
                top: parent.top;
                margins: 5
            }
            name: "СОКЕТ ТЕЛЕМЕТРИИ";
            width: 720;
            height: 450;
            color: Theme.color("color3");
        }

        NetworkTab.SocketConsole { id: panel_ExecdConsole;
            anchors {
                left: panel_TelemetryConsole.right;
                top: parent.top;
                margins: 5
            }
            name: "СОКЕТ КОМАНД";
            width: 345;
            height: 450;
            color: Theme.color("accent");
        }

        NetworkTab.SocketConsole { id: panel_FeedbackConsole;
            anchors {
                left: panel_ExecdConsole.right;
                top: parent.top;
                margins: 5
            }
            name: "СОКЕТ ОБРАТНОЙ СВЯЗИ";
            width: 425;
            height: 450;
            color: Theme.color("yellow");
        }

        NetworkTab.SocketConsole { id: panel_LFSConsole;
            anchors {
                right: parent.right;
                top: parent.top;
                margins: 5
            }
            name: "СОКЕТ TCP-IP";
            width: 380;
            height: 450;
            color: Theme.color("green");
        }

        NetworkTab.SocketConsole { id: panel_StripConsole;
            anchors {
                left: parent.left;
                top: panel_TelemetryConsole.bottom;
                margins: 5
            }
            name: "СОКЕТ UDP LFS";
            width: 380;
            height: 450;
            color: Theme.color("color0");
        }
    }

    Pane { id: panel_Network;
        anchors {
            right: parent.right;
            bottom: parent.bottom;
            margins: 5
        }
        Material.elevation: 30;
        opacity: 0.85;

        Timer { id: disconnect_timer; running: false; repeat: false; interval: 3000; onTriggered: {
                if(!Network.connected)
                {
                    Network.stopExecdSocket();
                    Network.stopTelemetrySocket();
                    Network.stopTCPSocket();
                    Network.networkDelay = 100;
                }
            }
        }
        Column {
            RoundButton { id: button_Connect;
                font.family: root.mainfont;
                height: 40;
                radius: 4;
                icon.source: Network.connected ? "qrc:/icons/google-material/unlink.png"
                                               : "qrc:/icons/google-material/link.png";
                icon.color: Theme.color("light0");
                text: Network.connected ? "Отключиться от РЛС" : "Подключиться к РЛС";
                Material.elevation: 30;
                Material.background: Network.connected ? Theme.color("red") : Theme.color("dark2");
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
            }
        }
    }

    Connections {
        target: Network;
        function onTelemetrySocketMetrics(data, size_bytes, out) { panel_TelemetryConsole.logdata(data, size_bytes, out); }
        function onFeedbackSocketMetrics(data, size_bytes, out) { panel_FeedbackConsole.logdata(data, size_bytes, out); }
        function onExecdSocketMetrics(data, size_bytes, out) { panel_ExecdConsole.logdata(data, size_bytes, out); }
        function onLfsSocketMetrics(data, size_bytes, out) { panel_LFSConsole.logdata(data, size_bytes, out); }
    }
}
