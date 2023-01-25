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
    
    if(RuntimeData::initialize()->getCurrentZoomLevel() >= 15.3)
    {
        setcellType(1);
        setCellSize(newZoom); // 100 m
    } else if(RuntimeData::initialize()->getCurrentZoomLevel() >= 12 && RuntimeData::initialize()->getCurrentZoomLevel() < 15.3)
    {
        setcellType(2);
        setCellSize(newZoom * 10); // 1 km
    } else if(RuntimeData::initialize()->getCurrentZoomLevel() >= 8 && RuntimeData::initialize()->getCurrentZoomLevel() < 12)
    {
        setcellType(3);
        setCellSize(newZoom * 100); // 10 km
    }
    else if(RuntimeData::initialize()->getCurrentZoomLevel() >= 5.5 && RuntimeData::initialize()->getCurrentZoomLevel() < 8)
    {
        setcellType(4);
        setCellSize(newZoom * 1000); // 100 km
    }
    else if(RuntimeData::initialize()->getCurrentZoomLevel() >= 3.5 && RuntimeData::initialize()->getCurrentZoomLevel() < 5.5)
    {
        setcellType(5);
        // remove completely
    }
}
