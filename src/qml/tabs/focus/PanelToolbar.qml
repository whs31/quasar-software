import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0

import "../../widgets" as Widgets

Pane { id: panel_EditorTools;
    Material.elevation: 30;

    Column {
        RoundButton { id: button_Hand;
            height: 44
            width: 44
            radius: 4
            icon.source: "qrc:/icons/vector/images/pan.svg"
            icon.color: focustab_root.currentTool === 0 ? ColorTheme.active.color(ColorTheme.Dark) : ColorTheme.active.color(ColorTheme.Text)
            Material.elevation: 30
            Material.background: focustab_root.currentTool === 0 ? ColorTheme.active.color(ColorTheme.PrimaryDark) : ColorTheme.active.color(ColorTheme.Surface)
            onPressed: focustab_root.currentTool = 0

            Widgets.TT { ff: root.mainfont; txt: "Инструмент перемещения"; }
        }

        RoundButton { id: button_Focus
            height: 44
            width: 44
            radius: 4
            icon.source: "qrc:/icons/vector/images/focus_circle.svg"
            icon.color: focustab_root.currentTool === 1 ? ColorTheme.active.color(ColorTheme.Dark) : ColorTheme.active.color(ColorTheme.Text)
            Material.elevation: 30
            Material.background: focustab_root.currentTool === 1 ? ColorTheme.active.color(ColorTheme.Orange) : ColorTheme.active.color(ColorTheme.Surface)
            onPressed: {
                if(focustab_root.currentTool === 1)
                    focustab_root.currentTool = 0
                else
                    focustab_root.currentTool = 1
            }

            Widgets.TT { ff: root.mainfont; txt: "Инструмент фокусировки"; }
        }
    }
}
