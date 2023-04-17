#pragma once

#include "../console.h++"
#include <QtCore/QMap>
#include <functional>
#include "definitions.h++"

class ConsolePrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(Console)
    Console* q_ptr;

    QMap<QString, std::function<void()>> command_list = {
        { "quit", [this](){ quit(); } },
    };

    public:
        ConsolePrivate(Console* parent);
        virtual ~ConsolePrivate() = default;

        Q_INVOKABLE void sendCommand(QString command);

        signals:
            __signal appendSignal(const QString& text);

    private:
        void quit();
};
