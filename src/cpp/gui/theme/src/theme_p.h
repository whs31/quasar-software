#pragma once

#include "../include/theme.h"

using std::vector;

namespace GUI
{
    class ThemePrivate : public QObject
    {
        Q_OBJECT
        Q_DECLARE_PUBLIC(Theme)

        public:
            ThemePrivate(Theme* parent);
            virtual ~ThemePrivate() = default;

            void applyTheme(QString theme);

            vector<QString> foundThemes;

            public slots:
                void findThemesInFolder();

        private:
            Theme* q_ptr;
            QHash<QString, QString> m_color;
    };
} // namespace GUI;
