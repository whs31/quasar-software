#pragma once

#include "SDK/LinePlot"

class QTimer;

namespace SDK::Quick
{
  class RealtimeLinePlot : public LinePlot
  {
    Q_OBJECT
      Q_PROPERTY(float interval READ interval WRITE setInterval NOTIFY intervalChanged)
      Q_PROPERTY(int seconds READ seconds WRITE setSeconds NOTIFY secondsChanged)
      Q_PROPERTY(float from READ from WRITE setFrom NOTIFY fromChanged)
      Q_PROPERTY(float to READ to WRITE setTo NOTIFY toChanged)

    public:
      explicit RealtimeLinePlot(QQuickItem* parent = nullptr);

      Q_INVOKABLE void append(float f);

      [[nodiscard]] float interval() const; void setInterval(float);
      [[nodiscard]] int seconds() const; void setSeconds(int);
      [[nodiscard]] float from() const; void setFrom(float);
      [[nodiscard]] float to() const; void setTo(float);

    signals:
      void intervalChanged();
      void secondsChanged();
      void fromChanged();
      void toChanged();

    private slots:
      void tick();

    private:
      QTimer* timer;
      float st;
      vector<float> vec;
      int so;

      float m_interval; // s
      int m_seconds;
      float m_from;
      float m_to;
  };
} // SDK::Quick