import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import "qrc:/qml/ui" as UI
import RuntimeData 1.0

Item {
    ColumnLayout
    {
        spacing: -2;
        Text {
            id: pitchText;
            color: "#dae1e5";
            font.capitalization: Font.MixedCase;
            font.pixelSize: 12;
            textFormat: Text.RichText
            text: "<b>Тангаж: <i>" + RuntimeData.pitch + "</i></b>";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
            style: Text.Raised;
        }
        Text {
            id: rollText;
            color: "#dae1e5";
            font.capitalization: Font.MixedCase;
            font.pixelSize: 12;
            textFormat: Text.RichText
            text: "<b>Крен: <i>" + RuntimeData.roll + "</i></b>";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
            style: Text.Raised;
        }
        Text {
            id: yawText;
            color: "#dae1e5";
            font.capitalization: Font.MixedCase;
            font.pixelSize: 12;
            textFormat: Text.RichText
            text: "<b>Рысканье: <i>" + RuntimeData.yaw + "</i></b>";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
            style: Text.Raised;
        }
        Text {
            id: throttleText;
            color: "#dae1e5";
            font.capitalization: Font.MixedCase;
            font.pixelSize: 12;
            textFormat: Text.RichText
            text: "<b>Тяга: <i>" + RuntimeData.throttle + "%</i></b>";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
            style: Text.Raised;
        }
    }
}
