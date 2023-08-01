import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Qt5Compat.GraphicalEffects
import QtQuick.Layouts 1.15

import QuaSAR.API 1.0

import Theme 1.0

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
                    text: NetworkAPI.remote.pings[0] === Net.Success ? "СОЕДИНЕНИЕ ДОСТУПНО"
                                                                     : "НЕТ СОЕДИНЕНИЯ";
                    Component.onCompleted: console.error(NetworkAPI.remote.pings[0])
                    color: NetworkAPI.remote.pings[0] === Net.Success ? ColorTheme.active.color(ColorTheme.Green)
                                                                      : ColorTheme.active.color(ColorTheme.Red)
                }

                ConnectionIndicator {
                    connected: NetworkAPI.remote.pings[0] === Net.Success ? 2 : 0;
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
                    text: NetworkAPI.remote.pings[1] === Net.Success ? "СОЕДИНЕНИЕ ДОСТУПНО"
                                                                     : "НЕТ СОЕДИНЕНИЯ";
                    color: NetworkAPI.remote.pings[1] === Net.Success ? ColorTheme.active.color(ColorTheme.Green)
                                                                      : ColorTheme.active.color(ColorTheme.Red)
                }

                ConnectionIndicator {
                    connected: NetworkAPI.remote.pings[1] === Net.Success ? 2 : 0;
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
                    text: NetworkAPI.remote.pings[2] === Net.Success ? "СОЕДИНЕНИЕ ДОСТУПНО"
                                                                     : "НЕТ СОЕДИНЕНИЯ";
                    color: NetworkAPI.remote.pings[2] === Net.Success ? ColorTheme.active.color(ColorTheme.Green)
                                                                      : ColorTheme.active.color(ColorTheme.Red)
                }

                ConnectionIndicator {
                    connected: NetworkAPI.remote.pings[2] === Net.Success ? 2 : 0;
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
                    text: NetworkAPI.remote.pings[3] === Net.Success ? "СОЕДИНЕНИЕ ДОСТУПНО"
                                                                     : "НЕТ СОЕДИНЕНИЯ";
                    color: NetworkAPI.remote.pings[3] === Net.Success ? ColorTheme.active.color(ColorTheme.Green)
                                                                      : ColorTheme.active.color(ColorTheme.Red)
                }

                ConnectionIndicator {
                    connected: NetworkAPI.remote.pings[3] === Net.Success ? 2 : 0;
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
                    text: NetworkAPI.remote.pings[4] === Net.Success ? "СОЕДИНЕНИЕ ДОСТУПНО"
                                                                     : "НЕТ СОЕДИНЕНИЯ";
                    color: NetworkAPI.remote.pings[4] === Net.Success ? ColorTheme.active.color(ColorTheme.Green)
                                                                      : ColorTheme.active.color(ColorTheme.Red)
                }

                ConnectionIndicator {
                    connected: NetworkAPI.remote.pings[4] === Net.Success ? 2 : 0;
                    Layout.fillHeight: true;
                    Layout.margins: 5;
                }
            }
        }
    }
}
