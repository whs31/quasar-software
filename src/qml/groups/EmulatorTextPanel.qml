import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15

import Telemetry 1.0

import Theme 1.0

import "qrc:/qml/ui" as UI

Item {
    ColumnLayout
    {
        spacing: -2;
        Text {
            id: pitchText;
            color: Theme.color("light1");
            font.capitalization: Font.MixedCase;
            font.pixelSize: 12;
            textFormat: Text.RichText
            text: "<b>Тангаж: <i>" + Telemetry.pitch + "°</i></b>";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
            style: Text.Raised;
        }
        Text {
            id: rollText;
            color: Theme.color("light1");
            font.capitalization: Font.MixedCase;
            font.pixelSize: 12;
            textFormat: Text.RichText
            text: "<b>Крен: <i>" + Telemetry.roll + "°</i></b>";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
            style: Text.Raised;
        }
        Text {
            id: yawText;
            color: Theme.color("light1");
            font.capitalization: Font.MixedCase;
            font.pixelSize: 12;
            textFormat: Text.RichText
            text: "<b>Рысканье: <i>" + Telemetry.yaw + "°</i></b>";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
            style: Text.Raised;
        }
        Text {
            id: throttleText;
            color: Theme.color("light1");
            font.capitalization: Font.MixedCase;
            font.pixelSize: 12;
            textFormat: Text.RichText
            text: "<b>Тяга: <i>" + Telemetry.throttle + "%</i></b>";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
            style: Text.Raised;
        }
    }
}
