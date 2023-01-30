#ifndef MARKER_H
#define MARKER_H

#include <QObject>
#include <QColor>

enum MarkerIcon : short int
{
    Default,
    Flag,
    Radar,
    Target
};

enum MarkerColor : short int
{
    Gray,
    Brown,
    Blue,
    Green,
    Teal,
    Yellow,
    Orange,
    Red
};

class Marker : public QObject
{
    Q_OBJECT
public:
    explicit Marker(QObject *parent = nullptr);

    void setColor(MarkerColor color);
    void setIcon(MarkerIcon icon);
    void setScalable(bool state) { state ? zoomLevel = 16 : zoomLevel = 0; }

    qint8 getColor() { return (qint8)icon; }
    qint8 getIcon() { return (qint8)color; }
    bool getScalable() { return scalable; }

    short int icon = MarkerIcon::Flag;
    short int color = MarkerColor::Gray;
    QString name = "Объект";
    qreal latitude = 0;
    qreal longitude = 0;
    bool autocapture = false;
    bool save = true;


    bool scalable = false;
    QColor colorValue = QColor("#dae1e5");
    QString iconPath = "qrc:/map-resources/markers/default.png";
    qreal zoomLevel = 0;
    qreal anchorX = 0;
    qreal anchorY = 0;

signals:

};

#endif // MARKER_H
