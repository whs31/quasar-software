/**
  * \struct QuasarSDK::ExecdArgument CExecdArgumentParser.h <QuasarSDK/Networking/CExecdArgumentParser.h>
  * \brief Тип данных для работы с сервисом \c execd.
  * \details ExecdArgument предоставляет полезные конструкторы
  * и функции для абстракции над аргументами сервиса. Вместо
  * приведения различных типов данных к строке вручную, используйте
  * этот тип.
  * \note После вызова конструктора тип аргумента не может быть изменен.
  * Инициализируйте аргументы значениями по умолчанию, а не пустыми конструкторами.
  */

/**
  * \class QuasarSDK::ExecdArgumentParser CExecdArgumentParser.h <QuasarSDK/Networking/CExecdArgumentParser.h>
  * \brief Класс для хранения и обработки аргументов команд сервиса \c execd.
  * \details Предоставляет функции и тип данных для удобной работы с аргументами.
  * Хранит 3 списка аргументов для формирования, фокусировки и переформирования соответственно.
  *
  * Список всех аргументов сервиса:
  * <table>
     <caption id="multi_row">Таблица аргументов сервиса execd</caption>
     <tr><th>Описание    <th>Ключ аргумента   <th>Тип данных   <th>Значение по умолчанию   <th>Диапазон   <th>Примечание
     <tr><td>Имя голограммы (.bin) без расширения</td><td>-f</td><td>String</td><td>m1</td><td></td><td></td></tr>
     <tr><td>Режим зондирования</td><td>-m</td><td>Integer</td><td>1</td><td>1..4, 6..7</td><td></td></tr>
     <tr><td>Смещение по времени</td><td>-t</td><td>Float</td><td>1</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Яркость изображения</td><td>-b</td><td>Float</td><td>0</td><td>0 - ∞</td><td>0 означает автоматически</td></tr>
     <tr><td>Высота БПЛА, м</td><td>-e</td><td>Float</td><td>-1</td><td>any</td><td>От уровня моря. -1 означает автоматически</td></tr>
     <tr><td>Скорость БПЛА, км/ч</td><td>-v</td><td>Float</td><td>-1</td><td>0 - ∞</td><td>-1 означает автоматически</td></tr>
     <tr><td>Режим интерполяции по скорости</td><td>-i</td><td>Integer</td><td>0</td><td>0 или 1</td><td></td></tr>
     <tr><td>Время синтезирования</td><td>--Ts</td><td>Float</td><td>1</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Время синтезирования полосового РЛИ</td><td>--Tstrip</td><td>Float</td><td>1</td><td>0 - ∞</td><td>Только для полосовых РЛИ</td></tr>
     <tr><td>Коэффициент частотной интерполяции (x)</td><td>--kR</td><td>Integer</td><td>1</td><td>1..4</td><td></td></tr>
     <tr><td>Коэффициент частотной интерполяции (y)</td><td>--kL</td><td>Integer</td><td>1</td><td>1..4</td><td></td></tr>
     <tr><td>Качество компрессии JPEG</td><td>--jq</td><td>Integer</td><td>80</td><td>0 - 100</td><td></td></tr>
     <tr><td>Размер дискреты (x) в метрах</td><td>--dx</td><td>Float</td><td>1</td><td>0 - ∞</td><td>Должно совпадать с --dy</td></tr>
     <tr><td>Размер дискреты (y) в метрах</td><td>--dy</td><td>Float</td><td>1</td><td>0 - ∞</td><td>Должно совпадать с --dx</td></tr>
     <tr><td>Расстояние до ближней границы, м</td><td>--x0</td><td>Float </td><td>100</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Смещение кадра (y)</td><td>--y0</td><td>Float</td><td>0</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Размер РЛИ (x), м</td><td>--lx</td><td>Float</td><td>2'000</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Размер РЛИ (y), м</td><td>--ly</td><td>Float</td><td>400</td><td>0 - ∞</td><td>Не используется</td></tr>
     <tr><td>Путь к хранилищу на РЛС</td><td>--ip</td><td>String</td><td>./img/</td><td></td><td></td></tr>
     <tr><td>Адрес для отправки изображения</td><td>--remote</td><td>String</td><td>None</td><td></td><td>e.g. 192.168.1.10:25565</td></tr>
     <tr><td>Тип вычислителя</td><td>--DSP</td><td>String</td><td>DSP_FFTW</td><td>DSP_FFTW или DSP_CUDA</td><td></td></tr>
     <tr><td>Вертикальное отражение РЛИ</td><td>--mirror</td><td>String</td><td>False</td><td>True или False</td><td>Булевая переменная начинается с заглавной буквы</td></tr>
     <tr><td>Высота земли в точке старта</td><td>--e0</td><td>Float</td><td>0</td><td>0 - ∞</td><td></td></tr>
     <tr><td>OX координата точки фокусировки</td><td>--px</td><td>Float</td><td>-1</td><td>произвольное</td><td></td></tr>
     <tr><td>OY координата точки фокусировки</td><td>--py</td><td>Float</td><td>-1</td><td>произвольное</td><td></td></tr>
     <tr><td>Размер стороны квадрата для фокусировки, м</td><td>--ls</td><td>Float</td><td>50</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Минимальное значение скорости для фокусировки</td><td>--vmin</td><td>Float</td><td>-1</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Максимальное значение скорости для фокусировки</td><td>--vmax</td><td>Float</td><td>-1</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Количество гипотез по скорости для фокусировки</td><td>--ni</td><td>Integer</td><td>10</td><td>1 - ∞</td><td></td></tr>
     </table>
  * \extends QObject
  */

#include "CExecdArgumentParser.h"
#include <utility>
#include <QtCore/QVariant>

namespace QuasarSDK
{
  /// \brief Создает объект ExecdArgumentParser с указанным родителем.
  ExecdArgumentParser::ExecdArgumentParser(QObject* parent)
      : QObject(parent)
  {}

  /**
   * \brief Возвращает строку с аргументами для режима формирования.
   * \details Строка обернута в круглые скобки. Строка содержит только
   * те аргументы, чьи значения отличаются от значений по умолчанию.
   * Строка вернет пустые скобки, если все аргументы совпадают с таковыми
   * по умолчанию.
   */
  QString ExecdArgumentParser::formArgumentString() const noexcept
  {
    QString ret = "(";
    bool no_space = true;
    for(const auto& key : formArgumentList.keys())
    {
      if(formArgumentList.value(key).value != defaults.value(key).value)
      {
        if(no_space) {
          ret += (key + " " + formArgumentList.value(key).value);
          no_space = false;
        }
        else
          ret += (" " + key + " " + formArgumentList.value(key).value);
      }
    }
    ret += ")";
    return ret;
  }

  /**
   * \brief Возвращает строку с аргументами для режима переформирования.
   * \details Строка обернута в круглые скобки. Строка содержит только
   * те аргументы, чьи значения отличаются от значений по умолчанию.
   * Строка вернет пустые скобки, если все аргументы совпадают с таковыми
   * по умолчанию.
   */
  QString ExecdArgumentParser::reformArgumentString() const noexcept
  {
    QString ret = "(";
    bool no_space = true;
    for(const auto& key : reformArgumentList.keys())
    {
      if(reformArgumentList.value(key).value != defaults.value(key).value)
      {
        if(no_space) {
          ret += (key + " " + reformArgumentList.value(key).value);
          no_space = false;
        }
        else
          ret += (" " + key + " " + reformArgumentList.value(key).value);
      }
    }
    ret += ")";
    return ret;
  }

  /**
   * \brief Возвращает строку с аргументами для режима фокусировки.
   * \details Строка обернута в круглые скобки. Строка содержит только
   * те аргументы, чьи значения отличаются от значений по умолчанию.
   * Строка вернет пустые скобки, если все аргументы совпадают с таковыми
   * по умолчанию.
   */
  QString ExecdArgumentParser::focusArgumentString() const noexcept
  {
    QString ret = "(";
    bool no_space = true;
    for(const auto& key : focusArgumentList.keys())
    {
      if(focusArgumentList.value(key).value != focus_defaults.value(key).value)
      {
        if(no_space) {
          ret += (key + " " + focusArgumentList.value(key).value);
          no_space = false;
        }
        else
          ret += (" " + key + " " + focusArgumentList.value(key).value);
      }
    }
    ret += ")";
    return ret;
  }

  /**
    * \brief Устанавливает значение в аргумент.
    * \details Автоматически преобразовывает данное значение \c QVariant
    * к типу аргумента, указанному при его создании.
    * \param v - значение для присвоения.
    */
  void ExecdArgument::set(const QVariant& v)
  {
    switch (type)
    {
      case Float: value = QString::number(v.toFloat(), 'f', FLOATING_POINT_PRECISION); break;
      case Integer: value = QString::number(v.toInt()); break;
      case String: value = v.toString(); break;
      default: break;
    }
  }

  /// \brief Создает аргумент строкового типа из данной строки.
  ExecdArgument::ExecdArgument(QString s)
    : value(std::move(s))
    , type(String)
  {}

  /// \brief Создает аргумент вещественного типа из данного числа.
  ExecdArgument::ExecdArgument(float f)
    : value(QString::number(f, 'f', FLOATING_POINT_PRECISION))
    , type(Float)
  {}

  /// \brief Создает аргумент целочисленного типа из данного числа.
  ExecdArgument::ExecdArgument(int i)
    : value(QString::number(i))
    , type(Integer)
  {}

  /// \brief Создает пустой аргумент с типом ArgumentType::String.
  ExecdArgument::ExecdArgument()
    : value("Error")
    , type(String)
  {}
} // QuasarSDK