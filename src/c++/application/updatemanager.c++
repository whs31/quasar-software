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
    , m_projectVersion(PROJECT_VERSION)
    , m_status(false)
  {}

  void UpdateManager::setFetchUrl(const QString& url) noexcept
  {
    m_fetchUrl = url;
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

    auto split_reply = QString(buffer).split(';');
    if(split_reply.length() != 3)
    {
      qCritical() << "[UPDATE MANAGER] Incorrect server result";
      return;
    }
    QString server_app, server_version, server_link;
    try
    {
      server_app = split_reply[0];
      server_version = split_reply[1];
      server_link = split_reply.last();
    }
    catch(...)
    {
      qCritical() << "[UPDATE MANAGER] Exception catched";
      return;
    }

    auto split_ss = server_version.split('.');
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
      return;
    }

    if(client_side < server_side)
      setStatus(true);
    else
      setStatus(false);

    m_remoteVersion = server_version;
    m_link = server_link;

    qDebug() << "$ [UPDATE MANAGER] Server-side version:" << server_version << "[" << server_side << "]";
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

  QString UpdateManager::remoteVersion() const
  {
    return m_remoteVersion;
  }

  QString UpdateManager::link() const
  {
    return m_link;
  }

} // Application