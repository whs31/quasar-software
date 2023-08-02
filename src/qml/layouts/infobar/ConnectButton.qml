import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Config 1.0

import QuaSAR.API 1.0

RowLayout {
    id: layout_SharedToolbar;
    spacing: -2

    RoundButton {
        id: button_Connect;
        property bool timeout: false;

        enabled: !timeout;
        opacity: enabled ? 1 : 0.5;
        font.family: root.mainfont;
        radius: 4;
        icon.source: NetworkAPI.isConnected ? "qrc:/icons/vector/network/wifi_off.svg"
                                            : "qrc:/icons/vector/network/wifi.svg"
        icon.color: ColorTheme.active.color(ColorTheme.Dark)
        text: NetworkAPI.isConnected ? "Отключение" : "Подключение";
        Material.elevation: 30;
        Material.foreground: ColorTheme.active.color(ColorTheme.Dark)
        Material.background: NetworkAPI.isConnected ? ColorTheme.active.color(ColorTheme.Red)
                                                    : ColorTheme.active.color(ColorTheme.PrimaryLightest)
        Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }
        Behavior on opacity { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }

        Layout.preferredHeight: 36

        onPressed: {
            let flag = NetworkAPI.isConnected

            NetworkAPI.stop()
            NetworkAPI.statusSocket.stop()

            if(!flag)
            {
                NetworkAPI.start(NetworkAPI.stringify(Settings.io.parameter("ip/de10"), Settings.io.parameter("port/telemetry-request")),
                                 NetworkAPI.stringify(Settings.io.parameter("ip/computer"), Settings.io.parameter("port/telemetry-receive")),
                                 Settings.io.parameter("misc/telemetry-frequency"),
                                 NetworkAPI.stringify(Settings.io.parameter("ip/de10"), Settings.io.parameter("port/execd")),
                                 NetworkAPI.stringify(Settings.io.parameter("ip/computer"), Settings.io.parameter("port/stdout")),
                                 NetworkAPI.stringify(Settings.io.parameter("ip/computer"), Settings.io.parameter("port/tcp")),
                                 NetworkAPI.stringify(Settings.io.parameter("ip/computer"), Settings.io.parameter("port/strip"))
                                 );
                NetworkAPI.statusSocket.setRequestAddress(NetworkAPI.stringify(Settings.io.parameter("ip/de10"), Settings.io.parameter("port/telemetry-request")))
                NetworkAPI.statusSocket.start(NetworkAPI.stringify(Settings.io.parameter("ip/computer"), Settings.io.parameter("port/status")))
                NetworkAPI.execd.execute(Net.RemoteStorageStatus)
                timeout = true;
                disconnect_timer.start();
            }
        }

        Timer { id: disconnect_timer; running: false; repeat: false; interval: 3000; onTriggered: {
                if(!NetworkAPI.isConnected)
                {
                    NetworkAPI.stop()
                    NetworkAPI.statusSocket.stop()
                }
                button_Connect.timeout = false;
            }
        }
    }

    BusyIndicator {
        enabled: !button_Connect.enabled;
        opacity: enabled ? 1 : 0;
        height: 40;
        implicitWidth: enabled ? 30 : 0;
        running: enabled;

        Layout.preferredHeight: 30
        Behavior on opacity { NumberAnimation { easing.type: Easing.Linear; duration: 300; } }
        Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 300; } }
    }
}

