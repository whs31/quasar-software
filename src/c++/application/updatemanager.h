#pragma once

#include <QtCore/QObject>

namespace Application
{
  class UpdateManager : public QObject
  {
    Q_OBJECT
      Q_PROPERTY(bool status READ status WRITE setStatus NOTIFY statusChanged)

    public:
      explicit UpdateManager(QObject* parent);

      [[nodiscard]] Q_INVOKABLE QString remoteVersion() const;
      [[nodiscard]] Q_INVOKABLE QString link() const;

      void setFetchUrl(const QString& url) noexcept;

      void fetch() noexcept;

      [[nodiscard]] bool status() const; void setStatus(bool);

    signals:
      void statusChanged();

    private:
      QString m_fetchUrl;
      QString m_projectVersion;
      QString m_remoteVersion;
      QString m_link;

      bool m_status;
  };
} // Application