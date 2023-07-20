//
// Created by whs31 on 20.07.23.
//

#pragma once

#include <queue>
#include <QtCore/QObject>
#include <QuasarSDK/Map/MapImageSegment>

using std::queue;
using QuasarSDK::Map::MapImageSegment;

namespace Processing
{
  class StreamProcessor : public QObject
  {
    Q_OBJECT

    public:
      explicit StreamProcessor(QObject* parent = nullptr);

      // model

      void process(const QByteArray& data) noexcept;

    signals:
      void finished(MapImageSegment segment);

      void queuePassed();
      void queueFinished();

    private:
      Q_SLOT void processChunk() noexcept;
      Q_SLOT void pass(MapImageSegment segment);

    private:
      queue<QByteArray> m_queue;
  };
} // Processing
