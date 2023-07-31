/**
 * \ingroup sdk_network
 * \class QuasarSDK::RemoteData CRemoteData.h <QuasarSDK/Networking/CRemoteData.h>
 * \brief Класс-хранилище для данных, связанных с РЛС.
 * \details Хранит текущие значения загруженности диска на РЛС,
 * доступности IPv4 адресов модулей РЛС
 * и предоставляет доступ к ним для движка QML и мета-объектной
 * системы.
 */

#include "remotedata.h"
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
      , m_voltagePrimary(0)
      , m_voltageSecondary(0)
      , m_commutatorConnected(false)
      , m_commutatorChannels({false, false})
      , m_commutatorSignal(false)
      , m_commutatorError(0)
      , m_emitting(false)
      , m_forming(false)
      , m_jetsonOnline(false)
      , m_execdEnabled(false)
      , m_transmitting(false)
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
   QList<int> RemoteData::pings() const { return m_pings; }
   void RemoteData::setPings(const QList<int>& o) {
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

   float RemoteData::voltagePrimary() const { return m_voltagePrimary; }
   void RemoteData::setVoltagePrimary(float x) {
     if(m_voltagePrimary == x)
       return;
     m_voltagePrimary = x;
     emit voltagePrimaryChanged();
   }

  float RemoteData::voltageSecondary() const { return m_voltageSecondary; }
  void RemoteData::setVoltageSecondary(float x) {
    if(m_voltageSecondary == x)
      return;
    m_voltageSecondary = x;
    emit voltageSecondaryChanged();
  }

  bool RemoteData::commutatorConnected() const { return m_commutatorConnected; }
  void RemoteData::setCommutatorConnected(bool x) {
     if(m_commutatorConnected == x)
       return;
     m_commutatorConnected = x;
     emit commutatorConnectedChanged();
   }

   QList<bool> RemoteData::commutatorChannels() const { return m_commutatorChannels; }
   void RemoteData::setCommutatorChannels(const QList<bool>& x) {
     if(m_commutatorChannels == x)
       return;
     m_commutatorChannels = x;
     emit commutatorChannelsChanged();
   }

   bool RemoteData::commutatorSignal() const { return m_commutatorSignal; }
   void RemoteData::setCommutatorSignal(bool x) {
     if(m_commutatorSignal == x)
       return;
     m_commutatorSignal = x;
     emit commutatorSignalChanged();
   }

   int RemoteData::commutatorError() const { return m_commutatorError; }
   void RemoteData::setCommutatorError(int x) {
     if(m_commutatorError == x)
       return;
     m_commutatorError = x;
     emit commutatorErrorChanged();
   }

   bool RemoteData::emitting() const { return m_emitting; }
   void RemoteData::setEmitting(bool x) {
     if(m_emitting == x)
       return;
     m_emitting = x;
     emit emittingChanged();
   }

  bool RemoteData::forming() const { return m_forming; }
  void RemoteData::setForming(bool x) {
    if(m_forming == x)
      return;
    m_forming = x;
    emit formingChanged();
  }

  bool RemoteData::jetsonOnline() const { return m_jetsonOnline; }
  void RemoteData::setJetsonOnline(bool x) {
    if(m_jetsonOnline == x)
      return;
    m_jetsonOnline = x;
    emit jetsonOnlineChanged();
  }

  bool RemoteData::execdEnabled() const { return m_execdEnabled; }
  void RemoteData::setExecdEnabled(bool x) {
    if(m_execdEnabled == x)
      return;
    m_execdEnabled = x;
    emit execdEnabledChanged();
  }

  bool RemoteData::transmitting() const { return m_transmitting; }
  void RemoteData::setTransmitting(bool x) {
    if(m_transmitting == x)
      return;
    m_transmitting = x;
    emit transmittingChanged();
  }
} // QuasarSDK
