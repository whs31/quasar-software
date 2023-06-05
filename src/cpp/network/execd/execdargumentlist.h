#pragma once

#include <QtCore/QMap>
#include <QtCore/QObject>

namespace Network
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

        QMap<QString, ExecdArgument> defaults = {
            {"-f", ExecdArgument("m1")},            //! @var Имя файла радиоголограммы без расширения
            {"-m", ExecdArgument(1)},               //! @var Режим зондирования [1..4, 6, 7]
            {"-t", ExecdArgument(1.0f)},            //! @var Смещение времени начала формирования отн. начала зондирования [0 - inf]
            {"-b", ExecdArgument(0.0f)},            //! @var Яркость РЛИ, 0 - авто [0 - inf]
            {"-e", ExecdArgument(-1.0f)},           //! @var Высота БПЛА отн. уровня моря, -1 - авто, м
            {"-v", ExecdArgument(-1.0f)},           //! @var Скорость БПЛА, -1 - авто, км/ч
            {"-i", ExecdArgument(0)},               //! @var Интерполяция скорости [0, 1] - 0: среднее значение за Ts,
                                                    //! 1: интерполированное значение для каждого периода за Ts
            {"--Ts", ExecdArgument(1.0f)},          //! @var Время синтезирования апертуры антенны [0 - inf]
            {"--Tstrip", ExecdArgument(1.0f)},      //! @var Время формирования полосового РЛИ [0 - inf]
            {"--kR", ExecdArgument(1)},             //! @var Коэффициент частотной интерполяции по наклонной дальности [1..4]
            {"--kL", ExecdArgument(1)},             //! @var Коэффициент частотной интерполяции по путевой дальности [1..4]
            {"--jq", ExecdArgument(80)},            //! @var Качество РЛИ после компрессии JPEG [1..100]

            {"--dx", ExecdArgument(1.0f)},          //! @var Размер элемента разрешения РЛИ по дальности, м [0 - inf]
            {"--dy", ExecdArgument(1.0f)},          //! @var Размер элемента разрешения РЛИ по путевой дальности, м [0 - inf]
            {"--x0", ExecdArgument(100.0f)},        //! @var Расстояние до ближней границы РЛИ, м [0 - inf]
            {"--y0", ExecdArgument(0.0f)},          //! @var Смещение кадра РЛИ по путевой дальности, м [0 - inf]
            {"--lx", ExecdArgument(2'000.0f)},      //! @var Протяженность РЛИ по дальности, м [0 - inf]
            {"--ly", ExecdArgument(400.0f)},        //! @var Протяженность РЛИ по путевой дальности, м [0 - inf]
            {"--ip", ExecdArgument("./img/")},      //! @var Путь для сохранения РЛИ на РЛС
            {"--remote", ExecdArgument("None")},    //! @var IP-адрес сервера TCP для передачи РЛИ (e.g. 127.0.0.1:9955)
            {"--DSP", ExecdArgument("DSP_FFTW")},   //! @var Тип вычислителя [DSP_FFTW, DSP_CUDA]
            {"--mirror", ExecdArgument("False")},   //! @var Вертикальное отзеркаливание РЛИ [True, False]
        };

        QMap<QString, ExecdArgument> focus_defaults = {
            {"-f", ExecdArgument("m1")},            // <-
            {"-b", ExecdArgument(0.0f)},            // <-
            {"-e", ExecdArgument(-1.0f)},           // <-
            {"-v", ExecdArgument(-1.0f)},           // <-
            {"--Ts", ExecdArgument(1.0f)},          // <-
            {"--remote", ExecdArgument("None")},    // <-

            {"--px", ExecdArgument(-1.0f)},         //! @var Координата по дальности точки для фокусировки
            {"--py", ExecdArgument(-1.0f)},         //! @var Координата по путевой дальности точки для фокусировки.
            {"--ls", ExecdArgument(50.0f)},         //! @var Размер стороны квадрата в м, по которой производится фокусировка
            {"--vmin", ExecdArgument(-1.0f)},       //! @var Минимальное  значение гипотезы по скорости для фокусировки, км/ч
            {"--vmax", ExecdArgument(-1.0f)},       //! @var Максимальное значение гипотезы по скорости для фокусировки, км/ч
            {"--ni", ExecdArgument(10)},            //! @var Количество гипотез по скорости [1 - inf]
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
