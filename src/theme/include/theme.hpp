#pragma once
#include <QObject>
#include <QPointF>
#include <vector>

class ThemePrivate;
class Theme : public QObject
{
    Q_OBJECT
    public:
        static Theme* get(QObject* parent = nullptr);

        const QString DEFAULT_THEME = "nord.json";           //! @brief Тема по умолчанию, если в конфиге не указано иное.
        const float BASE_RESOLUTION[2] = { 1366, 768 };      //! @brief Разрешение, под которое адаптируется программа (в пикселях).

        //! @brief Список строк с цветами палитры интерфейса.
        Q_PROPERTY(QList<QString> color READ color WRITE setColor NOTIFY colorChanged)
        QList<QString> color() const;

        //! @brief Вектор динамического скейлинга интерфейса по осям X и Y.
        Q_PROPERTY(QPointF scalingFactor READ scalingFactor WRITE setScalingFactor NOTIFY scalingFactorChanged)
        QPointF scalingFactor() const;
        void setScalingFactor(QPointF factor);

        //! @brief Задает размеры окна извне. Необходимо вызывать каждый раз, когда размеры
        //!        окна меняются.
        void setWindowDimension(float width, float height);

        signals:
        void colorChanged();
        void scalingFactorChanged();

    protected:
        ThemePrivate* const d_ptr;

    private:
        Q_DECLARE_PRIVATE(Theme)
        static Theme* _instance;
        explicit Theme(QObject *parent = nullptr);
        QList<QString> m_color;
        void setColor(const QList<QString>& list);
        QPointF m_scalingFactor;
};
