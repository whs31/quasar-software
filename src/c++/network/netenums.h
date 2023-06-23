/*!
 *  @file netenums.h
 *  @author Dmitry Ryazancev
 *  @date 22.06.2023
 */

#pragma once

#include <QtCore/QObject>

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
        Success,            //!< Успешное выполнение команды ping.
        DelayedSuccess,     //!< Команда выполнена с задержкой.
        Timeout,            //!< Команда не выполнена.
        Idle                //!< Выполнение команды не было запрошено.
      };

      //! @brief Перечисление категорий аргументов параметров формирования.
      enum ArgumentCategory
      {
        Form,               //!< Аргументы формирования.
        Focus,              //!< Аргументы фокусировки.
        Reform              //!< Аргументы переформирования.
      };

      //! @brief Перечисление встроенных в приложение команд.
      enum NetworkCommand
      {
        FormImage,          //!< Запуск формирования телескопического изображения.
        FocusImage,         //!< Фокусировка телескопического изображения.
        StartStrip,         //!< Запуск съемки полосового изображения.
        StopStrip,          //!< Остановка съемки полосового изображения.
        ReformImage,        //!< Переформирование телескопического изображения.
        RemoteStorageStatus,//!< Запрос информации о дисковом хранилище на РЛС.
        ClearRemoteStorage, //!< Очистка дискового хранилища на РЛС.
        Reboot,             //!< Запрос на перезагрузку систем РЛС.
        Poweroff            //!< Запрос на выключение систем РЛС.
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
