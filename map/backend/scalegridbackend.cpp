#include "scalegridbackend.h"

ScaleGridBackend::ScaleGridBackend(QObject *parent)
    : QObject{parent}
{
    connect(RuntimeData::initialize(), SIGNAL(currentZoomLevelChanged()), this, SLOT(recalculateGrid()));
}

qreal ScaleGridBackend::getCellSize() const
{ return m_cellSize; }
void ScaleGridBackend::setCellSize(qreal newCellSize)
{
    if (qFuzzyCompare(m_cellSize, newCellSize))
        return;
    m_cellSize = newCellSize;
    emit cellSizeChanged();
}

quint8 ScaleGridBackend::getCellType() const
{ return m_cellType; }
void ScaleGridBackend::setcellType(quint8 newCellType)
{
    if (m_cellType == newCellType)
        return;
    m_cellType = newCellType;
    emit cellTypeChanged();
}

void ScaleGridBackend::recalculateGrid(void)
{
    qreal newZoom = SMath::zoomLevelToDistance((18 - RuntimeData::initialize()->getCurrentZoomLevel()), 
                                                RuntimeData::initialize()->getLatitude()) / 754369;
    qCritical()<<RuntimeData::initialize()->getCurrentZoomLevel() << "  " << newZoom;
    setCellSize(newZoom);
}
