import QtQuick 2.15
import Theme 1.0

import "../../ui/checkboxes" as Checkboxes

Item {
    Checkboxes.LightCheckbox { id: checkbox_UseOnlineMaps;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.leftMargin: 8;
        anchors.topMargin: 8;

        fixed_width: 140;
        fixed_height: 16;
        label_text: "ОНЛАЙН-КАРТА";
        label_color: Theme.color("light1");
        label_text_size: 14;
        label_text_family: root.s_FontMain;
        label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        contrast_color: Theme.color("color0");
        highlight_color: Theme.color("color2");
        checked: true;
    }
}
