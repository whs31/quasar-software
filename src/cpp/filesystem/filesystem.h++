#pragma once

#include <Definitions>
#include <QtCore/QObject>

class Filesystem : public QObject
{
    Q_OBJECT

    public:
        static Filesystem* get(QObject* parent = nullptr);

        signals:

    private:
        Filesystem(QObject* parent = nullptr);

    private:
        static Filesystem* instance;
};

