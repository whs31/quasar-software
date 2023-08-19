import QtQuick 2.15

Rectangle { id: control;
    property int connected: 0;
    width: 10;
    height: 10;
    radius: width / 2;
    color: connected === 2 ? theme.green
                           : connected === 1 ? theme.yellow
                           : theme.red

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
