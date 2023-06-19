import QtQuick 2.15
import QtQuick.Controls 2.15

ToolTip { id: control;
    property string txt: "Tooltip";
    property string ff: "Arial";

    visible: parent.hovered;
    font {
        pixelSize: 11;
        family: ff;
    }
    contentItem: Text {
        text: txt;
        font: control.font;
        color: "#bac2de";
    }
    background: Rectangle {
        color: "#11111b";
        radius: 3;
    }
    delay: 500;
}
