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

    Rectangle { id: rect_Separator1;
        width: 2;
        height: 32;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: txt_LatValue.right;
        color: Theme.color("dark3");
    }

    Image { id: ico_AltIcon;
        width: 16;
        height: 16;
        anchors.left: rect_Separator1.right;
        anchors.leftMargin: 8;
        anchors.top: parent.top;
        anchors.topMargin: 6;
        source: "qrc:/icons/bottombar/altitude.png";
    }

    Text { id: txt_Alt;
        color: Theme.color("light0");
        font.weight: Font.ExtraBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: "ВЫСОТА:";
        width: 140;
        height: 12;
        anchors.top: ico_AltIcon.top;
        anchors.topMargin: 2;
        anchors.left: ico_AltIcon.right;
        anchors.leftMargin: 5;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Text { id: txt_AltValue;
        color: Theme.color("light0");
        font.weight: Font.DemiBold;
        font.family: root.s_FontMain;
        font.pixelSize: 16;
        text: Number(fl_Altitude).toFixed(0) + " м";
        width: 56;
        height: 16;
        anchors.top: txt_Alt.top;
        anchors.topMargin: -4;
        anchors.left: txt_Alt.right;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Image { id: ico_SeaIcon;
        width: 16;
        height: 16;
        anchors.left: ico_AltIcon.left;
        anchors.top: ico_AltIcon.bottom;
        anchors.topMargin: 2;
        source: "qrc:/icons/bottombar/sea-level.png";
    }

    Text { id: txt_Sea;
        color: Theme.color("light0");
        font.weight: Font.DemiBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: "НАД УРОВНЕМ МОРЯ:";
        width: 140;
        height: 12;
        anchors.top: ico_SeaIcon.top;
        anchors.topMargin: 2;
        anchors.left: ico_SeaIcon.right;
        anchors.leftMargin: 5;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Text { id: txt_SeaValue;
        color: Theme.color("light0");
        font.weight: Font.DemiBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: Number(fl_SeaAltitude).toFixed(0) + " м";
        width: 56;
        height: 12;
        anchors.top: txt_Sea.top;
        anchors.left: txt_Sea.right;
        anchors.leftMargin: 2;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }
}
