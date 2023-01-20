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
        currentValue: percentage;  //Number(RuntimeData.freeDiskSpace / RuntimeData.totalDiskSpace).toFixed(0)
        line_width: 9;

        fill_color: UX.textWhite;
        base_color: UX.errorDark;
        anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.bottomMargin: -1;
    }
    Labels.RoundLabel
    {
        id: tooltip1;
        anchors.top: parent.top;    anchors.topMargin: 1;
        anchors.left: clearSARCacheButton.horizontalCenter;

        fixed_width: 65;        fixed_height: 13;
        round_radius: 5;
        label_text: "ХРАНИЛИЩЕ";
        label_color: UX.primaryDarker;      round_color: UX.textWhite;
        label_text_size: 10;    label_text_family: fontSemiBold.name;
        label_text_bold: false;
    }
    Text {
        id: percentageText;
        text: percentage === 5 ? "?%" : Number(percentage).toFixed(0) + "%";
        font.capitalization: Font.MixedCase;
        font.pixelSize: 20;
        font.family: fontBold.name;
        font.bold: true;
        color: UX.textWhite;
        opacity: enabled ? 1.0 : 0.3;
        verticalAlignment: Text.AlignTop;
        horizontalAlignment: Text.AlignLeft;
        anchors.top: tooltip1.bottom;   anchors.topMargin: 0;
        anchors.left: clearSARCacheButton.right;    anchors.leftMargin: 6;
    }
    onPercentageChanged:
    {
        if(percentage >= 0 & percentage < 33) { circularProgressBar.base_color = UX.successLighter; }
        else if(percentage >= 33 & percentage < 66) { circularProgressBar.base_color = UX.warningLight; }
        else if(percentage >= 66 & percentage < 80) { circularProgressBar.base_color = UX.warningDark; }
        else if(percentage >= 80 & percentage <= 100) { circularProgressBar.base_color = UX.errorDark; }
    }
}
