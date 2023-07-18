import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import Config 1.0
import Markers 1.0

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
                //onTriggered: window_ExportDialog.open()
            }
            Action {
                text: "Сохранить маркеры в текстовый файл"
                icon {
                    source: "qrc:/icons/vector/common/file.svg"
                    color: ColorTheme.active.color(ColorTheme.Text)
                }
                //onTriggered: window_ExportDialog.open()
            }
        }

        MenuSeparator { }

        Action { text: "Выход"; onTriggered: Qt.quit(); }
    }
}
