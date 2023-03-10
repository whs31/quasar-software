#pragma once
#include "../include/theme.hpp"

class ThemePrivate
{
    Q_DECLARE_PUBLIC(Theme)
    public:
        ThemePrivate(QObject *parent);
        virtual ~ThemePrivate() = default;

    private:
        Theme* q_ptr;
};
