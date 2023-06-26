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
    #ifndef Q_OS_WIN
    setStatus(false);
    return;
    #endif

    QEventLoop loop;
    QNetworkAccessManager accessManager;
    QNetworkRequest request(m_fetchUrl);
    QNetworkReply* reply = accessManager.get(request);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QByteArray buffer = reply->readAll();

    auto split_ss = QString(buffer).split('.');
    auto split_cs = m_projectVersion.split('.');
    if(split_ss.length() != 3 or split_cs.length() != 3)
    {
      qCritical() << "[UPDATE MANAGER] Incorrect server result";
      return;
    }

    int server_side = 0;
    int client_side = 0;
    try
    {
      server_side += split_ss[0].toInt() * 10'000;
      server_side += split_ss[1].toInt() * 100;
      server_side += split_ss.last().toInt();

      client_side += split_cs[0].toInt() * 10'000;
      client_side += split_cs[1].toInt() * 100;
      client_side += split_cs.last().toInt();
    }
    catch(...)
    {
      qCritical() << "[UPDATE MANAGER] Safe block failed";
    }

    if(client_side < server_side)
      setStatus(true);
    else
      setStatus(false);

    qDebug() << "$ [UPDATE MANAGER] Server-side version:" << buffer << "[" << server_side << "]";
    qDebug() << "$ [UPDATE MANAGER] Current version:" << m_projectVersion << "[" << client_side << "]";
    qDebug() << "$ [UPDATE MANAGER] Update required:" << status();
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