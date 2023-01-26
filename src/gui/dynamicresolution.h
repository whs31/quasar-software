#ifndef DYNAMICRESOLUTION_H
#define DYNAMICRESOLUTION_H

#include <QObject>

class DynamicResolution : public QObject
{
    Q_OBJECT

    // динамический рескейлинг интерфейса
    Q_PROPERTY(qreal kw              READ getWidthCoefficient    WRITE setWidthCoefficient    NOTIFY widthCoefficientChanged)
    Q_PROPERTY(qreal kh              READ getHeightCoefficient   WRITE setHeightCoefficient   NOTIFY heightCoefficientChanged)
public:
    explicit DynamicResolution(QObject *parent = nullptr);
    qreal getWidthCoefficient() const;                                  void setWidthCoefficient(qreal value);
    qreal getHeightCoefficient() const;                                 void setHeightCoefficient(qreal value);

signals:
    void widthCoefficientChanged();
    void heightCoefficientChanged();

private:
    qreal m_widthK = 1;
    qreal m_heightK = 1;
};

#endif // DYNAMICRESOLUTION_H
