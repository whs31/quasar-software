import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15 // LEGACY
import QtQuick.Layouts 1.15

import Theme 1.0
import Network 1.0

Pane {
    property string name: "Ping Console";

    Material.elevation: 60;
    Material.background: ColorTheme.active.color(ColorTheme.BaseShade)


    Rectangle { id: header;
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.margins: -12;
        color: ColorTheme.active.color(ColorTheme.Surface)
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
            color: ColorTheme.active.color(ColorTheme.Text)
        }
    }

    Rectangle { id: textareabackground;
        color: ColorTheme.active.color(ColorTheme.BaseShade)
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
                    text: "Радиолокационный модуль: "
                    color: ColorTheme.active.color(ColorTheme.Text)
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
                    color: Network.remoteData.de10ping === 0 ? ColorTheme.active.color(ColorTheme.Green)
                                                             : Network.remoteData.de10ping === 1
                                                             ? ColorTheme.active.color(ColorTheme.Yellow)
                                                             : ColorTheme.active.color(ColorTheme.Red)
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
                    text: "Бортовой вычислитель: "
                    color: ColorTheme.active.color(ColorTheme.Text)
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
                    color: Network.remoteData.jetsonping === 0 ? ColorTheme.active.color(ColorTheme.Green)
                                                             : Network.remoteData.de10ping === 1
                                                             ? ColorTheme.active.color(ColorTheme.Yellow)
                                                             : ColorTheme.active.color(ColorTheme.Red)
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
                    color: ColorTheme.active.color(ColorTheme.Text)
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
                    color: Network.remoteData.navping === 0 ? ColorTheme.active.color(ColorTheme.Green)
                                                             : Network.remoteData.de10ping === 1
                                                             ? ColorTheme.active.color(ColorTheme.Yellow)
                                                             : ColorTheme.active.color(ColorTheme.Red)
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
                    text: "Коммутатор антенн: "
                    color: ColorTheme.active.color(ColorTheme.Text)
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
                    color: Network.remoteData.utl1ping === 0 ? ColorTheme.active.color(ColorTheme.Green)
                                                             : Network.remoteData.de10ping === 1
                                                             ? ColorTheme.active.color(ColorTheme.Yellow)
                                                             : ColorTheme.active.color(ColorTheme.Red)
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
                    text: "Коммутатор питания: "
                    color: ColorTheme.active.color(ColorTheme.Text)
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
                    color: Network.remoteData.utl2ping === 0 ? ColorTheme.active.color(ColorTheme.Green)
                                                             : Network.remoteData.de10ping === 1
                                                             ? ColorTheme.active.color(ColorTheme.Yellow)
                                                             : ColorTheme.active.color(ColorTheme.Red)
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
