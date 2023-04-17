#pragma once

#include <QObject>
#define __signal void

class Entry : public QObject
{
    Q_OBJECT

    public:
        explicit Entry(QObject *parent = nullptr);
};
