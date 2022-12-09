#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>

class Plotter : public QObject
{
    Q_OBJECT
public:
    explicit Plotter(QObject *parent = nullptr);

signals:

};

#endif // PLOTTER_H
