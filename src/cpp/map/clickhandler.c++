#include "clickhandler.h++"

using namespace Map;

ClickHandler* ClickHandler::instance = nullptr;
ClickHandler *ClickHandler::get(QObject* parent) {
    if(instance == nullptr)
        instance = new ClickHandler(parent);
    return instance;
}

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
