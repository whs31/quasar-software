#include "dynamicresolution.h"

DynamicResolution::DynamicResolution(QObject *parent)
    : QObject{parent}
{

}

qreal DynamicResolution::getWidthCoefficient() const { return m_widthK; }
void DynamicResolution::setWidthCoefficient(qreal value) { if (m_widthK == value) return;
    m_widthK = value; emit widthCoefficientChanged(); }

qreal DynamicResolution::getHeightCoefficient() const { return m_heightK; }
void DynamicResolution::setHeightCoefficient(qreal value) { if (m_heightK == value) return;
    m_heightK = value; emit heightCoefficientChanged(); }
