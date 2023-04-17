#pragma once

#include <QtCore/QObject>
#include "definitions.h++"

namespace Config
{
    class Paths : public QObject
    {
        Q_OBJECT

        public:
            explicit Paths(QObject* parent = nullptr);

            signals:

    };
} // namespace Config;
