#ifndef TMARKER_H
#define TMARKER_H

#include <QObject>
#include <QColor>

enum MarkerIcon : short int {
    GoogleDefaultMarker,
    SARImage
};

class TMarker : public QObject
{
    Q_OBJECT
public:
    explicit TMarker(QObject *parent = nullptr);
    QColor color = Qt::white;
    QString name = "Новый маркер";
    short int icon = MarkerIcon::GoogleDefaultMarker;
    qreal latitude = 0;
    qreal longitude = 0;
    bool scalable = false;
    bool save = true;
    qreal anchorX = 0;
    qreal anchorY = 0;

signals:

};

#endif // TMARKER_H
