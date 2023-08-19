import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import "../../widgets" as Widgets

import QuaSAR.API 1.0

RowLayout
{
    property real remoteDiskSpace: NetworkAPI.remote.storageSpace

    ToolButton {
        flat: true
        icon {
            source: "qrc:/icons/vector/network/storage.svg"
            color: theme.text
        }

        Material.foreground: theme.text
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
                             ? theme.text
                             : value < 50
                               ? theme.red
                               : value < 80
                                 ? theme.peach
                                 : theme.green
            Layout.preferredWidth: 100
        }

        Text {
            Layout.fillHeight: true;
            Layout.preferredWidth: 30;
            Layout.alignment: Qt.AlignRight
            color: theme.text
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
        icon.color: theme.base
        Material.elevation: 30
        Material.foreground: theme.base
        Material.background: theme.red
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

