import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import Config 1.0
import Markers 1.0
import Application 1.0

MenuBar {
    Menu {
        Material.background: ColorTheme.active.color(ColorTheme.Surface)
        title: "Файл"
        Menu {
            Material.background: ColorTheme.active.color(ColorTheme.Surface)
            contentWidth: 300
            title: "Экспорт"
            Action {
                text: "Экспортировать выбранные изображения";
                icon {
                    source: "qrc:/icons/vector/images/images.svg"
                    color: ColorTheme.active.color(ColorTheme.Text)
                }
                onTriggered: window_ExportDialog.open()
            }
            MenuSeparator { }

            Action {
                text: "Сохранить маркеры в JSON"
                icon {
                    source: "qrc:/icons/vector/common/file_percent.svg"
                    color: ColorTheme.active.color(ColorTheme.Text)
                }
                onTriggered: MarkersModel.save(Paths.markers() + "/" + Utils.currentDateString() + ".json", MarkersModel.JSON)
            }
            Action {
                text: "Сохранить маркеры в текстовый файл"
                icon {
                    source: "qrc:/icons/vector/common/file.svg"
                    color: ColorTheme.active.color(ColorTheme.Text)
                }
                onTriggered: MarkersModel.save(Paths.markers() + "/" + Utils.currentDateString() + ".txt", MarkersModel.PlainText)
            }
        }

        MenuSeparator { }

        Action {
            text: "Выйти"
            icon {
                source: "qrc:/icons/vector/common/close.svg"
                color: ColorTheme.active.color(ColorTheme.Text)
            }
            onTriggered: Qt.quit()
        }
    }

    Menu {
        Material.background: ColorTheme.active.color(ColorTheme.Surface)
        title: "Правка"

        MenuSeparator { }

        Action {
            text: "Настройки"
            icon {
                source: "qrc:/icons/vector/common/settings.svg"
                color: ColorTheme.active.color(ColorTheme.Text)
            }
            onTriggered: settingswindow.shown = !settingswindow.shown
        }
    }

    Menu {
        Material.background: ColorTheme.active.color(ColorTheme.Surface)
        title: "Дополнительно"
        contentWidth: 300
        Action {
            text: "Консоль разработчика"
            icon {
                source: "qrc:/icons/vector/common/terminal.svg"
                color: ColorTheme.active.color(ColorTheme.Text)
            }
            onTriggered: root.consoleshown = !root.consoleshown
        }

        Action {
            text: "Консоль РЛС"
            icon {
                source: "qrc:/icons/vector/common/remote_display.svg"
                color: ColorTheme.active.color(ColorTheme.Text)
            }
            onTriggered: root.vt100termshown = !root.vt100termshown
        }

        MenuSeparator { }

        Action {
            text: "О программе"
            icon {
                source: "qrc:/icons/vector/common/info.svg"
                color: ColorTheme.active.color(ColorTheme.Accent)
            }
            onTriggered: c_InfoWindow.b_Shown = !c_InfoWindow.b_Shown
        }
    }
}
