#pragma once

#include <QtCore/QObject>

class Diagram : public QObject
{
    Q_OBJECT
public:
    explicit Diagram(QObject *parent = nullptr);

signals:

};

