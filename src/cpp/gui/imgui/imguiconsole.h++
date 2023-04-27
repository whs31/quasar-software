#pragma once

#include <definitions.h++>
#include <QtCore/QObject>

namespace Debug
{
    class ImGuiConsole : public QObject
    {
        Q_OBJECT
        constexpr __global int FRAMERATE = 6;
        constexpr __global int GRAPH_SECONDS_COUNT = 30;
        constexpr __global int GRAPH_SIZE = FRAMERATE * GRAPH_SECONDS_COUNT;
        static int skip_frames;

        QString telsock_data;
        float telsock_graph_data[GRAPH_SIZE] = { };
        int telsock_load_size = 0;

        public:
            explicit ImGuiConsole(QObject* parent = nullptr);

            __qml void frame();
            __qml void telsockAppend(const QString& string);
    };
}// namespace Debug;

