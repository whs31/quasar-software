/**
 *  \file CRemoteData.h
 *  \author Дмитрий Рязанцев
 *  \date 06.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QObject>
#include <QtCore/QList>
#include "network_enums.h"

namespace QuasarSDK
{
  class RemoteData : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(float storageSpace READ storageSpace WRITE setStorageSpace NOTIFY storageSpaceChanged)
    Q_PROPERTY(QList<int> pings READ pings WRITE setPings NOTIFY pingsChanged)
    Q_PROPERTY(float downloadProgress READ downloadProgress WRITE setDownloadProgress NOTIFY downloadProgressChanged)
    Q_PROPERTY(bool isRecordingStrip READ isRecordingStrip WRITE setRecordingStrip NOTIFY recordingStripChanged)

    // status properties here
    Q_PROPERTY(float voltagePrimary READ voltagePrimary WRITE setVoltagePrimary NOTIFY voltagePrimaryChanged)
    Q_PROPERTY(float voltageSecondary READ voltageSecondary WRITE setVoltageSecondary NOTIFY voltageSecondaryChanged)
    Q_PROPERTY(bool commutatorConnected READ commutatorConnected WRITE setCommutatorConnected NOTIFY commutatorConnectedChanged)
    Q_PROPERTY(QList<bool> commutatorChannels READ commutatorChannels WRITE setCommutatorChannels NOTIFY commutatorChannelsChanged)
    Q_PROPERTY(bool commutatorSignal READ commutatorSignal WRITE setCommutatorSignal NOTIFY commutatorSignalChanged)
    Q_PROPERTY(int commutatorError READ commutatorError WRITE setCommutatorError NOTIFY commutatorErrorChanged)
    Q_PROPERTY(bool emitting READ emitting WRITE setEmitting NOTIFY emittingChanged)
    Q_PROPERTY(bool forming READ forming WRITE setForming NOTIFY formingChanged)
    Q_PROPERTY(bool jetsonOnline READ jetsonOnline WRITE setJetsonOnline NOTIFY jetsonOnlineChanged)
    Q_PROPERTY(bool execdEnabled READ execdEnabled WRITE setExecdEnabled NOTIFY execdEnabledChanged)
    Q_PROPERTY(bool transmitting READ transmitting WRITE setTransmitting NOTIFY transmittingChanged)

    public:
      explicit RemoteData(QObject* parent = nullptr);

      [[nodiscard]] float storageSpace() const; void setStorageSpace(float);
      [[nodiscard]] QList<int> pings() const; void setPings(const QList<int>&);
      [[nodiscard]] float downloadProgress() const; void setDownloadProgress(float);
      [[nodiscard]] bool isRecordingStrip() const; void setRecordingStrip(bool);

      [[nodiscard]] float voltagePrimary() const; void setVoltagePrimary(float);
      [[nodiscard]] float voltageSecondary() const; void setVoltageSecondary(float);
      [[nodiscard]] bool commutatorConnected() const; void setCommutatorConnected(bool);
      [[nodiscard]] QList<bool> commutatorChannels() const; void setCommutatorChannels(const QList<bool>&);
      [[nodiscard]] bool commutatorSignal() const; void setCommutatorSignal(bool);
      [[nodiscard]] int commutatorError() const; void setCommutatorError(int);
      [[nodiscard]] bool emitting() const; void setEmitting(bool);
      [[nodiscard]] bool forming() const; void setForming(bool);
      [[nodiscard]] bool jetsonOnline() const; void setJetsonOnline(bool);
      [[nodiscard]] bool execdEnabled() const; void setExecdEnabled(bool);
      [[nodiscard]] bool transmitting() const; void setTransmitting(bool);

    signals:
      void storageSpaceChanged();
      void pingsChanged();
      void downloadProgressChanged();
      void recordingStripChanged();
      void voltagePrimaryChanged();
      void voltageSecondaryChanged();
      void commutatorConnectedChanged();
      void commutatorChannelsChanged();
      void commutatorSignalChanged();
      void commutatorErrorChanged();
      void emittingChanged();
      void formingChanged();
      void jetsonOnlineChanged();
      void execdEnabledChanged();
      void transmittingChanged();

    private:
      float m_storageSpace;
      QList<int> m_pings;
      float m_downloadProgress;
      bool m_recordingStrip;

      float m_voltagePrimary;
      float m_voltageSecondary;
      bool m_commutatorConnected;
      QList<bool> m_commutatorChannels;
      bool m_commutatorSignal;
      int m_commutatorError;
      bool m_emitting;
      bool m_forming;
      bool m_jetsonOnline;
      bool m_execdEnabled;
      bool m_transmitting;
  };
} // QuasarSDK

#include <QtCore/QMetaType>
Q_DECLARE_METATYPE(QuasarSDK::RemoteData*)