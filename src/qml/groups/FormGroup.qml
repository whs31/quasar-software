import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import RuntimeData 1.0
import "qrc:/qml/ui" as UI
import UX 1.0

Item {
    width: childrenRect.width;
    height: childrenRect.height;
    UI.CustomButton
    {
        id: formImageButton;
        iconsource: "qrc:/ui-resources/white/newimage.png";
        primarycolor: UX.primaryLight;
        width: 320;
        height: 20;
        iconsize: 14;
        labeltext: "Формирование одиночного изображения";
        boldness: true;
        onClicked: ioHandler.formSingleImage();
        z: 99;
    }
    UI.CustomButton
    {
        id: continuousFormButton;
        iconsource: "qrc:/ui-resources/white/timer.png";
        primarycolor: UX.primaryLight;
        width: 320;
        height: 20;
        anchors.top: formImageButton.bottom;
        anchors.topMargin: 6;
        iconsize: 14;
        labeltext: RuntimeData.formingContinuous ? "Непрерывное формирование включено" : "Непрерывное формирование выключено";
        boldness: true;
        onClicked: ioHandler.formContinuously();
        z: 99;
    }
    Text {
        id: diskSpaceText;
        color: UX.textWhite;
        font.capitalization: Font.MixedCase;
        font.pixelSize: 12;
        anchors.top: continuousFormButton.bottom;
        anchors.topMargin: 6;
        textFormat: Text.RichText
        text: "<b>Хранилище изображений заполнено на <i>" + Number(RuntimeData.freeDiskSpace / RuntimeData.totalDiskSpace).toFixed(0) +
              "%</i></b>. Свободно " + Number(RuntimeData.freeDiskSpace / (10 * 1024 * 1024)).toFixed(1) + " Гб из " + Number(RuntimeData.totalDiskSpace / (10 * 1024 * 1024)).toFixed(1);
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
        style: Text.Raised;
    }
}
