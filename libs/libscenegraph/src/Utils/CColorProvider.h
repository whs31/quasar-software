/**
 *  \file CColorProvider.h
 *  \author Дмитрий Рязанцев
 *  \date 11.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <map>
#include <array>
#include <QtCore/QObject>
#include <QtGui/QColor>

using std::map;
using std::array;

namespace Scenegraph::Utils
{
  /**
   * \ingroup legacy
   * \brief Класс, предоставляющий палитру контрастных цветов.
   * \details Для использования класс необходимо зарегистрировать в QML либо как
   * тип, либо как синглтон. Предпочтительнее регистрировать класс как одиночный тип:
   * \code {.cpp}
     qmlRegisterType<Scenegraph::Utils::ColorProvider>("Scenegraph.Extras", 1, 0, "ColorProvider");
   * \endcode
   *
   * После этого необходимо импортировать тип в QML и создать объект:
   * \code {.py}
     import Scenegraph.Extras 1.0

     Item {
        ColorProvider {
            id: provider
            theme: ColorProvider.Light
            behavior: ColorProvider.RandomCycle
        }

        // Пример получения цвета:
        ListView {
            model: 100
            delegate: Rectangle {
                width: 100
                height: 100
                color: provider.next()
            }
        }
     }
     \endcode

     Пример с разными значениями DistributionBehavior:
     \image html sg_colorprovider.jpg
   */
  class ColorProvider : public QObject
  {
    Q_OBJECT

    /**
     * \brief Текущая тема цветовой палитры.
     * \details **Эта функция принудительно вызывает reset() при записи в свойство.**
     * \see theme, setTheme, themeChanged
     */
    Q_PROPERTY(ThemeVariant theme READ theme WRITE setTheme NOTIFY themeChanged)

    /**
     * \brief Текущее поведение при вызове функции next().
     * \details **Эта функция принудительно вызывает reset() при записи в свойство.**
     * \see behavior, setBehavior, behaviorChanged
     */
    Q_PROPERTY(DistributionBehavior behavior READ behavior WRITE setBehavior NOTIFY behaviorChanged)

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
        Lavender,         ///< <span style="background:#7287fd">Лавандовый.</span>

        Max = Lavender,   ///< Максимальное значение перечисления.
        Min = Rosewater   ///< Минимальное значение перечисления.
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
        RandomCycle,      ///< При вызове функции next() будет возвращен **случайный** цвет из палитры. Он может повторяться.
        OrderedTint,      ///< При вызове функции next() будет возвращен **следующий по порядку** цвет из палитры. Когда палитра закончится, цвета в ней будут слегка изменены и снова будут браться из ее начала.
        RandomTint        ///< При вызове функции next() будет возвращен **случайный** цвет из палитры. Если такой цвет был выдан ранее, он будет изменен.
      };

      Q_ENUM(ThemeVariant)
      Q_ENUM(BaseColor)
      Q_ENUM(DistributionBehavior)

      /// \brief Создает объект с указанным родителем.
      explicit ColorProvider(QObject* parent = nullptr);

      /**
       * \brief Возвращает цвет согласно текущему поведению DistributionBehavior.
       * \note Эта функция доступна в QML через мета-объектную систему.
       * \see reset, behavior, setBehavior, DistributionBehavior
       * \return Цвет в шестнадцатеричном формате (e. g. <tt>#FF00FF</tt>).
       */
      Q_INVOKABLE [[nodiscard]] QString next() const;

      /**
       * \brief Возвращает указанный цвет из палитры.
       * \details *Эта функция не увеличивает внутренний счетчик.*
       * \param base_color - тип цвета.
       * \note Эта функция доступна в QML через мета-объектную систему.
       * \see BaseColor
       * \return Цвет в шестнадцатеричном формате (e. g. <tt>#FF00FF</tt>).
       */
      Q_INVOKABLE [[nodiscard]] QString exactColor(BaseColor base_color) const;

      /**
       * \brief Сбрасывает внутренний счетчик выданных цветов.
       * \note Эта функция доступна в QML через мета-объектную систему.
       * \see next
       */
      Q_INVOKABLE void reset() noexcept;

      [[nodiscard]] ThemeVariant theme() const;           ///< Возвращает текущую тему цветовой палитры.
      void setTheme(ThemeVariant var);                    ///< Устанавливает текущую тему цветовой палитры. **Эта функция принудительно вызывает reset()**.

      [[nodiscard]] DistributionBehavior behavior() const;///< Возвращает текущее поведение при вызове функции next().
      void setBehavior(DistributionBehavior var);         ///< Устанавливает текущее поведение при вызове функции next(). **Эта функция принудительно вызывает reset()**.

      /**
       * \brief Устанавливает пользовательскую палитру для выбранной темы палитры.
       * \param new_palette - новая палитра с цветами. Палитра должна содержать все цвета из перечисления BaseColor.
       * \param palette_type - тип палитры. См. ThemeVariant.
       */
      void setPalette(const map<BaseColor, QColor>& new_palette, ThemeVariant palette_type);

    signals:
      void themeChanged();
      void behaviorChanged();

    private:
      map<BaseColor, QColor> m_dark_palette;
      map<BaseColor, QColor> m_light_palette;

      ThemeVariant m_currentTheme;
      DistributionBehavior m_currentBehavior;

      struct CPIterator
      {
        int loop;
        int count;
      };

      mutable CPIterator m_it;
      mutable array<bool, Max> m_exclude_list;
  };
} // Scenegraph::Utils
