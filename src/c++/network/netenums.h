#pragma once

#include <QtCore/QObject>

//! @brief Пространство имен для работы с сетевыми подключениями к РЛС.
namespace Networking
{
    //! @brief Класс-обёртка для общих перечислений пространства имён #Networking.
    class Enums : public QObject
    {
        Q_OBJECT

        public:
            //! @brief Перечисление статус-кодов команды ping.
            enum PingStatus
            {
                Success,
                DelayedSuccess,
                Timeout,
                Idle
            };

            //! @brief Перечисление категорий аргументов параметров формирования.
            enum ArgumentCategory
            {
                Form,
                Focus,
                Reform
            };

            //! @brief Перечисление встроенных в приложение команд.
            enum NetworkCommand
            {
                FormImage,
                FocusImage,
                StartStrip,
                StopStrip,
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
Q_DECLARE_METATYPE(Networking::Enums::PingStatus)
Q_DECLARE_METATYPE(Networking::Enums::ArgumentCategory)
Q_DECLARE_METATYPE(Networking::Enums::NetworkCommand)
