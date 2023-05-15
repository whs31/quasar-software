#include "clickhandler.h"
#include <QtCore/QDebug>
#include <QtGui/QGuiApplication>
#include <QtGui/QClipboard>

using namespace Map;

ClickHandler::ClickHandler(QObject* parent)
    : QObject{parent}
{

}

Map::ClickHandler::MouseState ClickHandler::state() const { return m_state; }
void ClickHandler::setState(const MouseState& other) {
    if (m_state == other)
        return;
    m_state = other;
    emit stateChanged();
}

void ClickHandler::copyCoordinatesToClipboard(double latitude, double longitude)
{
    QGuiApplication::clipboard()->setText("Широта: " + QString::number(latitude) + ", Долгота: " + QString::number(longitude));
    qDebug() << "[GUI] Copied coordinates to clipboard:" << latitude << longitude;
}
