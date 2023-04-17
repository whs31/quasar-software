#pragma once
#include "../include/theme.h++"

namespace GUI
{
    class ThemePrivate
    {
        Q_DECLARE_PUBLIC(Theme)

        Theme* q_ptr;
        QHash<QString, QString> m_color;

        public:
            ThemePrivate(Theme* parent);
            virtual ~ThemePrivate() = default;

            void setWindowDimension(float w, float h);
            void findThemesInFolder();
            void applyTheme(QString theme);

            std::vector<QString> foundThemes;
    };
} // namespace GUI;
