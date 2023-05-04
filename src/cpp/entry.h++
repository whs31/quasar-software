#pragma once

#include <definitions.h>
#include <QtCore/QObject>

class Entry : public QObject
{
    Q_OBJECT

    public:
        explicit Entry(QObject* parent = nullptr);
};
