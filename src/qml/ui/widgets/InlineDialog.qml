import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import UX 1.0

Rectangle {
    id: dialogBase;
	width: 24
	height: 22
    opacity: 0.6;
    color: UX.primaryDarker;
    radius: 5;
	border.color: UX.primaryDark;
    z: 100;

	FontLoader { id: fnt; source: "qrc:/fonts/SofiaSans-SemiBold.ttf"; }

    RoundButton {
        id: roundButton
        width: 28
        height: 28
        radius: 2
        text: "X"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        rightPadding: 0
        leftPadding: 0
        bottomPadding: 0
        topPadding: 0
        icon.cache: true
        font.pointSize: 7
		font.family: fnt.name;
		font.bold: true;
		font.capitalization: Font.AllUppercase;
        Material.background: UX.errorDark;
        hoverEnabled: false;
        scale: 1
        z: 100
		display: AbstractButton.IconOnly;
        icon.color: UX.textWhite;
		icon.source: "qrc:/icons/close.png";
		icon.width: 8;
		icon.height: 8;
		flat: true;
		highlighted: false;
        anchors.rightMargin: -2;
        onClicked: {
            remove();
        }
    }
}
