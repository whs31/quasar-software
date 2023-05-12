#include "multigraph.h++"
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QBrush>
#include <QtGui/QPolygonF>
#include <cmath>

MultiGraph::MultiGraph(QQuickItem* parent)
    : QQuickPaintedItem(parent)
    , timer(new QTimer(this))
{
    timer->start(timeInterval());
    connect(timer, &QTimer::timeout, this, [this](){
        for(int i = 0; i < storage.size(); ++i)
        {
            storage[i].erase(storage[i].begin());
            storage[i].push_back(storage_trigger[i]);
            storage_trigger[i] = 0;
        }
    });
}

void MultiGraph::paint(QPainter* painter)
{
    QPen pen(Qt::PenStyle::NoPen);
    QBrush brush(Qt::BrushStyle::SolidPattern);
    QBrush background_brush(Qt::BrushStyle::SolidPattern);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);

    background_brush.setColor(QColor(backgroundColor()));
    painter->setBrush(background_brush);
    painter->drawRect(0, 0, width(), height());

    painter->setBrush(brush);
    for(int i = 0; i < axisCount(); ++i)
    {
        QColor col = QColor(axisColors().at(i));
        col.setAlphaF(.7);
        brush.setColor(col);

        QPolygonF poly;
//        poly <<

//        painter->drawPolygon()
    }
}

void MultiGraph::setValues(const QList<float>& values)
{
    for(int i = 0; i < axisCount(); ++i)
        storage_trigger.insert(storage_trigger.begin() + i, values[i]);
}

float MultiGraph::timeLength() const { return m_timeLength; }
void MultiGraph::setTimeLength(float other) {
    if (qFuzzyCompare(m_timeLength, other))
        return;
    m_timeLength = other;
    emit timeLengthChanged();
}

float MultiGraph::valueMaxSize() const { return m_valueMaxSize; }
void MultiGraph::setValueMaxSize(float other) {
    if (qFuzzyCompare(m_valueMaxSize, other))
        return;
    m_valueMaxSize = other;
    emit valueMaxSizeChanged();
}

QList<QString> MultiGraph::axisNames() const { return m_axisNames; }
void MultiGraph::setAxisNames(const QList<QString> &other) {
    if (m_axisNames == other)
        return;
    m_axisNames = other;
    emit axisNamesChanged();
}

QList<QString> MultiGraph::axisColors() const { return m_axisColors; }
void MultiGraph::setAxisColors(const QList<QString> &other) {
    if (m_axisColors == other)
        return;
    m_axisColors = other;
    emit axisColorsChanged();
}

float MultiGraph::timeInterval() const { return m_timeInterval; }
void MultiGraph::setTimeInterval(float other) {
    if (qFuzzyCompare(m_timeInterval, other))
        return;
    m_timeInterval = other;
    emit timeIntervalChanged();

    timer->stop();
    timer->start(timeInterval());
}

int MultiGraph::axisCount() const { return m_axisCount; }
void MultiGraph::setAxisCount(int other) {
    if (m_axisCount == other)
        return;
    m_axisCount = other;
    emit axisCountChanged();
}

QString MultiGraph::backgroundColor() const { return m_backgroundColor; }
void MultiGraph::setBackgroundColor(const QString &other) {
    if (m_backgroundColor == other)
        return;
    m_backgroundColor = other;
    emit backgroundColorChanged();
}

QString MultiGraph::foregroundColor() const { return m_foregroundColor; }
void MultiGraph::setForegroundColor(const QString &other)
{
    if (m_foregroundColor == other)
        return;
    m_foregroundColor = other;
    emit foregroundColorChanged();
}
