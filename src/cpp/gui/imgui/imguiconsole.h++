#pragma once

#include <definitions.h++>
#include <QtCore/QObject>

namespace Debug
{
    class ImGuiConsole : public QObject
    {
        Q_OBJECT
        QString telsock_data;

        public:
            explicit ImGuiConsole(QObject* parent = nullptr);

            __qml void frame();
            __qml void telsockAppend(const QString& string);
    };
}// namespace Debug;

