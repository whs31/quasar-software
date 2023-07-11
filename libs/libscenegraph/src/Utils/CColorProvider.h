/**
 *  \file CColorProvider.h
 *  \author Дмитрий Рязанцев
 *  \date 11.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <map>
#include <QtCore/QObject>
#include <QtCore/QColor>

using std::map;

namespace Scenegraph::Utils
{
  /**
   * \brief Класс, предоставляющий палитру контрастных цветов.
   */
  class ColorProvider : public QObject
  {
    Q_OBJECT

    public:
      /// \brief Перечисление базовых цветов палитры. Применимо как к темной, так и к светлой палитре.
      enum BaseColor
      {
        Rosewater,        ///< <span style="background:#dc8a78">Светло-розовый.</span>
        Flamingo,         ///< <span style="background:#dd7878">Темно-розовый.</span>
        Pink,             ///< <span style="background:#ea76cb">Розовый.</span>
        Mauve,            ///< <span style="background:#8839ef">Фиолетовый.</span>
        Red,              ///< <span style="background:#d20f39">Красный.</span>
        Maroon,           ///< <span style="background:#e64553">Бледно-красный.</span>
        Peach,            ///< <span style="background:#fe640b">Оранжевый.</span>
        Yellow,           ///< <span style="background:#df8e1d">Желтый.</span>
        Green,            ///< <span style="background:#40a02b">Зеленый.</span>
        Teal,             ///< <span style="background:#179299">Бирюзовый.</span>
        Sky,              ///< <span style="background:#04a5e5">Голубой.</span>
        Sapphire,         ///< <span style="background:#209fb5">Сапфировый.</span>
        Blue,             ///< <span style="background:#1e66f5">Синий.</span>
        Lavender          ///< <span style="background:#7287fd">Лавандовый.</span>
      };

      /// \brief Перечисление вариаций цветовой палитры.
      enum ThemeVariant
      {
        Dark,             ///< Темная палитра для темной темы.
        Light             ///< Светлая палитра для светлой темы.
      };

      /// \brief Перечисление поведения класса при вызове функции next().
      enum DistributionBehavior
      {
        OrderedCycle,     ///< При вызове функции next() будет возвращен **следующий по порядку** цвет из палитры. Когда палитра закончится, цвета снова будут браться из нее с начала.
        RandomCycle,      ///< При вызове функции next() будет возвращен **случайный** цвет из палитры. Он не будет повторяться до тех пор, пока палитра не закончится.
        OrderedTint,      ///< При вызове функции next() будет возвращен **следующий по порядку** цвет из палитры. Когда палитра закончится, цвета в ней будут слегка изменены и снова будут браться из ее начала.
        RandomTint        ///< При вызове функции next() будет возвращен **случайный** цвет из палитры. Когда палитра закончится, цвета будут изменены и цикл начнется заново.
      };

      Q_ENUM(ThemeVariant)
      Q_ENUM(BaseColor)
      Q_ENUM(DistributionBehavior)

      explicit ColorProvider(QObject* parent = nullptr);

      [[nodiscard]] ThemeVariant theme() const;           ///< Возвращает текущую тему цветовой палитры.
      void setTheme(ThemeVariant var);                    ///< Устанавливает текущую тему цветовой палитры. **Эта функция принудительно вызывает reset()**.

      [[nodiscard]] DistributionBehavior behavior() const;///< Возвращает текущее поведение при вызове функции next().
      void setBehavior(DistributionBehavior var);         ///< Устанавливает текущее поведение при вызове функции next(). **Эта функция принудительно вызывает reset()**.

      /**
       * \brief Возвращает
       * \return
       */
      [[nodiscard]] QString next() const;


    private:
      map<BaseColor, QColor> m_dark_palette;
      map<BaseColor, QColor> m_light_palette;

  };
} // Scenegraph::Utils
