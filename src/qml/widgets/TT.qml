import QtQuick 2.15
import QtQuick.Controls 2.15

ToolTip { id: control;
    property string txt: "Tooltip";

    visible: parent.hovered;
    font {
        pixelSize: 13;
    }
    contentItem: Text {
        text: txt;
        font: control.font;
        color: theme.text
    }
    background: Rectangle {
        color: theme.crust
        radius: 3;
    }
    delay: 500;
}
