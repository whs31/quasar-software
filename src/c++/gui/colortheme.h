#pragma once

#include <map>
#include <QtCore/QObject>

namespace GUI
{
  namespace internal
  {
    class ColorThemeWrapper : public QObject
    {
      Q_OBJECT

      public:
        enum Color
        {
          BaseShade,
          Surface,
          Overlay,
          Subtext,
          Text,
          Lavender,
          PrimaryDark,
          Primary,
          PrimaryLight,
          PrimaryLightest,
          Accent,
          Red,
          Pink,
          Maroon,
          Rosewater,
          Orange,
          Yellow,
          Green,
          Mauve
        };
        Q_ENUM(Color)

        explicit ColorThemeWrapper(QObject* parent = nullptr);
        ~ColorThemeWrapper() override = default;

        Q_INVOKABLE QString color(Color key) const noexcept;
        void set(const std::map<Color, QString>& theme_dict) noexcept;

        std::map<QString, Color> keyMap =
          {
            {"base_shade", BaseShade},
            {"surface", Surface},
            {"overlay", Overlay},
            {"subtext", Subtext},
            {"text", Text},
            {"lavender", Lavender},
            {"primary_dark", PrimaryDark},
            {"primary", Primary},
            {"primary_light", PrimaryLight},
            {"primary_lightest", PrimaryLightest},
            {"accent", Accent},
            {"red", Red},
            {"pink", Pink},
            {"maroon", Maroon},
            {"rosewater", Rosewater},
            {"orange", Orange},
            {"yellow", Yellow},
            {"green", Green},
            {"mauve", Mauve}
          };

      private:
        std::map<Color, QString> m_activeTheme;
    };
  } // internal
} // GUI

#include <QtCore/QMetaType>
Q_DECLARE_METATYPE(GUI::internal::ColorThemeWrapper*)

namespace GUI
{
  class ColorTheme : public QObject
  {
    Q_OBJECT
      Q_PROPERTY(internal::ColorThemeWrapper* active MEMBER m_wrapper NOTIFY activeChanged)
      Q_PROPERTY(QString activeThemeName READ activeThemeName WRITE setActiveThemeName NOTIFY activeThemeNameChanged)
      Q_PROPERTY(QStringList themeList MEMBER m_themeList NOTIFY themeListChanged)

    public:
      static ColorTheme* get();
      ~ColorTheme() override = default;

      void set(const std::map<internal::ColorThemeWrapper::Color, QString>& dict) noexcept;
      [[nodiscard]] QString activeThemeName() const; void setActiveThemeName(const QString&);

    signals:
      void activeChanged(); // needs to be emitted explicitly.
      void activeThemeNameChanged();
      void themeListChanged();

    private:
      explicit ColorTheme(QObject* parent = nullptr);
      ColorTheme(const ColorTheme&);
      ColorTheme& operator=(const ColorTheme&);

      void scanThemes() noexcept;
      void apply() noexcept;

    private:
      internal::ColorThemeWrapper* m_wrapper;
      QString m_activeThemeName;
      QStringList m_themeList;
      std::map<QString, QString> m_files; // name, filename
  };
} // GUI