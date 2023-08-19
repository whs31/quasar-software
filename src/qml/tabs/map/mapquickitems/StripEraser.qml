import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15
import QtQuick.Layouts 1.15

import QuaSAR.API 1.0

import Notifications 1.0

MapQuickItem {
    anchorPoint.x: width / 2
    anchorPoint.y: height / 2
    z: 19
    visible: true
    enabled: visible

    Behavior on coordinate { CoordinateAnimation { duration: 125; easing.type: Easing.Linear; } }
    Material.background: "#50181926"

    sourceItem: Rectangle {
       height: 100
       width: 100
       radius: height / 2
       color: theme.maroon
       opacity: 0.5
       border {
           width: 5
           color: theme.red
       }
    }
}
