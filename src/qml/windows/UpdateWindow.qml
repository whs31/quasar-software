import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import Qt5Compat.GraphicalEffects

import Theme 1.0
import Config 1.0
import Application 1.0

Pane {
    property bool b_Shown: UpdateNotifier.status

    width: b_Shown ? implicitWidth : 0
    height: b_Shown ? implicitHeight : 0
    visible: height > 0
    enabled: visible
    Behavior on height { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad; } }
    Behavior on width { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad; } }
    clip: true

    Material.background: ColorTheme.active.color(ColorTheme.Dark)
    Material.elevation: 200

    layer.enabled: true
    layer.effect: DropShadow {
        samples: 16
        radius: 16
        horizontalOffset: 6
        verticalOffset: 6
        opacity: 0.5
    }

    ColumnLayout {
        Text {
            Layout.fillWidth: true
            font {
                family: root.mainfont
                pixelSize: 16
                bold: true
            }
            color: ColorTheme.active.color(ColorTheme.Text)
            text: "ДОСТУПНО ОБНОВЛЕНИЕ ПРИЛОЖЕНИЯ"
            horizontalAlignment: Text.AlignHCenter
        }

        Item { Layout.preferredHeight: 15; }

        RowLayout {
            Layout.fillWidth: true

            Text {
                Layout.fillWidth: true
                font {
                    family: root.mainfont
                    pixelSize: 14
                    bold: true
                }
                color: ColorTheme.active.color(ColorTheme.Text)
                text: "Текущая версия приложения:"
                horizontalAlignment: Text.AlignLeft
            }

            Text {
                font {
                    family: root.mainfont
                    pixelSize: 15
                    bold: true
                }
                color: ColorTheme.active.color(ColorTheme.Orange)
                text: Settings.projectVersion
                horizontalAlignment: Text.AlignRight
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Text {
                Layout.fillWidth: true
                font {
                    family: root.mainfont
                    pixelSize: 14
                    bold: true
                }
                color: ColorTheme.active.color(ColorTheme.Text)
                text: "Доступная версия приложения:"
                horizontalAlignment: Text.AlignLeft
            }

            Text {
                font {
                    family: root.mainfont
                    pixelSize: 15
                    bold: true
                }
                color: ColorTheme.active.color(ColorTheme.Green)
                text: UpdateNotifier.remoteVersion()
                horizontalAlignment: Text.AlignRight
            }
        }

        Item { Layout.preferredHeight: 30; }

        RowLayout {
            visible: UpdateLoader.progress != 0;
            Layout.fillWidth: true;

            ProgressBar {
                from: 0
                to: 1
                value: UpdateLoader.progress
                width: 295
            }

            Text {
                font {
                    family: root.mainfont
                    pixelSize: 15
                    bold: true
                }
                color: ColorTheme.active.color(ColorTheme.Text)
                text: Number(UpdateLoader.downloadedBytes / 1024).toFixed(0) + " кБ / " + Number(UpdateLoader.totalBytes / 1024).toFixed(0) + " кБ";
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter
            }
        }

        Row {
            Layout.fillWidth: true
            RoundButton {
                enabled: UpdateLoader.progress === 0;
                width: 200
                font.family: root.mainfont
                font.weight: Font.Bold
                height: 44
                radius: 4
                Material.elevation: 30
                Material.background: ColorTheme.active.color(ColorTheme.BaseShade)
                text: "Обновить"
                onPressed: UpdateLoader.download(UpdateNotifier.link());
            }

            RoundButton {
                enabled: UpdateLoader.progress === 0;
                width: 200
                font.family: root.mainfont
                font.weight: Font.Bold
                height: 44
                radius: 4
                Material.elevation: 30
                Material.background: ColorTheme.active.color(ColorTheme.Dark)
                text: "Закрыть"
                onPressed: b_Shown = false
            }

            Connections {
                target: UpdateLoader;
                function onDownloadFinished() {
                    UpdateLoader.cache(Paths.imageCache() + "/QuaSAR.exe");
                    b_Shown = false;
                    console.log("$ [GUI] Update download completed");
                }
            }
        }
    }
}
