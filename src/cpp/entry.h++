#pragma once

#include <Definitions>
#include <QtCore/QObject>

class Entry : public QObject
{
    Q_OBJECT

    public:
        explicit Entry(QObject* parent = nullptr);
};
