#pragma once

#include <QtCore/QObject>

class QNetworkReply;
class QNetworkAccessManager;

namespace Networking
{
  class HTTPDownloader : public QObject
  {
    Q_OBJECT
      Q_PROPERTY(float progress READ progress WRITE setProgress NOTIFY progressChanged)
      Q_PROPERTY(int downloadedBytes READ downloadedBytes WRITE setDownloadedBytes NOTIFY downloadedBytesChanged)
      Q_PROPERTY(int totalBytes READ totalBytes WRITE setTotalBytes NOTIFY totalBytesChanged)

    public:
      explicit HTTPDownloader(QObject* parent);

      Q_INVOKABLE void download(const QString& url) noexcept;
      Q_INVOKABLE void cache(const QString& destination) noexcept;

      [[nodiscard]] QByteArray data() const;

      [[nodiscard]] float progress() const; void setProgress(float);
      [[nodiscard]] int downloadedBytes() const; void setDownloadedBytes(int);
      [[nodiscard]] int totalBytes() const; void setTotalBytes(int);

    signals:
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