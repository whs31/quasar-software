#include "statusindicator.h++"
#include <QtGui/QPainter>
#include <QtGui/QBrush>
#include <cmath>


StatusIndicator::StatusIndicator(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
}

void StatusIndicator::paint(QPainter* painter)
{
    QColor col_error(errorColor());
    QColor col_warn(warnColor());
    QColor col_success(successColor());

    switch (state()) {
    case 0:
    {
        QBrush brush(col_error);
        painter->setBrush(brush);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->drawEllipse(width() / 2, height() / 2, std::min(width(), height()) / 2, std::min(width(), height()) / 2);

        break;
    }
    case 1:
    {
        QBrush brush(col_warn);
        painter->setBrush(brush);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->drawEllipse(width() / 2, height() / 2, std::min(width(), height()) / 2, std::min(width(), height()) / 2);

        break;
    }
    case 2:
    {
        QBrush brush(col_success);
        painter->setBrush(brush);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->drawEllipse(width() / 2, height() / 2, std::min(width(), height()) / 2, std::min(width(), height()) / 2);

        break;
    }
    default:
        break;
    }
}

QString StatusIndicator::errorColor() const { return m_errorColor; }
void StatusIndicator::setErrorColor(const QString &other) {
    if (m_errorColor == other) return;
    m_errorColor = other;
    emit errorColorChanged();
}

QString StatusIndicator::warnColor() const { return m_warnColor; }
void StatusIndicator::setWarnColor(const QString &other) {
    if (m_warnColor == other) return;
    m_warnColor = other;
    emit warnColorChanged();
}

QString StatusIndicator::successColor() const { return m_successColor; }
void StatusIndicator::setSuccessColor(const QString &other) {
    if (m_successColor == other) return;
    m_successColor = other;
    emit successColorChanged();
}

int StatusIndicator::state() const { return m_state; }
void StatusIndicator::setState(int other) {
    if (m_state == other) return;
    m_state = other;
    emit stateChanged();
    this->update();
}
