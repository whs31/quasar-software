import QtQuick 2.15
import Theme 1.0
import ClickHandler 1.0

import "../../../ui/checkboxes" as Checkboxes
import "../../../ui/buttons" as Buttons

Item {
    Buttons.LightToolButton { id: button_PanImage;
        anchors.top: button_Protractor.top;
        anchors.left: button_Protractor.right;
        anchors.leftMargin: 44;

        fixed_width: 35;
        fixed_height: 35;
        frame_color: Theme.color("light1");
        highlight_color: Theme.color("green");
        frame_radius: 2;
        frame_enabled: true;
        icon_px_size: 22;
        icon_source: "qrc:/icons/toolbar/map/map.png";
        tooltip_text: "Переместиться к последнему полученному РЛИ";
        tooltip_enabled: true;
        label_text_family: root.s_FontMain;
        onClicked: {
            root.map_pan_image();
        }
    }

    Buttons.LightToolButton { id: button_PanUAV;
        anchors.top: button_PanImage.top;
        anchors.left: button_PanImage.right;
        anchors.leftMargin: 6;

        fixed_width: 35;
        fixed_height: 35;
        frame_color: Theme.color("light1");
        highlight_color: Theme.color("green");
        frame_radius: 2;
        frame_enabled: true;
        icon_px_size: 22;
        icon_source: "qrc:/icons/toolbar/map/gps.png";
        tooltip_text: "Переместиться к БПЛА";
        tooltip_enabled: true;
        label_text_family: root.s_FontMain;
        onClicked: {
            root.map_pan_uav();
        }
    }

    Checkboxes.LightCheckbox { id: checkbox_EnableGrid;
        anchors.left: parent.left;
        anchors.top: button_PanUAV.bottom;
        anchors.leftMargin: 8;
        anchors.topMargin: 9;

        fixed_width: 193;
        fixed_height: 16;
        label_text: "МАСШТАБНАЯ СЕТКА      ";
        label_color: Theme.color("light1");
        label_text_size: 14;
        label_text_family: root.s_FontMain;
        label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        contrast_color: Theme.color("color0");
        highlight_color: Theme.color("color3");
        checked: false;

        onCheckedChanged: {
            root.b_MapShowGrid = checked;
        }
    }
}
