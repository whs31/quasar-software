import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0

import "../../widgets" as Widgets

Pane { id: panel_EditorTools;
    Material.elevation: 30;

    Column {
        RoundButton { id: button_Hand;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/google-material/hand.png";
            icon.color: focustab_root.currentTool === 0 ? Theme.color("dark0") : Theme.color("light0");
            Material.elevation: 30;
            Material.background: focustab_root.currentTool === 0 ? Theme.color("color0") : Theme.color("dark2");
            onPressed: focustab_root.currentTool = 0;

            Widgets.TT { ff: root.mainfont; txt: "Инструмент перемещения"; }
        }

        RoundButton { id: button_Focus;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/google-material/focus-scope.png";
            icon.color: focustab_root.currentTool === 1 ? Theme.color("dark0") : Theme.color("light0");
            Material.elevation: 30;
            Material.background: focustab_root.currentTool === 1 ? Theme.color("orange") : Theme.color("dark2");
            onPressed: {
                if(focustab_root.currentTool === 1)
                    focustab_root.currentTool = 0;
                else
                    focustab_root.currentTool = 1;
            }

            Widgets.TT { ff: root.mainfont; txt: "Инструмент фокусировки"; }
        }
    }
}
