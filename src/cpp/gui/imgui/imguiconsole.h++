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

        private:
            bool show_demo_window = true;
            bool show_another_window = false;
    };
}// namespace Debug;
