#pragma once

#include <definitions.h++>
#include <QtCore/QObject>

namespace Debug
{
    class ImGuiConsole : public QObject
    {
        Q_OBJECT

        public:
            explicit ImGuiConsole(QObject* parent = nullptr);
            __qml void frame();
    };
}// namespace Debug;

