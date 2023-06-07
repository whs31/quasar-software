import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15 // LEGACY
import QtQuick.Layouts 1.15

import Theme 1.0
import Network 1.0

Pane {
    property string name: "Ping Console";

    Material.elevation: 6;
    Material.background: Theme.color("dark1");


    Rectangle { id: header;
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.margins: -12;
        color: Theme.color("dark2");
        height: 24;

        Text {
            anchors.fill: parent;
            anchors.leftMargin: 3;
            font {
                family: root.mainfont
                bold: true
                pixelSize: 15
            }
            text: name;
            color: Theme.color("light1");
        }
    }

    Rectangle { id: textareabackground;
        color: Theme.color("dark1");
        anchors {
            top: header.bottom
            topMargin: 12
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        ColumnLayout {
            width: textareabackground.width;

            RowLayout {
                Layout.fillWidth: true;

                Text {
                    font {
                        family: root.mainfont
                        bold: true
                        pixelSize: 14
                    }
                    text: "DE10 Nano: "
                    color: Theme.color("light1");
                    Layout.fillWidth: true;
                }

                Text {
                    font {
                        family: root.mainfont
                        bold: true
                        pixelSize: 14
                    }
                    text: Network.remoteData.de10ping === 0 ? "СОЕДИНЕНИЕ ДОСТУПНО"
                                                            : "НЕТ СОЕДИНЕНИЯ";
                    color: Network.remoteData.de10ping === 0 ? Theme.color("green")
                                                             : Network.remoteData.de10ping === 1
                                                             ? Theme.color("yellow")
                                                             : Theme.color("red");
                }

                ConnectionIndicator {
                    connected: Network.remoteData.de10ping === 0 ? 2 : 0;
                    Layout.fillHeight: true;
                    Layout.margins: 5;
                }
            }

            RowLayout {
                Layout.fillWidth: true;

                Text {
                    font {
                        family: root.mainfont
                        bold: true
                        pixelSize: 14
                    }
                    text: "Jetson: "
                    color: Theme.color("light1");
                    Layout.fillWidth: true;
                }

                Text {
                    font {
                        family: root.mainfont
                        bold: true
                        pixelSize: 14
                    }
                    text: Network.remoteData.jetsonping === 0 ? "СОЕДИНЕНИЕ ДОСТУПНО"
                                                            : "НЕТ СОЕДИНЕНИЯ";
                    color: Network.remoteData.jetsonping === 0 ? Theme.color("green")
                                                             : Network.remoteData.de10ping === 1
                                                             ? Theme.color("yellow")
                                                             : Theme.color("red");
                }

                ConnectionIndicator {
                    connected: Network.remoteData.jetsonping === 0 ? 2 : 0;
                    Layout.fillHeight: true;
                    Layout.margins: 5;
                }
            }

            RowLayout {
                Layout.fillWidth: true;

                Text {
                    font {
                        family: root.mainfont
                        bold: true
                        pixelSize: 14
                    }
                    text: "Навигация: "
                    color: Theme.color("light1");
                    Layout.fillWidth: true;
                }

                Text {
                    font {
                        family: root.mainfont
                        bold: true
                        pixelSize: 14
                    }
                    text: Network.remoteData.navping === 0 ? "СОЕДИНЕНИЕ ДОСТУПНО"
                                                            : "НЕТ СОЕДИНЕНИЯ";
                    color: Network.remoteData.navping === 0 ? Theme.color("green")
                                                             : Network.remoteData.de10ping === 1
                                                             ? Theme.color("yellow")
                                                             : Theme.color("red");
                }

                ConnectionIndicator {
                    connected: Network.remoteData.navping === 0 ? 2 : 0;
                    Layout.fillHeight: true;
                    Layout.margins: 5;
                }
            }

            RowLayout {
                Layout.fillWidth: true;

                Text {
                    font {
                        family: root.mainfont
                        bold: true
                        pixelSize: 14
                    }
                    text: "RESERVED 1 {fix name}: "
                    color: Theme.color("light1");
                    Layout.fillWidth: true;
                }

                Text {
                    font {
                        family: root.mainfont
                        bold: true
                        pixelSize: 14
                    }
                    text: Network.remoteData.utl1ping === 0 ? "СОЕДИНЕНИЕ ДОСТУПНО"
                                                            : "НЕТ СОЕДИНЕНИЯ";
                    color: Network.remoteData.utl1ping === 0 ? Theme.color("green")
                                                             : Network.remoteData.de10ping === 1
                                                             ? Theme.color("yellow")
                                                             : Theme.color("red");
                }

                ConnectionIndicator {
                    connected: Network.remoteData.utl1ping === 0 ? 2 : 0;
                    Layout.fillHeight: true;
                    Layout.margins: 5;
                }
            }

            RowLayout {
                Layout.fillWidth: true;

                Text {
                    font {
                        family: root.mainfont
                        bold: true
                        pixelSize: 14
                    }
                    text: "RESERVED 2 {fix name}: "
                    color: Theme.color("light1");
                    Layout.fillWidth: true;
                }

                Text {
                    font {
                        family: root.mainfont
                        bold: true
                        pixelSize: 14
                    }
                    text: Network.remoteData.utl2ping === 0 ? "СОЕДИНЕНИЕ ДОСТУПНО"
                                                            : "НЕТ СОЕДИНЕНИЯ";
                    color: Network.remoteData.utl2ping === 0 ? Theme.color("green")
                                                             : Network.remoteData.de10ping === 1
                                                             ? Theme.color("yellow")
                                                             : Theme.color("red");
                }

                ConnectionIndicator {
                    connected: Network.remoteData.utl2ping === 0 ? 2 : 0;
                    Layout.fillHeight: true;
                    Layout.margins: 5;
                }
            }
        }
    }
}
