import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Network 1.0

Pane {
    Material.elevation: 60;
    Material.background: Theme.color("dark2");

    RowLayout {
        RoundButton { id: button_Ping;
            text: "Проверка состояния диска";
            font.family: root.mainfont;
            height: 40;
            radius: 4;
            icon.source: "qrc:/icons/google-material/storage.png"
            icon.color: Theme.color("light0");
            Material.elevation: 30;
            Material.foreground: Theme.color("light0");
            Material.background: Theme.color("dark3");
            onPressed: Network.executeCommand(Net.RemoteStorageStatus);
        }

        RoundButton { id: button_Reboot;
            text: "Перезагрузка";
            font.family: root.mainfont;
            height: 40;
            radius: 4;
            icon.source: "qrc:/icons/google-material/reboot.png"
            icon.color: Theme.color("dark0");
            Material.elevation: 30;
            Material.foreground: Theme.color("dark0");
            Material.background: Theme.color("orange");
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
            icon.source: "qrc:/icons/google-material/poweroff.png"
            icon.color: Theme.color("dark0");
            Material.elevation: 30;
            Material.foreground: Theme.color("dark0");
            Material.background: Theme.color("red");
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
