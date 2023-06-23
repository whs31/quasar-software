#pragma once

#include <map>
#include <QtCore/QObject>

// @todo class needs to self-register self with attribute constructor
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

      private:
        std::map<Color, QString> m_activeTheme;
        std::map<Color, QString> m_keyMap =
          {
            {BaseShade, "base_shade"},
            {Surface, "surface"},
            {Overlay, "overlay"},
            {Subtext, "subtext"},
            {Text, "text"},
            {Lavender, "lavender"},
            {PrimaryDark, "primary_dark"},
            {Primary, "primary"},
            {PrimaryLight, "primary_light"},
            {PrimaryLightest, "primary_lightest"},
            {Accent, "accent"},
            {Red, "red"},
            {Pink, "pink"},
            {Maroon, "maroon"},
            {Rosewater, "rosewater"},
            {Orange, "orange"},
            {Yellow, "yellow"},
            {Green, "green"},
            {Mauve, "mauve"}
          };
    };
  } // internal

  class ColorTheme : public QObject
  {
    Q_OBJECT
      Q_PROPERTY(internal::ColorThemeWrapper* active MEMBER m_wrapper NOTIFY activeChanged)
      Q_PROPERTY(QString activeThemeName READ activeThemeName WRITE setActiveThemeName NOTIFY activeThemeNameChanged)
      Q_PROPERTY(QStringList themeList MEMBER m_themeList NOTIFY themeListChanged)

    public:
      explicit ColorTheme(QObject* parent = nullptr);
      ~ColorTheme() override = default;

      void set(const std::map<internal::ColorThemeWrapper::Color, QString>& dict) noexcept;
      [[nodiscard]] QString activeThemeName() const; void setActiveThemeName(const QString&);

    signals:
      void activeChanged(); // needs to be emitted explicitly.
      void activeThemeNameChanged();
      void themeListChanged();

    private:
      internal::ColorThemeWrapper* m_wrapper;
      QString m_activeThemeName;
      QStringList m_themeList;
  };
} // GUI

#include <QtCore/QMetaType>
Q_DECLARE_METATYPE(GUI::internal::ColorThemeWrapper*)