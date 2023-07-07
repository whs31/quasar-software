/**
  * \class QuasarSDK::Telemetry CTelemetry.h <QuasarSDK/Networking/CTelemetry.h>
  * \brief Класс-хранилище для текущей телеметрии РЛС.
  * \details Хранит текущие значения телеметрии борта с РЛС
  * и предоставляет доступ к ним для движка QML и мета-объектной
  * системы.
  * \extends QObject
  */

#include "CTelemetry.h"

namespace QuasarSDK
{
  /// \brief Создает новый объект Telemetry с указанным родителем.
  Telemetry::Telemetry(QObject* parent)
      : QObject(parent)
      , m_datagram({})
      , m_seaLevel(0)
  {}

  /**
   * \brief Задает новую датаграмму телеметрии в класс.
   * \param datagram - новая датаграмма.
   */
  void Telemetry::setDatagram(const Datagrams::TelemetryDatagram& datagram) noexcept
  {
    m_datagram = datagram;

    emit positionChanged();
    emit velocityChanged();
    emit eulerAxesChanged();
    emit satellitesChanged();
    emit seaLevelChanged();
  }

  /**
   * \property Telemetry::position
   * \brief Предоставляет географическую позицию БПЛА.
   * \details Позиция представлена широтой, долготой (WGS-84)
   * и высотой в метрах над уровнем моря. Свойство доступно только
   * для чтения.
   */
  QGeoCoordinate Telemetry::position() const
  {
    return {m_datagram.latitude, m_datagram.longitude, m_datagram.altitude};
  }

  /**
   * \property Telemetry::velocity
   * \brief Предоставляет вектор скорости БПЛА.
   * \details Скорость представлена в виде двумерного вектора и выражена в километрах в час.
   * OX-составляющая вектора - горизонтальная скорость, OY-составляющая -
   * вертикальная. Свойство доступно только для чтения.
   */
  QVector2D Telemetry::velocity() const
  {
    return {static_cast<float>(m_datagram.velocity_course), static_cast<float>(m_datagram.velocity_vertical)};
  }

  /**
   * \property Telemetry::eulerAxes
   * \brief Предоставляет углы поворота БПЛА в связанной системе координат.
   * \details Углы представлены в виде трехмерного вектора, в котором:
   *    - ось *OX*: тангаж БПЛА
   *    - ось *OY*: рысканье или *курс* БПЛА
   *    - ось *OZ*: крен БПЛА
   * Все углы измеряются в градусах в диапазоне от -180 до +180.
   * Свойство доступно только для чтения.
   */
  QVector3D Telemetry::eulerAxes() const
  {
    return {static_cast<float>(m_datagram.pitch), static_cast<float>(m_datagram.yaw), static_cast<float>(m_datagram.roll)};
  }

  /**
   * \property Telemetry::satellites
   * \brief Предоставляет текущее количество спутников навигации.
   * \details Свойство доступно только для чтения.
   */
  int Telemetry::satellites() const
  {
    return m_datagram.satellites;
  }

  /**
   * \property Telemetry::seaLevel
   * \brief Предоставляет текущее значение высоты земной поверхности.
   * \details Свойство доступно как для чтения, так и для записи.
   * Предполагается, что данное значение будет устанавливаться пользователем
   * СПО для передачи его в качестве аргумента **--e0** в сервис \c execd.
   */
  float Telemetry::seaLevel() const { return m_seaLevel; }
  void Telemetry::setSeaLevel(float o)
  {
    if(m_seaLevel == o)
      return;
    m_seaLevel = o;
    emit seaLevelChanged();
  }
} // QuasarSDK