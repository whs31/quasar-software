import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "widgets" as Widgets
import "layouts" as Layouts
import "tabs" as Tabs

Window { id: root;
    width: 640;
    height: 480;
    visible: true;
    Component.onCompleted: showFullScreen();
    color: "black"

    Widgets.DebugConsole { id: debugConsole; }
}
