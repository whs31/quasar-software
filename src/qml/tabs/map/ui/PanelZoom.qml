import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Theme 1.0

Pane {
    Material.elevation: 30

    Column {
        RoundButton { id: button_ZoomIn
            height: 44
            width: 44
            radius: 4
            icon.source: "qrc:/icons/vector/common/plus.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Text)
            Material.elevation: 30
            Material.background: ColorTheme.active.color(ColorTheme.Surface)
            onPressed: maptab_root.zoomLevel += 0.5
        }

        RoundButton { id: button_ZoomOut
            height: 44
            width: 44
            radius: 4
            icon.source: "qrc:/icons/vector/common/minus.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Text)
            Material.elevation: 30
            Material.background: ColorTheme.active.color(ColorTheme.Surface)
            onPressed: maptab_root.zoomLevel -= 0.5
        }
    }
}
