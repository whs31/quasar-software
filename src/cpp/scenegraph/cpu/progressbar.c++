#include "progressbar.h++"
#include <QtGui/QPainter>
#include <QtGui/QBrush>
#include <cmath>


ProgressBar::ProgressBar(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
}

void ProgressBar::paint(QPainter* painter)
{
    QPen pen(Qt::PenStyle::NoPen);
    QBrush brush(Qt::BrushStyle::SolidPattern);
    QBrush background_brush(Qt::BrushStyle::SolidPattern);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);

    if(value() < 35)
        brush.setColor(QColor(errorColor()));
    else if(value() > 65)
        brush.setColor(QColor(successColor()));
    else
        brush.setColor(QColor(warnColor()));

    background_brush.setColor(QColor(backgroundColor()));
    painter->setBrush(background_brush);

    painter->drawRoundedRect(0, 0, this->width(), this->height(), 4, 4);

    painter->setBrush(brush);
    painter->drawRoundedRect(0, 0, this->width() * (float)value() / 100, this->height(), 4, 4);
}

QString ProgressBar::errorColor() const { return m_errorColor; }
void ProgressBar::setErrorColor(const QString &other) {
    if (m_errorColor == other) return;
    m_errorColor = other;
    emit errorColorChanged();
}

QString ProgressBar::warnColor() const { return m_warnColor; }
void ProgressBar::setWarnColor(const QString &other) {
    if (m_warnColor == other) return;
    m_warnColor = other;
    emit warnColorChanged();
}

QString ProgressBar::successColor() const { return m_successColor; }
void ProgressBar::setSuccessColor(const QString &other) {
    if (m_successColor == other) return;
    m_successColor = other;
    emit successColorChanged();
}

QString ProgressBar::backgroundColor() const { return m_backgroundColor; }
void ProgressBar::setBackgroundColor(const QString& other) {
    if (m_backgroundColor == other)
        return;
    m_backgroundColor = other;
    emit backgroundColorChanged();
}

int ProgressBar::value() const { return m_value; }
void ProgressBar::setValue(int other) {
    if (m_value == other) return;
    m_value = other;
    emit valueChanged();
    this->update();
}
