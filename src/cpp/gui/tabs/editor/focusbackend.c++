#include "focusbackend.h"
#include "map/imagemodel.h"
#include "network/network.h"

using namespace GUI;

FocusBackend::FocusBackend(QObject *parent)
    : QObject{parent}
    , m_imageIndex(-1)
    , m_mouseCoords(QPointF())
{}

void FocusBackend::setArguments() noexcept
{

}

QPointF FocusBackend::mouseCoords() const { return m_mouseCoords; }
void FocusBackend::setMouseCoords(QPointF other) {
    if (m_mouseCoords == other)
        return;
    m_mouseCoords = other;
    emit mouseCoordsChanged();
}

int FocusBackend::imageIndex() const { return m_imageIndex; }
void FocusBackend::setImageIndex(int other) {
    if (m_imageIndex == other)
        return;
    m_imageIndex = other;
    emit imageIndexChanged();
}
