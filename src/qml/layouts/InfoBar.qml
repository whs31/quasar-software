import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import QuaSAR.API 1.0

import Theme 1.0
import "./infobar" as Info

ToolBar {
    Flickable
    {
        width: parent.width
        height: parent.height
        clip: true
        interactive: true
        contentWidth: 1920
        flickableDirection: Flickable.HorizontalFlick

        RowLayout {
            Info.ConnectionIndicator {
                offlineMode: NetworkAPI.offlineMode
                connected: NetworkAPI.isConnected
                delay: NetworkAPI.currentNetworkDelay
            }

            Info.ConnectButton { }

            ToolSeparator { }

            Info.NavigationBar {
                latitude: NetworkAPI.telemetry.position.latitude
                longitude: NetworkAPI.telemetry.position.longitude
                altitude: NetworkAPI.telemetry.position.altitude - NetworkAPI.telemetry.seaLevel
                seaAltitude: NetworkAPI.telemetry.position.altitude
                velocity: NetworkAPI.telemetry.velocity.x
                direction: NetworkAPI.telemetry.eulerAxes.y
                satellitesCount: NetworkAPI.telemetry.satellites
            }

            ToolSeparator { }
            Info.StorageWidget { }

            ToolSeparator { }
        }
    }
}
