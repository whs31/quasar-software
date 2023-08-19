import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import QuaSAR.API 1.0

Pane { id: panel_EditorToolbar
    Material.elevation: 30

    Row {
        RoundButton { id: button_FormImage
            font.family: root.mainfont
            height: 40
            radius: 4
            icon.source: "qrc:/icons/vector/images/reform.svg"
            icon.color: theme.base
            text: "Переформирование изображения"
            Material.elevation: 30
            Material.foreground: theme.base
            Material.background: theme.mauve
            onPressed: NetworkAPI.execd.execute(Net.ReformImage)
        }

        RoundButton { id: button_FocusImage
            enabled: focustab_root.currentTool === 1
            font.family: root.mainfont
            height: 40
            radius: 4
            icon.source: "qrc:/icons/vector/images/focus_circle.svg"
            icon.color: theme.base
            text: "Фокусировка изображения"
            Material.elevation: 30
            Material.foreground: theme.base
            Material.background: theme.peach
            onPressed: NetworkAPI.execd.execute(Net.FocusImage)
        }
    }
}
