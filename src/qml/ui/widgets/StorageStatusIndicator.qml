import QtQuick 2.15
import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels
import "qrc:/qml/ui/progress-bars" as ProgressBars
import Theme 1.0
import RuntimeData 1.0
import SignalLinker 1.0
import DialogWindowBackend 1.0


Item {
    property real percentage: 50;

    id: rt;
    width: 91 * Theme.scalingFactor.x;
    height: 55 * Theme.scalingFactor.y;

    Buttons.LightToolButton
    {
		property bool waitingForDialogResponse: false;

        id: clearSARCacheButton;
        enabled: !RuntimeData.windowLock;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 15 * Theme.scalingFactor.y;
        anchors.left: parent.left;
        anchors.leftMargin: 16 * Theme.scalingFactor.x;

        fixed_width: 22 * Theme.scalingFactor.x;
        fixed_height: 22 * Theme.scalingFactor.y;
        frame_color: Theme.color("light1");
        highlight_color: Theme.color("red");
        frame_radius: 11 * Theme.scalingFactor.x; frame_enabled: true;
        icon_px_size: 12 * Theme.scalingFactor.y;
        icon_source: "qrc:/icons/trashbin.png";
		onClicked: {
			RuntimeData.windowLock = true;
			DialogWindowBackend.header = "ОЧИСТКА ХРАНИЛИЩА РЛС";
			DialogWindowBackend.icon = "qrc:/icons/dialog/error.png";
			DialogWindowBackend.text = "Вы уверены, что хотите очистить хранилище изображений на РЛС? Это действие приведет к полному удалению всех снимков и голограмм. Его нельзя обратить!";
			DialogWindowBackend.show();
			waitingForDialogResponse = true;
		}
		function handleResponse()
		{
			if(waitingForDialogResponse === true)
			{
				if(DialogWindowBackend.returnCode === 1)
				{
					SignalLinker.clearSARStorage();
					waitingForDialogResponse = false;
				}
			}
		}
		Component.onCompleted: {
			DialogWindowBackend.returnCodeChanged.connect(handleResponse)
		}
    }
    ProgressBars.CircularProgressBar
    {
        id: circularProgressBar;
        start_angle: 0.349066; //20 deg
        end_angle: 5.06; //290 deg
        fixed_width: 55 * Theme.scalingFactor.x;
        fixed_height: 55 * Theme.scalingFactor.y;
        currentValue: percentage;  //Number(RuntimeData.freeDiskSpace / RuntimeData.totalDiskSpace).toFixed(0)
        line_width: 9 * Theme.scalingFactor.x;

        fill_color: Theme.color("light1");
        base_color: Theme.color("red");
        anchors.bottom: parent.bottom; anchors.left: parent.left;
        anchors.bottomMargin: -1 * Theme.scalingFactor.y;
    }
    Labels.RoundLabel
    {
        id: tooltip1;
        anchors.top: parent.top;    anchors.topMargin: 1 * Theme.scalingFactor.y;
        anchors.left: clearSARCacheButton.horizontalCenter;

        fixed_width: 65 * Theme.scalingFactor.x;
        fixed_height: 14 * Theme.scalingFactor.y;
        round_radius: 5 * Theme.scalingFactor.x;
        label_text: "ХРАНИЛИЩЕ";
        label_color: Theme.color("dark1");
        round_color: Theme.color("light1");
        label_text_size: 10 * Theme.scalingFactor.y;
        label_text_family: fontSemiBold.name;
        label_text_bold: false;
    }
    Text {
        id: percentageText;
        text: percentage === 5 ? "?%" : Number(percentage).toFixed(0) + "%";
        font.capitalization: Font.MixedCase;
        font.pixelSize: 20 * Theme.scalingFactor.y;
        font.family: fontBold.name;
        font.bold: true;
        color: Theme.color("light1");
        opacity: enabled ? 1.0 : 0.3;
        verticalAlignment: Text.AlignTop;
        horizontalAlignment: Text.AlignLeft;
        anchors.top: tooltip1.bottom;   anchors.topMargin: 0 * Theme.scalingFactor.y;
        anchors.left: clearSARCacheButton.right;    anchors.leftMargin: 6 * Theme.scalingFactor.x;
    }
    onPercentageChanged:
    {
        if(percentage >= 0 & percentage < 33) { circularProgressBar.base_color = Theme.color("green"); }
        else if(percentage >= 33 & percentage < 66) { circularProgressBar.base_color = Theme.color("yellow"); }
        else if(percentage >= 66 & percentage < 80) { circularProgressBar.base_color = Theme.color("orange"); }
        else if(percentage >= 80 & percentage <= 100) { circularProgressBar.base_color = Theme.color("red"); }
    }
}
