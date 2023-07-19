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

  private slots:
    static void closeApplication() noexcept;

  private:
    Application::UpdateManager* m_updateManager;
    Application::QuickUtils* m_quickUtils;
    Networking::HTTPDownloader* m_httpDownloader;
};
