import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import Network 1.0

Pane { id: panel_EditorToolbar
    Material.elevation: 30

    Row {
        RoundButton { id: button_FormImage
            font.family: root.mainfont
            height: 40
            radius: 4
            icon.source: "qrc:/icons/vector/images/reform.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Dark)
            text: "Переформирование изображения"
            Material.elevation: 30
            Material.foreground: ColorTheme.active.color(ColorTheme.Dark)
            Material.background: ColorTheme.active.color(ColorTheme.Accent)
            onPressed: Network.executeCommand(Net.ReformImage)
        }

        RoundButton { id: button_FocusImage
            enabled: focustab_root.currentTool === 1
            font.family: root.mainfont
            height: 40
            radius: 4
            icon.source: "qrc:/icons/vector/images/focus_circle.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Dark)
            text: "Фокусировка изображения"
            Material.elevation: 30
            Material.foreground: ColorTheme.active.color(ColorTheme.Dark)
            Material.background: ColorTheme.active.color(ColorTheme.Orange)
            onPressed: Network.executeCommand(Net.FocusImage)
        }
    }
}
