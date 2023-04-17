#pragma once

#include <QObject>
#include <QPointF>
#include <QHash>
#include <vector>

#define __signal void
#define __deprecated __attribute__((deprecated))
#define __qml Q_INVOKABLE

namespace GUI
{
    class ThemePrivate;
    class Theme : public QObject
    {
        Q_OBJECT
        Q_DECLARE_PRIVATE(Theme)

        //! @brief Вектор динамического скейлинга интерфейса по осям X и Y.
        Q_PROPERTY(QPointF scalingFactor READ scalingFactor WRITE setScalingFactor NOTIFY scalingFactorChanged)

        static Theme* _instance;
        QPointF m_scalingFactor;

        public:
            static Theme* get(QObject* parent = nullptr);
            virtual ~Theme() = default;

            //! @brief Тема по умолчанию, если в конфиге не указано иное.
            const QString DEFAULT_THEME = "nord.json";

            //! @brief Разрешение, под которое адаптируется программа (в пикселях).
            const float BASE_RESOLUTION[2] = { 1366, 768 };

            //! @brief
            __qml QString color(QString key);

            //! @brief Сеттер и геттер для параметра scalingFactor.
            QPointF scalingFactor() const;
            void setScalingFactor(QPointF factor);

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
    };
} // namespace GUI;
