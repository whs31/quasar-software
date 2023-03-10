#pragma once
#include <QObject>
#include <QPointF>
#include <QHash>
#include <vector>

class ThemePrivate;
class Theme : public QObject
{
    Q_OBJECT
    public:
        static Theme* get(QObject* parent = nullptr);

        const QString DEFAULT_THEME = "nord.json";           //! @brief Тема по умолчанию, если в конфиге не указано иное.
        const float BASE_RESOLUTION[2] = { 1366, 768 };      //! @brief Разрешение, под которое адаптируется программа (в пикселях).

        //! @brief
        Q_INVOKABLE QString color(QString key);

        //! @brief Вектор динамического скейлинга интерфейса по осям X и Y.
        Q_PROPERTY(QPointF scalingFactor READ scalingFactor WRITE setScalingFactor NOTIFY scalingFactorChanged)
        QPointF scalingFactor() const;
        void setScalingFactor(QPointF factor);

        //! @brief Задает размеры окна извне. Необходимо вызывать каждый раз, когда размеры
        //!        окна меняются.
        void setWindowDimension(float width, float height);

        signals:
        void colorsChanged();
        void scalingFactorChanged();

    protected:
        ThemePrivate* const d_ptr;

    private:
        Q_DECLARE_PRIVATE(Theme)
        static Theme* _instance;
        explicit Theme(QObject *parent = nullptr);
        QPointF m_scalingFactor;
};
