import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Controls.Material 2.15

import LPVL.Charts 1.0
import ImageProcessing 1.0
import Theme 1.0

Window {
    Material.theme: Material.Dark;
    Material.accent: Theme.color("color1");
    Material.primary: Theme.color("accent");
    Material.foreground: Theme.color("light0");
    Material.background: Theme.color("dark1");

    width: 900;
    height: 500;

    color: Theme.color("dark0");
    modality: Qt.NonModal;
    title: "Матрица полосового изображения";

    LPVLMatrixPlot { id: plot;
        anchors.fill: parent;
    }

    Connections {
        target: ImageProcessing;
        function onStripVector8bit(vec, r, c)
        {
            plot.set(vec, r, c);
            show();
        }
    }
}
