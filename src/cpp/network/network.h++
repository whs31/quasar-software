#pragma once

#include <QtCore/QObject>

namespace Network
{
    class Network : public QObject
    {
        Q_OBJECT
        static Network* instance;

        public:
            static Network* get(QObject* parent = nullptr);

            signals:

        private:
            explicit Network(QObject *parent = nullptr);
    };
} // namespace Network;
