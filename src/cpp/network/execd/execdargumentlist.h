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
            {"-f", ExecdArgument("m1")},
            {"-m", ExecdArgument(1)},
            {"-t", ExecdArgument(1.0f)},
            {"-b", ExecdArgument(0)},
            {"--e0", ExecdArgument(120)},
            {"-e", ExecdArgument(-10000)},
            {"-v", ExecdArgument(-1.0f)},
            {"-w", ExecdArgument("HAMMING")},
            {"-i", ExecdArgument(0)},
            {"--Ts", ExecdArgument(1.0f)},
            {"--Tstrip", ExecdArgument(1.0f)},
            {"--kR", ExecdArgument(1)},
            {"--kL", ExecdArgument(1)},
            {"--jq", ExecdArgument(80)},

            {"--dx", ExecdArgument(1.0f)},
            {"--dy", ExecdArgument(1.0f)},
            {"--x0", ExecdArgument(100)},
            {"--y0", ExecdArgument(200)},
            {"--lx", ExecdArgument(2'000)},
            {"--ly", ExecdArgument(400)},
            {"--ip", ExecdArgument("./img/")},
            {"--im", ExecdArgument("out")},
            {"--Tshift", ExecdArgument(1.0f)},
            {"--remote", ExecdArgument("None")},
            {"--td", ExecdArgument(-1)},
        };

        QMap<QString, ExecdArgument> focus_defaults = {
            {"-f", ExecdArgument("m1")},
            {"-b", ExecdArgument(0)},
            {"--e0", ExecdArgument(120)},
            {"-e", ExecdArgument(-10000)},
            {"-v", ExecdArgument(-1.0f)},
            {"--Ts", ExecdArgument(1.0f)},

            {"--remote", ExecdArgument("None")},

            {"--px", ExecdArgument(-1.0f)},
            {"--py", ExecdArgument(-1.0f)},
            {"--ls", ExecdArgument(-1.0f)},
            {"--Ts", ExecdArgument(-1.0f)},
            {"--vmin", ExecdArgument(-1.0f)},
            {"--vmax", ExecdArgument(-1.0f)},
            {"--driftAngle", ExecdArgument(-1.0f)},
            {"--ni", ExecdArgument(1)},
        };

        public:
            explicit ExecdArgumentList(QObject* parent = nullptr);

            QMap<QString, ExecdArgument> argument_list = defaults;
            QMap<QString, ExecdArgument> reform_argument_list = defaults;
            QMap<QString, ExecdArgument> focus_argument_list = focus_defaults;
    };
} // Network
