/**
 * \ingroup sdk_network
 * \class QuasarSDK::RemoteData CRemoteData.h <QuasarSDK/Networking/CRemoteData.h>
 * \brief Класс-хранилище для данных, связанных с РЛС.
 * \details Хранит текущие значения загруженности диска на РЛС,
 * доступности IPv4 адресов модулей РЛС
 * и предоставляет доступ к ним для движка QML и мета-объектной
 * системы.
 */

#include "CRemoteData.h"
#include <QtCore/QMetaType>

namespace QuasarSDK
{
  /// \brief Создает новый объект RemoteData с указанным родителем.
  RemoteData::RemoteData(QObject* parent)
      : QObject(parent)
      , m_storageSpace(0)
      , m_pings({Enums::Idle, Enums::Idle, Enums::Idle, Enums::Idle, Enums::Idle})
      , m_downloadProgress(0)
      , m_recordingStrip(false)
  {
    qRegisterMetaType<Enums::PingStatus>("Enums::PingStatus");
    qRegisterMetaType<QList<Enums::PingStatus>>("QList<Enums::PingStatus>");
  }

    /**
     * \property RemoteData::storageSpace
     * \brief Предоставляет значение свободного места на диске РЛС.
     * \details Значение лежит в диапазоне от 0 до 100.
     * Свойство доступно только для чтения.
     */
   float RemoteData::storageSpace() const { return m_storageSpace; }
   void RemoteData::setStorageSpace(float o) {
     if(m_storageSpace == o)
       return;
     m_storageSpace = o;
     emit storageSpaceChanged();
   }

    /**
     * \property RemoteData::pings
     * \brief Предоставляет список состояний доступности модулей РЛС.
     * \details Свойство доступно только для чтения.
     */
   QList<Enums::PingStatus> RemoteData::pings() const { return m_pings; }
   void RemoteData::setPings(const QList<Enums::PingStatus>& o) {
     m_pings = o;
     emit pingsChanged();
   }

   /**
    * \property RemoteData::downloadProgress
    * \brief Предоставляет значение процента загрузки больших данных с РЛС.
    */
   float RemoteData::downloadProgress() const { return m_downloadProgress; }
   void RemoteData::setDownloadProgress(float o) {
     if(m_downloadProgress == o)
       return;
     m_downloadProgress = o;
     emit downloadProgressChanged();
   }

   /**
    * \property RemoteData::isRecordingStrip
    * \brief Предоставляет состояние записи полосового изображения.
    */
   bool RemoteData::isRecordingStrip() const { return m_recordingStrip; }
   void RemoteData::setRecordingStrip(bool o) {
     if(m_recordingStrip == o)
       return;
     m_recordingStrip = o;
     emit recordingStripChanged();
   }

} // QuasarSDK
