import QtQuick 2.15
import Theme 1.0

Item {
    property real fl_Latitude: 0.0;
    property real fl_Longitude: 0.0;
    property real fl_Altitude: 0.0;
    property real fl_SeaAltitude: 0.0;
    property real fl_Velocity: 0.0;
    property real fl_Direction: 0.0;
    property int i_SatellitesCount: 0;
    property real fl_ConnectionDelay: 0.0;
    property real fl_RemoteDiskSpace: 0.0;

    width: 915;
    height: 46;

    Image { id: ico_LatIcon;
        width: 16;
        height: 16;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.topMargin: 6;
        source: "qrc:/icons/bottombar/latitude.png";
    }

    Text { id: txt_Lat;
        color: Theme.color("light0");
        font.weight: Font.ExtraBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: "ШИРОТА:";
        width: 75;
        height: 12;
        anchors.top: ico_LatIcon.top;
        anchors.topMargin: 2;
        anchors.left: ico_LatIcon.right;
        anchors.leftMargin: 5;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Text { id: txt_LatValue;
        color: Theme.color("light0");
        font.weight: Font.DemiBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: Number(fl_Latitude).toFixed(7) + "° N";
        width: 100;
        height: 12;
        anchors.top: txt_Lat.top;
        anchors.left: txt_Lat.right;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Image { id: ico_LonIcon;
        width: 16;
        height: 16;
        anchors.left: parent.left;
        anchors.top: ico_LatIcon.bottom;
        anchors.topMargin: 2;
        source: "qrc:/icons/bottombar/longitude.png";
    }

    Text { id: txt_Lon;
        color: Theme.color("light0");
        font.weight: Font.ExtraBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: "ДОЛГОТА:";
        width: 75;
        height: 12;
        anchors.top: ico_LonIcon.top;
        anchors.topMargin: 2;
        anchors.left: ico_LonIcon.right;
        anchors.leftMargin: 5;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Text { id: txt_LonValue;
        color: Theme.color("light0");
        font.weight: Font.DemiBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: Number(fl_Longitude).toFixed(7) + "° E";
        width: 100;
        height: 12;
        anchors.top: txt_Lon.top;
        anchors.left: txt_Lon.right;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }
}
