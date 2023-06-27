import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Network 1.0

Pane {
    Material.elevation: 60;
    Material.background: ColorTheme.active.color(ColorTheme.Surface)

    RowLayout {
        RoundButton { id: button_Ping;
            text: "Проверка состояния диска";
            font.family: root.mainfont;
            height: 40;
            radius: 4;
            icon.source: "qrc:/icons/vector/network/hdd.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Text)
            Material.elevation: 30;
            Material.foreground: ColorTheme.active.color(ColorTheme.Text)
            Material.background: ColorTheme.active.color(ColorTheme.Overlay)
            onPressed: Network.executeCommand(Net.RemoteStorageStatus);
        }

        RoundButton { id: button_Reboot;
            text: "Перезагрузка";
            font.family: root.mainfont;
            height: 40;
            radius: 4;
            icon.source: "qrc:/icons/vector/common/refresh.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Dark)
            Material.elevation: 30;
            Material.foreground: ColorTheme.active.color(ColorTheme.Dark)
            Material.background: ColorTheme.active.color(ColorTheme.Orange)
            onPressed: dialogwindow.open("Перезагрузка РЛС", "Вы уверены, что хотите перезагрузить РЛС?", "warn", 21);

            Connections {
                target: dialogwindow;
                function onClosed(status, uid) {
                    if(uid === 21 && status === true) {
                        console.log("[GUI] Reboot requested");
                        Network.executeCommand(Net.Reboot);
                    }
                }
            }
        }

        RoundButton { id: button_Shutdown;
            text: "Выключить РЛС";
            font.family: root.mainfont;
            height: 40;
            radius: 4;
            icon.source: "qrc:/icons/vector/network/poweroff.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Dark)
            Material.elevation: 30;
            Material.foreground: ColorTheme.active.color(ColorTheme.Dark)
            Material.background: ColorTheme.active.color(ColorTheme.Red)
            onPressed: dialogwindow.open("Выключение РЛС", "Вы уверены, что хотите выключить РЛС?", "warn", 22);

            Connections {
                target: dialogwindow;
                function onClosed(status, uid) {
                    if(uid === 22 && status === true) {
                        console.log("[GUI] Reboot requested");
                        Network.executeCommand(Net.Poweroff);
                    }
                }
            }
        }
    }
}
