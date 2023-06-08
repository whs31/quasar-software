import QtQuick 2.15
import QtQuick.Controls 2.15

ToolTip { id: control;
    visible: hovered;
    font {
        family: root.mainfont
        pixelSize: 13
    }

    contentItem: Text {
        text: control.text;
        font: control.font;
        color: Theme.color("dark0");
    }

    background: Rectangle {
        color: Theme.color("light1");
        radius: 3;
    }

    delay: 500;
    text: "Example text";
}
