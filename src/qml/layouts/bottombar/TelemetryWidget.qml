import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Network 1.0
import "../../widgets" as Widgets

Item {
    property real fl_Latitude: Network.telemetry.latitude
    property real fl_Longitude: Network.telemetry.longitude
    property real fl_Altitude: Network.telemetry.altitude - Network.telemetry.seaLevel
    property real fl_SeaAltitude: Network.telemetry.altitude
    property real fl_Velocity: Network.telemetry.velocityCourse
    property real fl_Direction: Network.telemetry.course
    property int i_SatellitesCount: Network.telemetry.satellites
    property real fl_ConnectionDelay: Network.networkDelay
    property real fl_RemoteDiskSpace: Network.remoteData.storageSpace

    RowLayout {
        spacing: 8

        GridLayout {
            columns: 2
            Layout.preferredWidth: 170
            Layout.fillHeight: true

            Text {
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.DemiBold
                    family: root.mainfont
                    pixelSize: 13
                    capitalization: Font.AllUppercase
                }

                text: "Широта:"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                Layout.fillWidth: true
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.ExtraBold
                    family: root.mainfont
                    pixelSize: 13
                    capitalization: Font.AllUppercase
                }
                text: Number(fl_Latitude).toFixed(7) + "° N"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.DemiBold
                    family: root.mainfont
                    pixelSize: 13
                    capitalization: Font.AllUppercase
                }

                text: "Долгота:"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                Layout.fillWidth: true
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.ExtraBold
                    family: root.mainfont
                    pixelSize: 13
                    capitalization: Font.AllUppercase
                }
                text: Number(fl_Longitude).toFixed(7) + "° E"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle { width: 2; height: 32; color: ColorTheme.active.color(ColorTheme.Surface) }

        GridLayout {
            columns: 2
            Layout.fillHeight: true
            Layout.preferredWidth: 180

            Text {
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.DemiBold
                    family: root.mainfont
                    pixelSize: 13
                    capitalization: Font.AllUppercase
                }

                text: "Высота:"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                Layout.fillWidth: true
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.ExtraBold
                    family: root.mainfont
                    pixelSize: 13
                }
                text: Number(fl_Altitude).toFixed(0) + " м"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.DemiBold
                    family: root.mainfont
                    pixelSize: 13
                    capitalization: Font.AllUppercase
                }

                text: "Над уровнем моря:"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                Layout.fillWidth: true
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.ExtraBold
                    family: root.mainfont
                    pixelSize: 13
                }
                text: Number(fl_SeaAltitude).toFixed(0) + " м"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle { width: 2; height: 32; color: ColorTheme.active.color(ColorTheme.Surface) }

        GridLayout {
            columns: 2
            Layout.fillHeight: true
            Layout.preferredWidth: 140

            Text {
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.DemiBold
                    family: root.mainfont
                    pixelSize: 13
                    capitalization: Font.AllUppercase
                }

                text: "Скорость:"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                Layout.fillWidth: true
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.ExtraBold
                    family: root.mainfont
                    pixelSize: 13
                }
                text: Number(fl_Velocity).toFixed(0) + " км/ч"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.DemiBold
                    family: root.mainfont
                    pixelSize: 13
                    capitalization: Font.AllUppercase
                }

                text: "Курс:"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                Layout.fillWidth: true
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.ExtraBold
                    family: root.mainfont
                    pixelSize: 13
                }
                text: Number(fl_Direction).toFixed(1) + "°"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle { width: 2; height: 32; color: ColorTheme.active.color(ColorTheme.Surface) }

        GridLayout {
            columns: 2
            Layout.fillHeight: true
            Layout.preferredWidth: 130

            Text {
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.DemiBold
                    family: root.mainfont
                    pixelSize: 13
                    capitalization: Font.AllUppercase
                }

                text: "Спутники:"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                Layout.fillWidth: true
                color: i_SatellitesCount < 3 ? ColorTheme.active.color(ColorTheme.Red)
                                             : i_SatellitesCount < 6
                                             ? ColorTheme.active.color(ColorTheme.Yellow)
                                             : ColorTheme.active.color(ColorTheme.Green)
                font {
                    weight: Font.ExtraBold
                    family: root.mainfont
                    pixelSize: 13
                }
                text: Number(i_SatellitesCount).toFixed(0)
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.DemiBold
                    family: root.mainfont
                    pixelSize: 13
                    capitalization: Font.AllUppercase
                }

                text: "Задержка:"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                Layout.fillWidth: true
                color: fl_ConnectionDelay < 3
                       ? ColorTheme.active.color(ColorTheme.Green)
                       : fl_ConnectionDelay < 8
                       ? ColorTheme.active.color(ColorTheme.Yellow)
                       : ColorTheme.active.color(ColorTheme.Red)
                font {
                    weight: Font.ExtraBold
                    family: root.mainfont
                    pixelSize: 13
                }
                text: fl_ConnectionDelay < 0.2 ? "~0 с" : Number(fl_ConnectionDelay).toFixed(1) + " с"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle { width: 2; height: 32; color: ColorTheme.active.color(ColorTheme.Surface) }

        ColumnLayout {
            Layout.fillHeight: true

            Text {
                color: ColorTheme.active.color(ColorTheme.Text)
                font {
                    weight: Font.ExtraBold
                    family: root.mainfont
                    pixelSize: 13
                    capitalization: Font.AllUppercase
                }

                text: "Свободное место на РЛС"
                Layout.alignment: Qt.AlignHCenter
                horizontalAlignment: Text.Left
                verticalAlignment: Text.AlignVCenter
            }

            RowLayout {
                Layout.fillHeight: true

                ProgressBar {
                    value: fl_RemoteDiskSpace
                    indeterminate: fl_RemoteDiskSpace === 0
                    Material.accent: value === 0
                                     ? ColorTheme.active.color(ColorTheme.Text)
                                     : value < 0.5
                                     ? ColorTheme.active.color(ColorTheme.Red)
                                     : value < 0.8
                                     ? ColorTheme.active.color(ColorTheme.Orange)
                                     : ColorTheme.active.color(ColorTheme.Green)
                }

                Text {
                    Layout.fillHeight: true;
                    Layout.preferredWidth: 30;
                    Layout.alignment: Qt.AlignRight
                    color: ColorTheme.active.color(ColorTheme.Text)
                    font {
                        weight: Font.ExtraBold
                        family: root.mainfont
                        pixelSize: 13
                        capitalization: Font.AllUppercase
                    }
                    text: Number(fl_RemoteDiskSpace * 100).toFixed(0) + "%"
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        RoundButton {
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredHeight: 40
            Layout.preferredWidth: 40
            font.family: root.mainfont
            radius: 13
            icon.source: "qrc:/icons/vector/common/delete.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Dark)
            Material.elevation: 30
            Material.foreground: ColorTheme.active.color(ColorTheme.Dark)
            Material.background: ColorTheme.active.color(ColorTheme.Red)
            onPressed: dialogwindow.open("Очистка удаленного диска", "Вы уверены, что хотите очистить удаленное хранилище на РЛС?", "error", 27)

            Connections {
                function onClosed(status, uid) {
                    if (uid === 27 && status === true) {
                        console.log("[GUI] Clearing remote storage");
                        Network.executeCommand(Net.ClearRemoteStorage);
                    }
                }

                target: dialogwindow
            }

            Widgets.TT {
                ff: root.mainfont
                txt: "Очистить хранилище на РЛС"
            }

        }
    }
}
