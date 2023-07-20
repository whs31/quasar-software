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

    public:
      explicit RemoteData(QObject* parent = nullptr);

      [[nodiscard]] float storageSpace() const; void setStorageSpace(float);
      [[nodiscard]] QList<int> pings() const; void setPings(const QList<int>&);
      [[nodiscard]] float downloadProgress() const; void setDownloadProgress(float);
      [[nodiscard]] bool isRecordingStrip() const; void setRecordingStrip(bool);

    signals:
      void storageSpaceChanged();
      void pingsChanged();
      void downloadProgressChanged();
      void recordingStripChanged();

    private:
      float m_storageSpace;
      QList<int> m_pings;
      float m_downloadProgress;
      bool m_recordingStrip;
  };
} // QuasarSDK

#include <QtCore/QMetaType>
Q_DECLARE_METATYPE(QuasarSDK::RemoteData*)