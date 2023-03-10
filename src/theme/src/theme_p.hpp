#pragma once
#include "../include/theme.hpp"

class ThemePrivate
{
    Q_DECLARE_PUBLIC(Theme)
    public:
        ThemePrivate(Theme* parent);
        virtual ~ThemePrivate() = default;

        void setWindowDimension(float w, float h);
        void findThemesInFolder();
        void applyTheme(QString theme);

        std::vector<QString> foundThemes;

    private:
        Theme* q_ptr;
        QHash<QString, QString> m_color;
};
