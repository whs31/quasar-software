#pragma once

#include <QtCore/QObject>

namespace Application
{
  class UpdateManager;
}

namespace Networking
{
  class HTTPDownloader;
}

class Entry : public QObject
{
  Q_OBJECT

  public:
    explicit Entry(QObject* parent = nullptr);

  signals:
    void scheduleClose();

  private slots:
    void closeApplication() noexcept;

  private:
    Application::UpdateManager* m_updateManager;
    Networking::HTTPDownloader* m_httpDownloader;
};
