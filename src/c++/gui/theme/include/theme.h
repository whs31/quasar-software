#pragma once

#include <QtCore/QObject>
#include <QtCore/QHash>
#include <LPVL/Global>
#include <vector>

namespace GUI
{
  class ThemePrivate;
  class Theme : public QObject
  {
    Q_OBJECT
    Q_DECLARE_PRIVATE(Theme)

    public:
      static Theme* get();
      ~Theme() override = default;

      Q_INVOKABLE QString color(QString key);
      Q_INVOKABLE QString colorText(const QString& text, const QString& theme_color_name);

    signals:
      void colorsChanged();

    protected:
      ThemePrivate* const d_ptr;

    private:
      explicit Theme(QObject* parent = nullptr);
      Theme(const Theme&);
      Theme& operator=(const Theme&);
  };
} // namespace GUI;
