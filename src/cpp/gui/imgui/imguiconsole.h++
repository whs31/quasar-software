#pragma once

#include <definitions.h++>
#include <QtCore/QObject>

namespace Debug
{
    class ImGuiConsole : public QObject
    {
        Q_OBJECT
        constexpr __global int FRAMERATE = 10;
        constexpr __global int GRAPH_SECONDS_COUNT = 30;
        constexpr __global int GRAPH_SIZE = FRAMERATE * GRAPH_SECONDS_COUNT;

        static int skip_frames;
        bool set_up = false;

        QString telsock_data;
        float telsock_graph_data[GRAPH_SIZE] = { };
        int telsock_load_size = 0;

        QString execdsock_data;
        float execdsock_graph_data[GRAPH_SIZE] = { };
        int execdsock_load_size = 0;

        QString feedbacksock_data;
        float feedbacksock_graph_data[GRAPH_SIZE] = { };
        int feedbacksock_load_size = 0;

        QString tcpsock_data;
        float tcpsock_graph_data[GRAPH_SIZE] = { };
        int tcpsock_load_size = 0;

        public:
            explicit ImGuiConsole(QObject* parent = nullptr);

            __qml void frame();
            __qml void telsockAppend(const QString& string);
            __qml void execdsockAppend(const QString& string);
            __qml void feedbacksockAppend(const QString& string);
            __qml void tcpsockAppend(const QString& string);

        private:
            void setup();
    };
}// namespace Debug;

