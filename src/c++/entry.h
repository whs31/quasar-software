#pragma once

#include <QtCore/QObject>

namespace Application
{
  class UpdateManager;
}

class Entry : public QObject
{
  Q_OBJECT

  public:
    explicit Entry(QObject* parent = nullptr);

  private:
    Application::UpdateManager* m_updateManager;
};
