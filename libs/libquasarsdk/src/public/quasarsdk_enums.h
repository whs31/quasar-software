/**
 *  \file quasarsdk_enums.h
 *  \author Дмитрий Рязанцев
 *  \date 04.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QObject>

namespace QuasarSDK
{
  /**
   * \class QuasarSDK::Enums quasarsdk_enums.h <QuasarSDK/Enums>
   * \brief Класс-обёртка для общих перечислений SDK РЛС "Квазар".
   * \details Предоставляет общие перечисления для использования
   * между различными классами внутри SDK, а также позволяет
   * зарегистрировать их в мета-объектной системе для доступа из
   * движка QML.
   * \extends QObject
   */
  class Enums : public QObject
  {
    Q_OBJECT

    public:
      //! @brief Перечисление статус-кодов команды ping.
      enum PingStatus
      {
        Success,            //!< Успешное выполнение команды \с ping.
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
        SimpleStrip,        //!< Запуск формирования упрощенного полосового изображения.
        StartStrip,         //!< Запуск съемки полосового изображения.
        StopStrip,          //!< Остановка съемки полосового изображения.
        ReformImage,        //!< Переформирование телескопического изображения.
        RemoteStorageStatus,//!< Запрос информации о дисковом хранилище на РЛС.
        ClearRemoteStorage, //!< Очистка дискового хранилища на РЛС.
        Reboot,             //!< Запрос на перезагрузку систем РЛС.
        PowerOff            //!< Запрос на выключение систем РЛС.
      };

      Q_ENUM(PingStatus)
      Q_ENUM(ArgumentCategory)
      Q_ENUM(NetworkCommand)
  };
} // QuasarSDK

#include <QtCore/QMetaType>
Q_DECLARE_METATYPE(QuasarSDK::Enums::PingStatus)
Q_DECLARE_METATYPE(QuasarSDK::Enums::ArgumentCategory)
Q_DECLARE_METATYPE(QuasarSDK::Enums::NetworkCommand)