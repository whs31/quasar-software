#pragma once
#include <QObject>
#include <QPointF>

class ThemePrivate;
class Theme : public QObject
{
    Q_OBJECT
    public:
        explicit Theme(QObject *parent = nullptr);

        Q_PROPERTY(QList<QString> color READ color WRITE setColor NOTIFY colorChanged)
        QList<QString> color() const;

        Q_PROPERTY(QPointF scalingFactor READ scalingFactor WRITE setScalingFactor NOTIFY scalingFactorChanged)

        QPointF scalingFactor() const;
        void setScalingFactor(QPointF newScalingFactor);

    signals:
        void colorChanged();

        void scalingFactorChanged();

    protected:
        ThemePrivate* const d_ptr;

    private:
        Q_DECLARE_PRIVATE(Theme)
        QList<QString> m_color;
        void setColor(const QList<QString>& list);
        QPointF m_scalingFactor;
};
