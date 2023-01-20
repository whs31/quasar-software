import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import RuntimeData 1.0
import "qrc:/qml/ui" as UI
import UX 1.0

//114855520 111111159808 example cache clear string
Item {
    width: childrenRect.width;
    height: childrenRect.height;
    UI.CustomButton
    {
        id: continuousFormButton;
        iconsource: "qrc:/ui-resources/white/timer.png";
        primarycolor: UX.primaryLight;
        width: 320;
        height: 20;
        iconsize: 14;
        labeltext: RuntimeData.formingContinuous ? "Непрерывное формирование включено" : "Непрерывное формирование выключено";
        boldness: true;
        onClicked: ioHandler.formContinuously();
        z: 99;
    }
    Rectangle
    {
        id: textBackground;
        color: UX.primaryDark;
        radius: 10;
        width: diskSpaceText.paintedWidth + 15;
        height: diskSpaceText.paintedHeight + 5;
        anchors.top: continuousFormButton.bottom;
        anchors.topMargin: 6;
        Text {
            id: diskSpaceText;
            color: UX.textColored;
            font.capitalization: Font.MixedCase;
            font.pixelSize: 13;
            anchors.centerIn: parent;
            textFormat: Text.RichText
            text: RuntimeData.freeDiskSpace !== 0 ? "Хранилище изображений заполнено на <b>" + Number(RuntimeData.freeDiskSpace / RuntimeData.totalDiskSpace).toFixed(0) + "%</b>.<br>
                  Свободно <b>" + Number(RuntimeData.freeDiskSpace).toFixed(1) + " ГБ </b> из <b>" + Number(RuntimeData.totalDiskSpace).toFixed(1) + " ГБ </b>" : "Невозможно определить состояние хранилища.";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
        }
    }
    UI.CustomButton
    {
        id: clearDiskButton;
        iconsource: "qrc:/ui-resources/white/trashbin.png";
        primarycolor: UX.errorDark;
        accentcolor: UX.errorDarker;
        width: 160;
        height: 20;
        anchors.top: textBackground.bottom;
        anchors.topMargin: 6;
        iconsize: 14;
        labeltext: "Очистить хранилище";
        boldness: false;
        onClicked: ioHandler.clearSARDisk();
        z: 99;
    }
}
