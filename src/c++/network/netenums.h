#pragma once

#include <QtCore/QObject>

//! @namespace Namespace network-related classes.
namespace Networking
{
    class Enums : public QObject
    {
        Q_OBJECT

        public:
            //! @enum Enumeration for ping status.
            //! @memberof Success - ping finished successfully.
            //! @memberof DelayedSuccess - ping finished successfully
            //!           with significant delay.
            //! @memberof Timeout - ping failed with timeout.
            //! @memberof Idle - ping doesn't started yet.
            enum PingStatus
            {
                Success,
                DelayedSuccess,
                Timeout,
                Idle
            };

            enum ArgumentCategory
            {
                Form,
                Focus,
                Reform
            };

            enum NetworkCommand
            {
                FormImage,
                FocusImage,
                ReformImage,
                RemoteStorageStatus,
                ClearRemoteStorage,
                Reboot,
                Poweroff
            };

            Q_ENUM(PingStatus)
            Q_ENUM(ArgumentCategory)
            Q_ENUM(NetworkCommand)
    };
} // Network

#include <QtCore/QMetaType>
Q_DECLARE_METATYPE(Networking::Enums*)
Q_DECLARE_METATYPE(Networking::Enums::PingStatus)
Q_DECLARE_METATYPE(Networking::Enums::ArgumentCategory)
Q_DECLARE_METATYPE(Networking::Enums::NetworkCommand)
