#pragma once

#include <QtCore/QObject>
#include <QtCore/QAbstractListModel>

namespace Map
{
    class Route : public QAbstractListModel
    {
        Q_OBJECT

    public:
        explicit Route(QObject* parent = nullptr);

        signals:

    };
} // namespace Map

