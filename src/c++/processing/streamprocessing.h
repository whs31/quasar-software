#pragma once

#include <queue>
#include <QtCore/QObject>
#include "map/entities/image.h"

using std::queue;

namespace Map
{
  class StripModel;
}

namespace Processing
{
  class StreamProcessing : public QObject
  {
      Q_OBJECT

    public:
      static StreamProcessing* get();
      static Map::StripModel* model();

      void append(const QByteArray& data) noexcept;

    signals:
      void processingFinished(Map::StripImage image);

      void passQueue();
      void finishedQueue();

    private slots:
      void processChunk() noexcept;
      void passChunk(Map::StripImage image);

    private:
      explicit StreamProcessing(QObject* parent = nullptr);
      StreamProcessing(const StreamProcessing&);
      StreamProcessing& operator=(const StreamProcessing&);

    private:
      queue<QByteArray> m_queue;
  };
} // Processing
