/**
 *  \file execdargumentlist.h
 *  \author Dmitry Ryazancev
 *  \date 30.06.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QMap>
#include <QtCore/QObject>

namespace Networking
{
  /**
   * \brief Type for working with \c execd arguments.
   * \details ExecdArgument provides useful constructors
   * and functions for abstracting \c execd arguments of
   * different literal types. Instead of using plain integers
   * and floats and manually converting them to string, use this
   * type instead.
   */
  struct ExecdArgument
  {
    /// \brief Constant describing how many numbers will remain in float after point.
    constexpr static const int FLOATING_POINT_PRECISION = 1;

    /// \brief Enum for type of argument.
    enum ArgumentType
    {
      Float,    ///< Floating-point type.
      Integer,  ///< Integer type.
      String    ///< String type.
    };

    /// \brief Constructs empty argument with #ArgumentType::String.
    ExecdArgument();

    /// \brief Constructs argument from given integer.
    ExecdArgument(int);

    /// \brief Constructs argument from given float.
    ExecdArgument(float);

    /// \brief Constructs argument from given string.
    ExecdArgument(QString);

    /**
     * \brief Sets value to argument.
     * \details Automatically converts given \c QVariant value
     * to type of argument, assigned on it's construction.
     * \param v - variant value to assign.
     */
    void set(const QVariant& v);

    /// \brief Current string value of argument type.
    QString value;

    /// \brief Type of argument, assigned on it's construction.
    ArgumentType type;
  };

  /**
   * \brief Class for storing and processing \c execd arguments.
   * \details Provides useful functions for automatic conversion
   * values to \c execd arguments. Stores 3 different argument lists
   * for form, reform and focus mode respectively.
   *
   * List of all \c execd arguments:
   * <table>
     <caption id="multi_row">Arguments table</caption>
     <tr><th>Description    <th>Argument key   <th>Value type   <th>Default value   <th>Range   <th>Note
     <tr><td>Name of .bin file without file extension</td><td>-f</td><td>String</td><td>m1</td><td></td><td></td></tr>
     <tr><td>Probing mode</td><td>-m</td><td>Integer</td><td>1</td><td>1..4, 6..7</td><td></td></tr>
     <tr><td>Time shift relative to start</td><td>-t</td><td>Float</td><td>1</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Brightness of resulting image</td><td>-b</td><td>Float</td><td>0</td><td>0 - ∞</td><td>0 means auto</td></tr>
     <tr><td>Altitude of UAV, meters</td><td>-e</td><td>Float</td><td>-1</td><td>any</td><td>Sea-level. -1 means auto </td></tr>
     <tr><td>Speed of UAV, km/h</td><td>-v</td><td>Float</td><td>-1</td><td>0 - ∞</td><td>-1 means auto</td></tr>
     <tr><td>Speed interpolation mode</td><td>-i</td><td>Integer</td><td>0</td><td>0 or 1</td><td>Treated as boolean</td></tr>
     <tr><td>SAR synthesis time</td><td>--Ts</td><td>Float</td><td>1</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Strip synthesis time</td><td>--Tstrip</td><td>Float</td><td>1</td><td>0 - ∞</td><td>Only for strip images</td></tr>
     <tr><td>Frequency interpolation factor (x)</td><td>--kR</td><td>Integer</td><td>1</td><td>1..4</td><td></td></tr>
     <tr><td>Frequency interpolation factor (y)</td><td>--kL</td><td>Integer</td><td>1</td><td>1..4</td><td></td></tr>
     <tr><td>JPEG compression quality</td><td>--jq</td><td>Integer</td><td>80</td><td>0 - 100</td><td></td></tr>
     <tr><td>Discrete size (x) in meters</td><td>--dx</td><td>Float</td><td>1</td><td>0 - ∞</td><td>Must be equal with --dy</td></tr>
     <tr><td>Discrete size (y) in meters</td><td>--dy</td><td>Float</td><td>1</td><td>0 - ∞</td><td>Must be equal with --dx</td></tr>
     <tr><td>Distance to near edge of image, meters</td><td>--x0</td><td>Float </td><td>100</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Frame shift (y)</td><td>--y0</td><td>Float</td><td>0</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Image length (x), meters</td><td>--lx</td><td>Float</td><td>2'000</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Image length (y), meters</td><td>--ly</td><td>Float</td><td>400</td><td>0 - ∞</td><td>Unused</td></tr>
     <tr><td>Path to storage in SAR</td><td>--ip</td><td>String</td><td>./img/</td><td></td><td></td></tr>
     <tr><td>Address for fsend service to send result</td><td>--remote</td><td>String</td><td>None</td><td></td><td>e.g. 192.168.1.10:25565</td></tr>
     <tr><td>Computer type</td><td>--DSP</td><td>String</td><td>DSP_FFTW</td><td>DSP_FFTW or DSP_CUDA</td><td></td></tr>
     <tr><td>Vertical mirroring of image</td><td>--mirror</td><td>String</td><td>False</td><td>True or False</td><td>Booleans must start with capital letter</td></tr>
     <tr><td>Altitude of ground in start point</td><td>--e0</td><td>Float</td><td>0</td><td>0 - ∞</td><td></td></tr>
     <tr><td>OX coordinate for focusing</td><td>--px</td><td>Float</td><td>-1</td><td>any</td><td></td></tr>
     <tr><td>OY coordinate for focusing</td><td>--py</td><td>Float</td><td>-1</td><td>any</td><td></td></tr>
     <tr><td>Length of square side for focusing, meters</td><td>--ls</td><td>Float</td><td>50</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Minimal value of speed prediction for focusing</td><td>--vmin</td><td>Float</td><td>-1</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Maximal value of speed prediction for focusing</td><td>--vmax</td><td>Float</td><td>-1</td><td>0 - ∞</td><td></td></tr>
     <tr><td>Number of speed predictions</td><td>--ni</td><td>Integer</td><td>10</td><td>1 - ∞</td><td></td></tr></tbody></table>
   */
  class ExecdArgumentList : public QObject
  {
    Q_OBJECT

      /**
       * \brief Default values for forming mode in \c execd service.
       * \note In future releases will be replaced with .json file.
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

      /// @brief Значения аргументов фокусировки \b execd по умолчанию
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
      /// \brief Constructs new instance of ExecdArgumentList with given parent.
      explicit ExecdArgumentList(QObject* parent = nullptr);

      /**
       * \brief Returns arguments for Form mode.
       * \details Function returns string, containing all of
       * changed Form mode arguments inside brackets.
       * \return String with changed arguments.
       */
      [[nodiscard]] QString getFormArguments() const noexcept;

      /**
       * \brief Returns arguments for Reform mode.
       * \details Function returns string, containing all of
       * changed Reform mode arguments inside brackets.
       * \return String with changed arguments.
       */
      [[nodiscard]] QString getReformArguments() const noexcept;

      /**
       * \brief Returns arguments for Focus mode.
       * \details Function returns string, containing all of
       * changed Focus mode arguments inside brackets.
       * \return String with changed arguments.
       */
      [[nodiscard]] QString getFocusArguments() const noexcept;

      /// \brief Container for arguments in Form mode.
      QMap<QString, ExecdArgument> argument_list = defaults;

      /// \brief Container for arguments in Reform mode.
      QMap<QString, ExecdArgument> reform_argument_list = defaults;

      /// \brief Container for arguments in Focus mode.
      QMap<QString, ExecdArgument> focus_argument_list = focus_defaults;
  };
} // Network
