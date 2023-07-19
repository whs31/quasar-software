import QtQuick 2.15
import QtQuick.Controls 2.15
import Theme 1.0

ToolTip { id: control;
    property string txt: "Tooltip";

    visible: parent.hovered;
    font {
        pixelSize: 13;
    }
    contentItem: Text {
        text: txt;
        font: control.font;
        color: ColorTheme.active.color(ColorTheme.Text)
    }
    background: Rectangle {
        color: ColorTheme.active.color(ColorTheme.Dark)
        radius: 3;
    }
    delay: 500;
}
