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
}
