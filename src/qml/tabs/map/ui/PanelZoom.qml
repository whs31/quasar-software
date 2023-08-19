import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Pane {
    Material.elevation: 30

    Column {
        RoundButton { id: button_ZoomIn
            height: 44
            width: 44
            radius: 4
            icon.source: "qrc:/icons/vector/common/plus.svg"
            icon.color: theme.text
            Material.elevation: 30
            Material.background: theme.surface0
            onPressed: maptab_root.zoomLevel += 0.5
        }

        RoundButton { id: button_ZoomOut
            height: 44
            width: 44
            radius: 4
            icon.source: "qrc:/icons/vector/common/minus.svg"
            icon.color: theme.text
            Material.elevation: 30
            Material.background: theme.surface0
            onPressed: maptab_root.zoomLevel -= 0.5
        }
    }
}
