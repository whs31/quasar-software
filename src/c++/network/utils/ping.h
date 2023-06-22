#pragma once

#include <vector>
#include <QtCore/QObject>
#include <QtCore/QStringList>

class QTimer;
class QProcess;

using std::vector;

//! @namespace Namespace network-related classes.
namespace Networking
{
    //! @class Class for checking connection to
    //!        specified IPv4 address via ICMP.
    class Pinger : public QObject
    {
        Q_OBJECT

        public:
            //! @brief Constructs new Pinger object with
            //!        given parent.
            explicit Pinger(QObject* parent = nullptr);
            ~Pinger();

            //! @brief Starts pinging given address, until Pinger
            //!        is not destroyed or stopped.
            //! @param interval - ms interval between pings. 0 means auto.
            //! @param address - IPv4 address to ping.
            //! @param args - ping command line arguments.
            void start(uint32_t interval, const QString& address, const vector<QString> args = {});

            //! @brief Stops pinging address.
            void stop() noexcept;

            signals:
                //! @brief Emitted when ping is finished.
                //! @param status - Network::PingStatus result code.
                void result(int status);

        private:
            private slots:
                void ping();
                void recv();

        private:
            QProcess* ch;
            QTimer* t;
            QString addr;
            QStringList m_args;
    };
} // Network
