#pragma once

#include <Definitions>
#include <QtCore/QObject>
#include <QtCore/QPointF>
#include <QtCore/QHash>
#include <vector>
#include <imgui/imgui.h>

#define THEME GUI::Theme::get()

namespace GUI
{
    class ThemePrivate;
    class Theme : public QObject
    {
        Q_OBJECT
        Q_DECLARE_PRIVATE(Theme)

        //! @brief Вектор динамического скейлинга интерфейса по осям X и Y.
        Q_PROPERTY(QPointF scalingFactor READ scalingFactor WRITE setScalingFactor NOTIFY scalingFactorChanged)

        public:
            static Theme* get(QObject* parent = nullptr);
            virtual ~Theme() = default;

            //! @brief Тема по умолчанию, если в конфиге не указано иное.
            const QString DEFAULT_THEME = "nord.json";

            //! @brief Разрешение, под которое адаптируется программа (в пикселях).
            const float BASE_RESOLUTION[2] = { 1366, 768 };

            //! @brief
            __qml QString color(QString key);

            //! @brief
            __qml QString colorText(const QString& text, const QString& theme_color_name);

            //! @brief
            ImVec4 hexToFloatColor(const QString& hex, float alpha = 1) const;

            //! @brief Сеттер и геттер для параметра scalingFactor.
            __getter QPointF scalingFactor() const;
            __setter void setScalingFactor(QPointF factor);

            //! @brief Задает размеры окна извне. Необходимо вызывать каждый раз, когда размеры
            //!        окна меняются.
            void setWindowDimension(float width, float height);

            //! @warning В связи с тем, что поддержка QWidgets убрана из проекта, функция больше
            //!          не имеет реализации.
            __deprecated void setQWidgetsStylesheet();

            signals:
                __signal colorsChanged();
                __signal scalingFactorChanged();

        protected:
            ThemePrivate* const d_ptr;

        private:
            explicit Theme(QObject* parent = nullptr);

        private:
            static Theme* _instance;
            QPointF m_scalingFactor;
    };
} // namespace GUI;
