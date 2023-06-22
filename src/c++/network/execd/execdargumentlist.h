#pragma once

#include <QtCore/QMap>
#include <QtCore/QObject>

namespace Networking
{
    struct ExecdArgument
    {
        constexpr static const int FLOATING_POINT_PRECISION = 1;

        enum ArgumentType
        {
            Float,
            Integer,
            String
        };

        ExecdArgument();
        ExecdArgument(int);
        ExecdArgument(float);
        ExecdArgument(QString);

        void set(const QVariant& v);

        QString value;
        ArgumentType type;
    };

    class ExecdArgumentList : public QObject
    {
        Q_OBJECT

        //! @brief Значения аргументов \b execd по умолчанию
        QMap<QString, ExecdArgument> defaults = {
            {"-f", ExecdArgument("m1")},            //!< Имя файла радиоголограммы без расширения.
            {"-m", ExecdArgument(1)},               //!< Режим зондирования [1..4, 6, 7].
            {"-t", ExecdArgument(1.0f)},            //!< Смещение времени начала формирования отн. начала зондирования [0 - ∞].
            {"-b", ExecdArgument(0.0f)},            //!< Яркость РЛИ, 0 - авто [0 - ∞].
            {"-e", ExecdArgument(-1.0f)},           //!< Высота БПЛА отн. уровня моря, -1 - авто, м.
            {"-v", ExecdArgument(-1.0f)},           //!< Скорость БПЛА, -1 - авто, км/ч.
            {"-i", ExecdArgument(0)},               //!< Интерполяция скорости [0, 1] - 0: среднее значение за Ts, 1: интерполированное значение для каждого периода за Ts.
            {"--Ts", ExecdArgument(1.0f)},          //!< Время синтезирования апертуры антенны [0 - ∞].
            {"--Tstrip", ExecdArgument(1.0f)},      //!< Время формирования полосового РЛИ [0 - ∞].
            {"--kR", ExecdArgument(1)},             //!< Коэффициент частотной интерполяции по наклонной дальности [1..4].
            {"--kL", ExecdArgument(1)},             //!< Коэффициент частотной интерполяции по путевой дальности [1..4].
            {"--jq", ExecdArgument(80)},            //!< Качество РЛИ после компрессии JPEG [1..100].

            {"--dx", ExecdArgument(1.0f)},          //!< Размер элемента разрешения РЛИ по дальности, м [0 - ∞].
            {"--dy", ExecdArgument(1.0f)},          //!< Размер элемента разрешения РЛИ по путевой дальности, м [0 - ∞].
            {"--x0", ExecdArgument(100.0f)},        //!< Расстояние до ближней границы РЛИ, м [0 - ∞].
            {"--y0", ExecdArgument(0.0f)},          //!< Смещение кадра РЛИ по путевой дальности, м [0 - ∞].
            {"--lx", ExecdArgument(2'000.0f)},      //!< Протяженность РЛИ по дальности, м [0 - ∞].
            {"--ly", ExecdArgument(400.0f)},        //!< Протяженность РЛИ по путевой дальности, м [0 - ∞].
            {"--ip", ExecdArgument("./img/")},      //!< Путь для сохранения РЛИ на РЛС.
            {"--remote", ExecdArgument("None")},    //!< IP-адрес сервера TCP для передачи РЛИ (напр. \c 127.0.0.1:9955).
            {"--DSP", ExecdArgument("DSP_FFTW")},   //!< Тип вычислителя [\c DSP_FFTW, \c DSP_CUDA].
            {"--mirror", ExecdArgument("False")},   //!< Вертикальное отзеркаливание РЛИ [\c True, \c False]. Стиль написания булевых переменных - с заглавной буквы.

            {"--e0", ExecdArgument(0.0f)}           //!< Высота над уровнем моря.
        };

        //! @brief Значения аргументов фокусировки \b execd по умолчанию
        QMap<QString, ExecdArgument> focus_defaults = {
            {"-f", ExecdArgument("m1")},            // <-
            {"-b", ExecdArgument(0.0f)},            // <-
            {"-e", ExecdArgument(-1.0f)},           // <-
            {"-v", ExecdArgument(-1.0f)},           // <-
            {"--Ts", ExecdArgument(1.0f)},          // <-
            {"--remote", ExecdArgument("None")},    // <-
            {"--e0", ExecdArgument(0.0f)},          // <-

            {"--px", ExecdArgument(-1.0f)},         //!< Координата по дальности точки для фокусировки.
            {"--py", ExecdArgument(-1.0f)},         //!< Координата по путевой дальности точки для фокусировки..
            {"--ls", ExecdArgument(50.0f)},         //!< Размер стороны квадрата в м, по которой производится фокусировка.
            {"--vmin", ExecdArgument(-1.0f)},       //!< Минимальное  значение гипотезы по скорости для фокусировки, км/ч.
            {"--vmax", ExecdArgument(-1.0f)},       //!< Максимальное значение гипотезы по скорости для фокусировки, км/ч.
            {"--ni", ExecdArgument(10)},            //!< Количество гипотез по скорости [1 - ∞].
        };

        public:
            explicit ExecdArgumentList(QObject* parent = nullptr);

            QString getFormArguments() const noexcept;
            QString getReformArguments() const noexcept;
            QString getFocusArguments() const noexcept;

            QMap<QString, ExecdArgument> argument_list = defaults;
            QMap<QString, ExecdArgument> reform_argument_list = defaults;
            QMap<QString, ExecdArgument> focus_argument_list = focus_defaults;
    };
} // Network
