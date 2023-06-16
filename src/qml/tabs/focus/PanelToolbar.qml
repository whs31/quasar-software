import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0

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

            ToolTip { id: tt1; visible: parent.hovered; font { family: root.mainfont; pixelSize: 13; }
                      contentItem: Text { text: tt1.text; font: tt1.font;  color: Theme.color("dark0"); }
                      background: Rectangle { color: Theme.color("light1"); radius: 3; } delay: 500;
                      text: "Инструмент перемещения"; }
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

            ToolTip { id: tt2; visible: parent.hovered; font { family: root.mainfont; pixelSize: 13; }
                      contentItem: Text { text: tt2.text; font: tt2.font;  color: Theme.color("dark0"); }
                      background: Rectangle { color: Theme.color("light1"); radius: 3; } delay: 500;
                      text: "Инструмент фокусировки"; }
        }
    }
}
