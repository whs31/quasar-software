/**
 *  \file httpdownloader.h
 *  \author Dmitry Ryazancev
 *  \date 30.06.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QObject>

class QNetworkReply;
class QNetworkAccessManager;

namespace Networking
{
  /**
   * \brief Class for downloading files by HTTP/HTTPS protocol.
   * \details Class is used to easily download and save files
   * from Internet.
   * Provides bindings to QML.
   * \extends QObject
   */
  class HTTPDownloader : public QObject
  {
      /**
       * \property progress
       * \brief Download progress in normalized percentage.
       * \par %progress, setProgress, progressChanged
       *
       * \property downloadedBytes
       * \brief Currently downloaded bytes count.
       * \par %downloadedBytes, setDownloadedBytes, downloadedBytesChanged
       *
       * \property totalBytes
       * \brief Total bytes count to download.
       * \par %totalBytes, setTotalBytes, totalBytesChanged
       */
    Q_OBJECT
      Q_PROPERTY(float progress READ progress WRITE setProgress NOTIFY progressChanged)
      Q_PROPERTY(int downloadedBytes READ downloadedBytes WRITE setDownloadedBytes NOTIFY downloadedBytesChanged)
      Q_PROPERTY(int totalBytes READ totalBytes WRITE setTotalBytes NOTIFY totalBytesChanged)

    public:
      /// \brief Constructs new HTTPDownloader object with given parent.
      explicit HTTPDownloader(QObject* parent);

      /**
       * \brief Tries to download file from given URL.
       * \details Downloads file, if it is possible,
       * and stores in inside this class instance.
       * \param url - URL to download. Can be either HTTP or HTTPS.
       * \note Can be invoked from QML via Qt meta-object system.
       */
      Q_INVOKABLE void download(const QString& url) noexcept;

      /**
       * \brief Saves all currently downloaded data in file.
       * \param destination - absolute path to target file.
       * \note Can be invoked from QML via Qt meta-object system.
       */
      Q_INVOKABLE void cache(const QString& destination) noexcept;

      [[nodiscard]] QByteArray data() const;

      [[nodiscard]] float progress() const; void setProgress(float);
      [[nodiscard]] int downloadedBytes() const; void setDownloadedBytes(int);
      [[nodiscard]] int totalBytes() const; void setTotalBytes(int);

    signals:
      /// \brief Emitted when downloading file is finished.
      void downloadFinished();

      void progressChanged();
      void downloadedBytesChanged();
      void totalBytesChanged();

    private slots:
      void fileDownloaded(QNetworkReply* reply);
      void progressReply(qint64 recv, qint64 total);

    private:
      QNetworkAccessManager* m_accessManager;
      QByteArray m_data;

      float m_progress;
      int m_downloadedBytes;
      int m_totalBytes;
  };
} // Networking