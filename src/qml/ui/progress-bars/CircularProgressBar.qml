import QtQuick 2.15
import DynamicResolution 1.0

Canvas {
    id: canvas;
    width: fixed_width;
    height: fixed_height;
    antialiasing: true;

    property color fill_color: "orange";
    property color base_color: "lightblue";

    property real centerWidth: width / 2;
    property real centerHeight: height / 2;
    property real radius: (Math.min(canvas.width, canvas.height) / 2) - 5 * DynamicResolution.kw;

    property real fixed_width: 240 * DynamicResolution.kw;
    property real fixed_height: 240 * DynamicResolution.kw;

    property real minimumValue: 0;
    property real maximumValue: 100;
    property real currentValue: 33;

    // this is the angle that splits the circle in two arcs
    // first arc is drawn from 0 radians to angle radians
    // second arc is angle radians to 2*PI radians
    property real angle: (currentValue - minimumValue) / (maximumValue - minimumValue) * (end_angle - start_angle);

    property real start_angle: -Math.PI / 2;
    property real end_angle: Math.PI / 2;
    property real line_width: 5;

    onFill_colorChanged: requestPaint()
    onBase_colorChanged: requestPaint()
    onMinimumValueChanged: requestPaint()
    onMaximumValueChanged: requestPaint()
    onCurrentValueChanged: requestPaint()

    onPaint: {
        var ctx = getContext("2d");
        ctx.save();
        ctx.clearRect(0, 0, canvas.width, canvas.height);
//        if (mouseArea.pressed) {
//            ctx.beginPath();
//            ctx.lineWidth = 1;
//            ctx.fillStyle = Qt.lighter(canvas.base_color, 1.25);
//            ctx.arc(canvas.centerWidth,
//                    canvas.centerHeight,
//                    canvas.radius,
//                    0,
//                    2*Math.PI);
//            ctx.fill();
//        }
        ctx.beginPath();
        ctx.lineWidth = line_width;
        ctx.strokeStyle = fill_color;
        ctx.arc(canvas.centerWidth,
                canvas.centerHeight,
                canvas.radius,
                start_angle + canvas.angle,
                start_angle + end_angle);
        ctx.stroke();
        ctx.beginPath();
        ctx.lineWidth = line_width;
        ctx.strokeStyle = canvas.base_color;
        ctx.arc(canvas.centerWidth,
                canvas.centerHeight,
                canvas.radius,
                canvas.start_angle,
                canvas.start_angle + canvas.angle);//(end_angle / (2 * Math.PI))
        ctx.stroke();
        ctx.restore();
    }
}
