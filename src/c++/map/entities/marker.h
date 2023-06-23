#pragma once

#include <QtCore/QString>

namespace Map
{
  struct Marker
  {
    Marker(double latitude, double longitude, QString name,
           QString color = "white", QString icon = "qrc:/map/markers/default.png");

    double latitude;
    double longitude;
    QString name;
    QString color;
    QString icon;
  };

  struct PlannerPoint : public Marker
  {
    QString command;
  };
} //namespace Map;
