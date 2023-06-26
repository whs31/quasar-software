#include "httpdownloader.h"
#include <QtCore/QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

namespace Networking
{
  HTTPDownloader::HTTPDownloader(QObject* parent)
    : QObject(parent)
    , m_accessManager(new QNetworkAccessManager(this))
    , m_progress(0)
    , m_downloadedBytes(0)
    , m_totalBytes(1)
  {
    connect(m_accessManager, &QNetworkAccessManager::finished, this, &HTTPDownloader::fileDownloaded);
  }

  void HTTPDownloader::download(const QString& url) noexcept
  {
    m_data.clear();
    qDebug() << "[HTTP DOWNLOADER] Requested download from" << url;
    QNetworkRequest request(url);
    QNetworkReply* m_reply = m_accessManager->get(request);
    connect(m_reply, &QNetworkReply::downloadProgress, this, [this](qint64 recv, qint64 total)
    {
      this->setDownloadedBytes(recv);
      this->setTotalBytes(total);
      if(total != 0)
        this->setProgress(recv / total);
    });
  }

  void HTTPDownloader::cache(const QString& destination) noexcept
  {
    QFile file(destination);
    if(not file.open(QIODevice::WriteOnly))
    {
      qCritical() << "[HTTP DOWNLOADER] Error opening" << destination;
      return;
    }

    file.write(m_data);
    file.close();
  }

  QByteArray HTTPDownloader::data() const
  {
    return m_data;
  }

  void HTTPDownloader::fileDownloaded(QNetworkReply* reply)
  {
    m_data = reply->readAll();
    reply->deleteLater();
    emit downloadFinished();
  }

  float HTTPDownloader::progress() const { return m_progress; }
  void HTTPDownloader::setProgress(float o)
  {
    if(m_progress == o)
      return;
    m_progress = o;
    emit progressChanged();
  }

  int HTTPDownloader::downloadedBytes() const { return m_downloadedBytes; }
  void HTTPDownloader::setDownloadedBytes(int o)
  {
    if(m_downloadedBytes == o)
      return;
    m_downloadedBytes = o;
    emit downloadedBytesChanged();
  }

  int HTTPDownloader::totalBytes() const { return m_totalBytes; }
  void HTTPDownloader::setTotalBytes(int o)
  {
    if(m_totalBytes == o)
      return;
    m_totalBytes = o;
    emit totalBytesChanged();
  }

} // Networking