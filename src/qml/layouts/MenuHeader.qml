import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import QuaSAR.API 1.0

import Config 1.0
import Markers 1.0
import Application 1.0
import Filesystem 1.0

MenuBar {
    Menu {
        Material.background: theme.mantle
        title: "Файл"
        contentWidth: 300
        Menu {
            Material.background: theme.mantle
            contentWidth: 400
            title: "Экспорт"
            Action {
                text: "Экспортировать выбранные изображения";
                icon {
                    source: "qrc:/icons/vector/images/images.svg"
                    color: theme.text
                }
                onTriggered: window_ExportDialog.open()
            }
            MenuSeparator { }

            Action {
                text: "Сохранить маркеры в JSON"
                icon {
                    source: "qrc:/icons/vector/common/file_percent.svg"
                    color: theme.text
                }
                onTriggered: MarkersModel.save(Paths.markers() + "/" + Utils.currentDateString() + ".json", MarkersModel.JSON)
            }
            Action {
                text: "Сохранить маркеры в текстовый файл"
                icon {
                    source: "qrc:/icons/vector/common/file.svg"
                    color: theme.text
                }
                onTriggered: MarkersModel.save(Paths.markers() + "/" + Utils.currentDateString() + ".txt", MarkersModel.PlainText)
            }
        }

        MenuSeparator { }

        Action {
            text: "Закрыть программу"
            icon {
                source: "qrc:/icons/vector/common/close.svg"
                color: theme.text
            }
            onTriggered: Qt.quit()
        }
    }

    Menu {
        Material.background: theme.mantle
        title: "Изображения"
        contentWidth: 400

        Action {
            text: "Обновить выбранный каталог"
            icon {
                source: "qrc:/icons/vector/common/refresh.svg"
                color: theme.mantle
            }

            onTriggered: {
                let ret = Filesystem.fetchImageDirectory();
                if(!ret)
                    messagebox.open("Не найдены изображения", "В целевой папке не найдены радиолокационные изображения.", "warn");
            }
        }

        Action {
            text: "Выбрать каталог с изображениями"
            icon {
                source: "qrc:/icons/vector/common/open.svg"
                color: theme.text
            }

            onTriggered: window_FileDialog.open()
        }

        MenuSeparator { }

        Action {
            text: "Очистить локальный кэш"
            icon {
                source: "qrc:/icons/vector/common/delete.svg"
                color: theme.text
            }

            onTriggered: dialogwindow.open("Очистка кэша", "Вы уверены, что хотите очистить кэш радиолокационных изображений? \n" +
                                           "Все изображения, сохраненные на этом АРМ, будут удалены!", "warn", 3)
        }
    }

    Menu {
        Material.background: theme.mantle
        title: "Сеть"
        contentWidth: 300

        Action {
            text: "Проверка хранилища РЛС"
            icon {
                source: "qrc:/icons/vector/network/hdd.svg"
                color: theme.text
            }
            onTriggered: NetworkAPI.execd.execute(Net.RemoteStorageStatus)
        }

        MenuSeparator { }

        Action {
            text: "Перезагрузить РЛС"
            icon {
                source: "qrc:/icons/vector/common/refresh.svg"
                color: theme.text
            }
            onTriggered: dialogwindow.open("Перезагрузка РЛС", "Вы уверены, что хотите перезагрузить РЛС?", "warn", 21)
        }

        Action {
            text: "Выключить РЛС"
            icon {
                source: "qrc:/icons/vector/network/poweroff.svg"
                color: theme.text
            }
            onTriggered: dialogwindow.open("Выключение РЛС", "Вы уверены, что хотите выключить РЛС?", "warn", 22)
        }
    }

    Menu {
        Material.background: theme.mantle
        title: "Дополнительно"
        contentWidth: 300
        Action {
            text: "Консоль разработчика"
            icon {
                source: "qrc:/icons/vector/common/terminal.svg"
                color: theme.text
            }
            onTriggered: root.consoleshown = !root.consoleshown
        }

        Action {
            text: "Консоль РЛС"
            icon {
                source: "qrc:/icons/vector/common/remote_display.svg"
                color: theme.text
            }
            onTriggered: root.vt100termshown = !root.vt100termshown
        }

        MenuSeparator { }

        Action {
            text: "О программе"
            icon {
                source: "qrc:/icons/vector/common/info.svg"
                color: theme.mauve
            }
            onTriggered: c_InfoWindow.b_Shown = !c_InfoWindow.b_Shown
        }
    }

    Connections {
        target: dialogwindow;
        function onClosed(status, uid) {
            if(uid === 3 && status === true) {
                console.log("[GUI] Cache cleared");
                Paths.clearImageCache();
            }
            if(uid === 21 && status === true) {
                console.log("[GUI] Reboot requested");
                NetworkAPI.execd.execute(Net.Reboot)
            }
            if(uid === 22 && status === true) {
                console.log("[GUI] Reboot requested");
                NetworkAPI.execd.execute(Net.PowerOff)
            }
        }
    }
}
