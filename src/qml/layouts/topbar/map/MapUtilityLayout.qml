import QtQuick 2.15
import Theme 1.0
import ClickHandler 1.0

import "../../../ui/buttons" as Buttons

Item {
    Buttons.LightToolButton { id: button_HideEntities;
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.leftMargin: 7;
        anchors.topMargin: 5;

        fixed_width: 35;
        fixed_height: 35;
        frame_color: Theme.color("light1");
        background_color: "transparent";
        highlight_color: Theme.color("orange");
        frame_radius: 2;
        frame_enabled: true;
        icon_px_size: 22;
        icon_source: "qrc:/icons/toolbar/map/hidden.png";
        tooltip_text: "Скрыть все объекты карты";
        tooltip_enabled: true;
        label_text_family: root.s_FontMain;
        onClicked: {
            root.map_hide_entities();
        }
    }

    Buttons.LightToolButton { id: button_ClearTrack;
        anchors.top: button_HideEntities.top;
        anchors.left: button_HideEntities.right;
        anchors.leftMargin: 6;

        fixed_width: 35;
        fixed_height: 35;
        frame_color: Theme.color("light1");
        background_color: "transparent";
        highlight_color: Theme.color("red");
        frame_radius: 2;
        frame_enabled: true;
        icon_px_size: 22;
        icon_source: "qrc:/icons/toolbar/map/eraser.png";
        tooltip_text: "Очистить трек полёта";
        tooltip_enabled: true;
        label_text_family: root.s_FontMain;
        onClicked: {
            root.map_clear_track();
        }
    }

    Buttons.LightToolButton { id: button_ClearEntities;
        anchors.top: button_ClearTrack.top;
        anchors.left: button_ClearTrack.right;
        anchors.leftMargin: 6;

        fixed_width: 35;
        fixed_height: 35;
        frame_color: Theme.color("light1");
        background_color: "transparent";
        highlight_color: Theme.color("red");
        frame_radius: 2;
        frame_enabled: true;
        icon_px_size: 22;
        icon_source: "qrc:/icons/toolbar/map/trash.png";
        tooltip_text: "Очистить карту от маркеров и радиолокационных изображений";
        tooltip_enabled: true;
        label_text_family: root.s_FontMain;
        onClicked: {
            root.map_clear_entities();
        }
    }
}


