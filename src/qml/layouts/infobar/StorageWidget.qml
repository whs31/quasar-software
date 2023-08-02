import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import "../../widgets" as Widgets

import QuaSAR.API 1.0

RowLayout
{
    property real remoteDiskSpace: NetworkAPI.remote.storageSpace

    ToolButton  {
        flat: true
        icon {
            source: "qrc:/icons/vector/network/storage.svg"
            color: ColorTheme.active.color(ColorTheme.Text)
        }

        Material.foreground: ColorTheme.active.color(ColorTheme.Text)
        Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }

        Layout.preferredWidth: 45

        Widgets.TT { txt: "Текущее свободное место в хранилище РЛС" }
    }

    RowLayout {
        Layout.fillHeight: true

        ProgressBar {
            value: remoteDiskSpace
            from: 0
            to: 100
            indeterminate: remoteDiskSpace === 0
            Material.accent: value === 0
                             ? ColorTheme.active.color(ColorTheme.Text)
                             : value < 50
                               ? ColorTheme.active.color(ColorTheme.Red)
                               : value < 80
                                 ? ColorTheme.active.color(ColorTheme.Orange)
                                 : ColorTheme.active.color(ColorTheme.Green)
            Layout.preferredWidth: 100
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
            text: Number(remoteDiskSpace).toFixed(0) + "%"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
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
                    NetworkAPI.execd.execute(Net.ClearRemoteStorage)
                }
            }

            target: dialogwindow
        }

        Widgets.TT {  txt: "Очистить хранилище на РЛС" }
    }
}

