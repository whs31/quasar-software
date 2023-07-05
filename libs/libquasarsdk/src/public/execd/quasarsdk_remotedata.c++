/**
  * \class QuasarSDK::RemoteData quasarsdk_remotedata.h <QuasarSDK/Execd/Data>
  * \brief Класс-хранилище для данных, связанных с РЛС.
  * \details Хранит текущие значения загруженности диска на РЛС,
  * доступности IPv4 адресов модулей РЛС
  * и предоставляет доступ к ним для движка QML и мета-объектной
  * системы.
  */

#include "quasarsdk_remotedata.h"

namespace QuasarSDK
{
  /// \brief Создает новый объект RemoteData с указанным родителем.
  RemoteData::RemoteData(QObject* parent)
      : QObject(parent)
      , storageSpace(-1)
      , pings({Enums::Idle, Enums::Idle, Enums::Idle, Enums::Idle, Enums::Idle})
  {}

  /**
   * \property RemoteData::storageSpace
   * \brief Предоставляет значение свободного места на диске РЛС.
   * \details Значение лежит в диапазоне от 0 до 100.
   * Свойство доступно только для чтения.
   */

  /**
   * \property RemoteData::pings
   * \brief Предоставляет список состояний доступности модулей РЛС.
   * \details Свойство доступно только для чтения.
   */
} // QuasarSDK