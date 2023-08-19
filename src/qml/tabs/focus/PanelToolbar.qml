import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import "../../widgets" as Widgets

Pane { id: panel_EditorTools;
    Material.elevation: 30;

    Column {
        RoundButton { id: button_Hand;
            height: 44
            width: 44
            radius: 4
            icon.source: "qrc:/icons/vector/images/pan.svg"
            icon.color: focustab_root.currentTool === 0 ? theme.base : theme.text
            Material.elevation: 30
            Material.background: focustab_root.currentTool === 0 ? theme.blue : theme.surface0
            onPressed: focustab_root.currentTool = 0

            Widgets.TT { txt: "Инструмент перемещения"; }
        }

        RoundButton { id: button_Focus
            height: 44
            width: 44
            radius: 4
            icon.source: "qrc:/icons/vector/images/focus_circle.svg"
            icon.color: focustab_root.currentTool === 1 ? theme.base : theme.text
            Material.elevation: 30
            Material.background: focustab_root.currentTool === 1 ? theme.peach : theme.surface0
            onPressed: {
                if(focustab_root.currentTool === 1)
                    focustab_root.currentTool = 0
                else
                    focustab_root.currentTool = 1
            }

            Widgets.TT { txt: "Инструмент фокусировки"; }
        }
    }
}
