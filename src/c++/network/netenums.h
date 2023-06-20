#pragma once

#include <QtCore/QObject>

//! @namespace Namespace for network-related classes.
namespace Networking
{
    //! @class Provides common network-related enums.
    //! @details Enums are avialable in QML via meta-object system.
    class Enums : public QObject
    {
        Q_OBJECT

        public:
            //! @enum     Enumeration for ping status.
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

            //! @enum Enumeration for execd argument category.
            enum ArgumentCategory
            {
                Form,
                Focus,
                Reform
            };

            //! @enum     Enumeration for execd command type.
            //! @memberof FormImage - asks SAR to form telescopic
            //!           image with arguments.
            //! @memberof FocusImage - asks SAR to focus telescopic
            //!           image at given point and arguments.
            //! @memberof ReformImage - asks SAR to reform existing
            //!           hologram with another set of arguments.
            //! @memberof RemoteStorageStatus - asks SAR about
            //!           remaining disk space.
            //! @memberof ClearRemoteStorage - asks SAR to clear
            //!           disk storage from images and binaries.
            //! @memberof Reboot - forces SAR to reboot itself.
            //! @memberof Poweroff - forces SAR to shutdown itself.
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
