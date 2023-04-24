#pragma once

#include <definitions.h++>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QMap>
#include <QtCore/QMetaType>
#include <QtQml/QQmlPropertyMap>
#include "execdargument.h++"

class ExecdCommandFormer : public QObject
{
    Q_OBJECT

    public:
        explicit ExecdCommandFormer(QObject* parent = nullptr);

        signals:

    private:
        const QMap<QString, execdargument_t> defaults =
        {
            {"", execdargument_t("-f", execdargument_t::String, "m1", "Имя файла")},
            {"", execdargument_t()},
        };
};

