#ifndef SCALEGRIDBACKEND_H
#define SCALEGRIDBACKEND_H

#include <QObject>
#include "smath.h"
#include "runtimedata.h"

class ScaleGridBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal cellSize               READ getCellSize               WRITE setCellSize               NOTIFY cellSizeChanged)
    Q_PROPERTY(quint8 cellType              READ getCellType               WRITE setcellType               NOTIFY cellTypeChanged)

public:
    explicit ScaleGridBackend(QObject *parent = nullptr);

    qreal getCellSize() const;
    void setCellSize(qreal newCellSize);

    quint8 getCellType() const;
    void setcellType(quint8 newCellType);

signals:
    void cellSizeChanged();
    void cellTypeChanged();

private slots:
    void recalculateGrid(void);

private:
    qreal m_cellSize;
    quint8 m_cellType;
};

#endif // SCALEGRIDBACKEND_H
