import QtQuick 2.15
import Theme 1.0

Rectangle { id: control;
    property int connected: 0;
    width: 10;
    height: 10;
    radius: width / 2;
    color: connected === 2 ? ColorTheme.active.color(ColorTheme.Green)
                           : connected === 1 ? ColorTheme.active.color(ColorTheme.Yellow)
                           : ColorTheme.active.color(ColorTheme.Red)

    SequentialAnimation {
        NumberAnimation {
            target: control;
            property: "opacity";
            from: 0;
            to: 1;
            duration: 500;
        }
        NumberAnimation {
            target: control;
            property: "opacity";
            from: 1;
            to: 0;
            duration: 500;
        }
        loops: Animation.Infinite;
        running: (connected === 2);
    }
}
