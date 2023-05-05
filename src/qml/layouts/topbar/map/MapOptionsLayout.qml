import QtQuick 2.15
import Theme 1.0

import "../../../ui/checkboxes" as Checkboxes

Item {
    Checkboxes.LightCheckbox { id: checkbox_ShowTrack;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.leftMargin: 2;
        anchors.topMargin: 9;

        fixed_width: 250;
        fixed_height: 16;
        label_text: "ТРЕК ПОЛЁТА";
        label_color: Theme.color("light1");
        label_text_size: 14;
        label_text_family: root.s_FontMain;
        label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        contrast_color: Theme.color("color0");
        highlight_color: Theme.color("color3");
        checked: true;

        onCheckedChanged: {
            root.b_MapShowTrack = checked;
        }
    }

    Checkboxes.LightCheckbox { id: checkbox_ShowDiagram;
        anchors.left: checkbox_ShowTrack.left;
        anchors.top: checkbox_ShowTrack.bottom;
        anchors.topMargin: 4;

        fixed_width: 250;
        fixed_height: 16;
        label_text: "ДИАГРАММА НАПРАВЛЕННОСТИ";
        label_color: Theme.color("light1");
        label_text_size: 14;
        label_text_family: root.s_FontMain;
        label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        contrast_color: Theme.color("color0");
        highlight_color: Theme.color("color3");
        checked: true;

        onCheckedChanged: {
            root.b_MapShowDiagram = checked;
        }
    }

    Checkboxes.LightCheckbox { id: checkbox_ShowCursorCoords;
        anchors.left: checkbox_ShowDiagram.left;
        anchors.top: checkbox_ShowDiagram.bottom;
        anchors.topMargin: 4;

        fixed_width: 250;
        fixed_height: 16;
        label_text: "КООРДИНАТЫ КУРСОРА";
        label_color: Theme.color("light1");
        label_text_size: 14;
        label_text_family: root.s_FontMain;
        label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        contrast_color: Theme.color("color0");
        highlight_color: Theme.color("color3");
        checked: true;

        onCheckedChanged: {
            root.b_MapShowCursorCoords = checked;
        }
    }
}
