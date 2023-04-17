import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

//import "widgets" as Widgets

Window { id: root;
    width: 640;
    height: 480;
    visible: true;
    Component.onCompleted: showFullScreen();
    color: "black"

    //Widgets.ConsoleWidget { id: debugConsole; }
}
