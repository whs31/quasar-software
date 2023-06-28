#include "sdkrealtimelineplot.h"
#include <stdexcept>
#include <QtCore/QTimer>
#include <QtQuick/QSGGeometryNode>
#include <QtQuick/QSGFlatColorMaterial>
#include "SDK/ScenegraphAlgorithms"

namespace SDK::Quick
{
  RealtimeLinePlot::RealtimeLinePlot(QQuickItem* parent)
      : LinePlot(parent)
      , timer(new QTimer(this))
      , st(0)
      , m_interval(1.0)
      , m_seconds(30)
      , m_from(0)
      , m_to(0)
  {
    this->setFlags(ItemHasContents);
    connect(timer, &QTimer::timeout, this, &RealtimeLinePlot::tick);

    vec.resize(static_cast<size_t>((float)seconds() / interval()));
    timer->start(static_cast<int>(interval() * 1'000));
  }

  void RealtimeLinePlot::append(float f) { st = f; }

  float RealtimeLinePlot::interval() const { return m_interval; }
  void RealtimeLinePlot::setInterval(float o) {
    if (qFuzzyCompare(m_interval, o))
      return;

    if(o <= 0)
      throw std::invalid_argument("Interval must be greater than 0.");

    m_interval = o;
    emit intervalChanged();

    vec.clear();
    so = static_cast<int>((float)seconds() / interval());
  }

  int RealtimeLinePlot::seconds() const { return m_seconds; }
  void RealtimeLinePlot::setSeconds(int o) {
    if (m_seconds == o)
      return;

    if(o <= 0)
      throw std::invalid_argument("Seconds must be greater than 0.");

    m_seconds = o;
    emit secondsChanged();

    vec.clear();
    this->update();
  }

  void RealtimeLinePlot::tick()
  {
    so = static_cast<int>((float)seconds() / interval());
    if(vec.size() >= so and not vec.empty())
      vec.erase(vec.begin());
    vec.push_back(st);
    st = 0;

    if(from() == 0 and to() == 0)
      this->set(vec);
    else
      this->set(vec, to(), from());
  }

  float RealtimeLinePlot::from() const { return m_from; }
  void RealtimeLinePlot::setFrom(float o) {
    if (qFuzzyCompare(m_from, o))
      return;
    m_from = o;
    emit fromChanged();
  }

  float RealtimeLinePlot::to() const { return m_to; }
  void RealtimeLinePlot::setTo(float o) {
    if (qFuzzyCompare(m_to, o))
      return;
    m_to = o;
    emit toChanged();
  }
} // SDK::Quick