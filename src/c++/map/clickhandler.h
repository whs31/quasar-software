#pragma once

#include <QtCore/QObject>

namespace Map
{
  class GeoMarkerModel;

  class ClickHandler : public QObject
  {
    public:
      enum MouseState
      {
        Idle,
        RulerActive,
        ProtractorActive,
        MarkerActive,
        PlannerActive,
        TileLoaderActive,
        EraserActive
      };

    Q_OBJECT
    Q_ENUM(MouseState);
    Q_PROPERTY(MouseState state READ state WRITE setState NOTIFY stateChanged)

    public:
      static ClickHandler* get();

      [[nodiscard]] MouseState state() const; void setState(const MouseState&);
      [[nodiscard]] GeoMarkerModel* geoMarkerModel() const;

      Q_INVOKABLE void copyCoordinatesToClipboard(double latitude, double longitude);
      Q_INVOKABLE void addMarker(double latitude, double longitude, const QString& name, const QString& color, const QString& icon);

    signals:
      void stateChanged();

    private:
      explicit ClickHandler(QObject* parent = nullptr);
      ClickHandler(const ClickHandler&);
      ClickHandler& operator=(const ClickHandler&);

    private:
      MouseState m_state = Idle;
      GeoMarkerModel* m_marker_model;
  };
} // namespace Map;
