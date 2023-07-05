/**
 *  \file quasarsdk_execdargumentparser.h
 *  \author Дмитрий Рязанцев
 *  \date 06.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QMap>
#include <QtCore/QObject>

namespace QuasarSDK
{
  /**
   * \brief Тип данных для работы с сервисом \c execd.
   * \details ExecdArgument предоставляет полезные конструкторы
   * и функции для абстракции над аргументами сервиса. Вместо
   * приведения различных типов данных к строке вручную, используйте
   * этот тип.
   * \note После вызова конструктора тип аргумента не может быть изменен.
   * Инициализируйте аргументы значениями по умолчанию, а не пустыми конструкторами.
   */
  struct ExecdArgument
  {
    /// \brief Константа, определяющая, сколько знаков после запятой сохраняется после приведения числа к строке.
    constexpr static const int FLOATING_POINT_PRECISION = 1;

    /// \brief Тип аргумента.
    enum ArgumentType
    {
      Float,    ///< Число с плавающей точкой.
      Integer,  ///< Целое число.
      String    ///< Строка.
    };

    /// \brief Создает пустой аргумент с типом ArgumentType::String.
    ExecdArgument();

    /// \brief Создает аргумент целочисленного типа из данного числа.
    ExecdArgument(int);

    /// \brief Создает аргумент вещественного типа из данного числа.
    ExecdArgument(float);

    /// \brief Создает аргумент строкового типа из данной строки.
    ExecdArgument(QString);

    /**
     * \brief Устанавливает значение в аргумент.
     * \details Автоматически преобразовывает данное значение \c QVariant
     * к типу аргумента, указанному при его создании.
     * \param v - значение для присвоения.
     */
    void set(const QVariant& v);

    /// \brief Текущее значение аргумента в виде строки.
    QString value;

    /// \brief Тип значения аргумента, присвоенный при создании.
    ArgumentType type;
  };

  class ExecdArgumentParser
  {

  };
} // QuasarSDK
