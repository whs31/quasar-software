#pragma once

#include <QtCore/QObject>

namespace Application
{
  class UpdateManager;
  class QuickUtils;
}

namespace Networking
{
  class HTTPDownloader;
}

class QuaSAR : public QObject
{
  Q_OBJECT

  public:
    explicit QuaSAR(QObject* parent = nullptr);

  signals:
    void scheduleClose();

  private:
    Q_SLOT void passTCPData(const QByteArray& data, const QString& name) noexcept;
    Q_SLOT void passUDPData(const QByteArray& data) noexcept;

    Q_SLOT static void closeApplication() noexcept;

  private:
    Application::UpdateManager* m_updateManager;
    Application::QuickUtils* m_quickUtils;
    Networking::HTTPDownloader* m_httpDownloader;
};
