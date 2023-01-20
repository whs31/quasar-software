import QtQuick 2.15
import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels
import "qrc:/qml/ui/progress-bars" as ProgressBars
import UX 1.0

Item {
    property real percentage: 50;

    id: rt;
    width: 91;
    height: 55;

    Buttons.LightToolButton
    {
        id: clearSARCacheButton;
        anchors.bottom: parent.bottom; anchors.bottomMargin: 15;
        anchors.left: parent.left;    anchors.leftMargin: 16;

        fixed_width: 22;      fixed_height: 22;
        frame_color: UX.textWhite;
        highlight_color: UX.errorDark;
        frame_radius: 11; frame_enabled: true;
        icon_px_size: 12;
        icon_source: "qrc:/icons/trashbin.png";
        onClicked: {
            ioHandler.clearSARDisk();
        }
    }
    ProgressBars.CircularProgressBar
    {
        id: circularProgressBar;
        start_angle: 0.349066; //20 deg
        end_angle: 5.06; //290 deg
        fixed_width: 55;
        fixed_height: 55;
        minimumValue: 0;
        maximumValue: 100;
        currentValue: percentage;  //Number(RuntimeData.freeDiskSpace / RuntimeData.totalDiskSpace).toFixed(0)
        line_width: 9;

        fill_color: UX.textWhite;
        base_color: UX.errorDark;
        anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.bottomMargin: -1;
    }
}
