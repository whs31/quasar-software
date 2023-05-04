import QtQuick 2.15
import Theme 1.0

import "../../../ui/checkboxes" as Checkboxes
import "../../../ui/buttons" as Buttons

Item {
    Buttons.LightToolButton { id: button_Ruler;
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.leftMargin: 7;
        anchors.topMargin: 5;

        fixed_width: 35;
        fixed_height: 35;
        frame_color: Theme.color("light1");
        highlight_color: Theme.color("color3");
        frame_radius: 2;
        frame_enabled: true;
        icon_px_size: 22;
        icon_source: "qrc:/icons/toolbar/map/ruler.png";
        tooltip_text: "Линейка";
        tooltip_enabled: true;
        label_text_family: root.s_FontMain;
        onClicked: {

        }
    }

    Buttons.LightToolButton { id: button_Protractor;
        anchors.top: button_Ruler.top;
        anchors.left: button_Ruler.right;
        anchors.leftMargin: 6;

        fixed_width: 35;
        fixed_height: 35;
        frame_color: Theme.color("light1");
        highlight_color: Theme.color("color3");
        frame_radius: 2;
        frame_enabled: true;
        icon_px_size: 22;
        icon_source: "qrc:/icons/toolbar/map/protractor.png";
        tooltip_text: "Линейка";
        tooltip_enabled: true;
        label_text_family: root.s_FontMain;
        onClicked: {

        }
    }
}
