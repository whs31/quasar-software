#pragma once

#include <QtCore/QObject>
#include "definitions.h++"

class Entry : public QObject
{
    Q_OBJECT

    public:
        explicit Entry(QObject *parent = nullptr);
};
