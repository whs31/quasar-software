/**
 *  \file CExecdArgumentParser.h
 *  \author Дмитрий Рязанцев
 *  \date 06.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QMap>
#include <QtCore/QObject>

namespace QuasarSDK
{
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

    ExecdArgument();
    explicit ExecdArgument(int);
    explicit ExecdArgument(float);
    explicit ExecdArgument(QString);

    void set(const QVariant& v);

    QString value;      ///< Текущее значение аргумента в виде строки.
    ArgumentType type;  ///< Тип значения аргумента, присвоенный при создании.
  };

  class ExecdArgumentParser : public QObject
  {
    Q_OBJECT

    private:
      /**
       * \brief Значения по умолчанию для режима формирования и переформирования в сервисе \c execd.
       * \deprecated В будущем будет заменено на файл .json.
       */
      QMap<QString, ExecdArgument> defaults = {
          {"-f", ExecdArgument("m1")},
          {"-m", ExecdArgument(1)},
          {"-t", ExecdArgument(1.0f)},
          {"-b", ExecdArgument(0.0f)},
          {"-e", ExecdArgument(-1.0f)},
          {"-v", ExecdArgument(-1.0f)},
          {"-i", ExecdArgument(0)},
          {"--Ts", ExecdArgument(1.0f)},
          {"--Tstrip", ExecdArgument(1.0f)},
          {"--kR", ExecdArgument(1)},
          {"--kL", ExecdArgument(1)},
          {"--jq", ExecdArgument(80)},

          {"--dx", ExecdArgument(1.0f)},
          {"--dy", ExecdArgument(1.0f)},
          {"--x0", ExecdArgument(100.0f)},
          {"--y0", ExecdArgument(0.0f)},
          {"--lx", ExecdArgument(2'000.0f)},
          {"--ly", ExecdArgument(400.0f)},
          {"--ip", ExecdArgument("./img/")},
          {"--remote", ExecdArgument("None")},
          {"--DSP", ExecdArgument("DSP_FFTW")},
          {"--mirror", ExecdArgument("False")},

          {"--e0", ExecdArgument(0.0f)}
      };

      /**
       * \brief Значения аргументов для режима фокусировки по умолчанию.
       * \deprecated В будущем будет заменено на файл .json.
       */
      QMap<QString, ExecdArgument> focus_defaults = {
          {"-f", ExecdArgument("m1")},            // <-
          {"-b", ExecdArgument(0.0f)},            // <-
          {"-e", ExecdArgument(-1.0f)},           // <-
          {"-v", ExecdArgument(-1.0f)},           // <-
          {"--Ts", ExecdArgument(1.0f)},          // <-
          {"--remote", ExecdArgument("None")},    // <-
          {"--e0", ExecdArgument(0.0f)},          // <-

          {"--px", ExecdArgument(-1.0f)},
          {"--py", ExecdArgument(-1.0f)},
          {"--ls", ExecdArgument(50.0f)},
          {"--vmin", ExecdArgument(-1.0f)},
          {"--vmax", ExecdArgument(-1.0f)},
          {"--ni", ExecdArgument(10)},
      };

    public:
      explicit ExecdArgumentParser(QObject* parent = nullptr);

      [[nodiscard]] QString formArgumentString() const noexcept;
      [[nodiscard]] QString reformArgumentString() const noexcept;
      [[nodiscard]] QString focusArgumentString() const noexcept;

      QMap<QString, ExecdArgument> formArgumentList = defaults;       ///< Список аргументов для режима формирования.
      QMap<QString, ExecdArgument> reformArgumentList = defaults;     ///< Список аргументов для режима переформирования.
      QMap<QString, ExecdArgument> focusArgumentList = focus_defaults;///< Список аргументов для режима фокусировки.
  };
} // QuasarSDK
