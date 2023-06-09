import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Theme 1.0

Pane {
    Material.elevation: 30;

    Column {
        RoundButton { id: button_ZoomIn;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/google-material/zoom-in.png";
            icon.color: Theme.color("light0");
            Material.elevation: 30;
            Material.background: Theme.color("dark2");
            onPressed: maptab_root.zoomLevel += 0.5;
        }

        RoundButton { id: button_ZoomOut;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/google-material/zoom-out.png";
            icon.color: Theme.color("light0");
            Material.elevation: 30;
            Material.background:  Theme.color("dark2");
            onPressed: maptab_root.zoomLevel -= 0.5;
        }
    }
}
