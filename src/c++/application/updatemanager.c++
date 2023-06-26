#include "updatemanager.h"
#include <QtCore/QEventLoop>
#include <QtCore/QDebug>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>

namespace Application
{

  UpdateManager::UpdateManager(QObject* parent)
    : QObject(parent)
    , m_fetchUrl("http://195.133.13.123:8090")
    , m_downloadUrl("http://ya.ru")
    , m_projectVersion(PROJECT_VERSION)
    , m_status(false)
  {}

  void UpdateManager::setFetchUrl(const QString& url) noexcept
  {
    m_fetchUrl = url;
  }

  void UpdateManager::setDownloadUrl(const QString& url) noexcept
  {
    m_downloadUrl = url;
  }

  void UpdateManager::fetch() noexcept
  {
    QEventLoop loop;
    QNetworkAccessManager accessManager;
    QNetworkRequest request(m_fetchUrl);
    QNetworkReply* reply = accessManager.get(request);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QByteArray buffer = reply->readAll();
    qDebug() << "$ " << buffer << m_projectVersion;
  }

  bool UpdateManager::status() const { return m_status; }
  void UpdateManager::setStatus(bool other)
  {
    if(m_status == other)
      return;
    m_status = other;
    emit statusChanged();
  }

} // Application