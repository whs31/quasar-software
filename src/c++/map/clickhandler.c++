#include "clickhandler.h"
#include <QtCore/QDebug>
#include <QtGui/QGuiApplication>
#include <QtGui/QClipboard>
#include "markermodel.h"

namespace Map
{

  ClickHandler* ClickHandler::get() { static ClickHandler instance; return &instance; }

  ClickHandler::ClickHandler(QObject* parent)
    : QObject{parent}
    , marker_model(new MarkerModel(this))
  {}

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

  MarkerModel* ClickHandler::markerModel()
  {
    return marker_model;
  }

  void ClickHandler::addMarker(double latitude, double longitude, const QString& name, const QString& color, const QString& icon)
  {
    markerModel()->add(Marker(latitude, longitude, name, color, icon));
  }

} // Map
