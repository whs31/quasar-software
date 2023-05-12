#pragma once

#include <Definitions>
#include <QtCore/QObject>
#include <QtCore/QPointF>
#include <QtCore/QHash>
#include <vector>

#define THEME GUI::Theme::get()

namespace GUI
{
    class ThemePrivate;
    class Theme : public QObject
    {
        Q_OBJECT
        DEFINE_AS_SINGLETON(Theme)
        Q_DECLARE_PRIVATE(Theme)

        public:
            virtual ~Theme() = default;

            //! @brief Тема по умолчанию, если в конфиге не указано иное.
            const QString DEFAULT_THEME = "nord.json";

            //! @brief
            __exposed QString color(QString key);

            //! @brief
            __exposed QString colorText(const QString& text, const QString& theme_color_name);

            signals:
                __signal colorsChanged();

        protected:
            ThemePrivate* const d_ptr;

        private:
            explicit Theme(QObject* parent = nullptr);
    };
} // namespace GUI;
