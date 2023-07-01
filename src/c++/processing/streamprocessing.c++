#include "streamprocessing.h"
#include <QtCore/QDebug>
#include "processing/imageprocessing.h"
#include "map/models/stripmodel.h"

namespace Processing
{

  StreamProcessing* StreamProcessing::get() { static StreamProcessing instance; return &instance; }
  StreamProcessing::StreamProcessing(QObject* parent)
    : QObject(parent)
  {
    connect(this, &StreamProcessing::processingFinished, this, &StreamProcessing::passChunk, Qt::QueuedConnection);
    connect(this, &StreamProcessing::passQueue, this, &StreamProcessing::processChunk, Qt::QueuedConnection);
    connect(this, &StreamProcessing::finishedQueue, this, [](){
      qDebug() << "$ [STREAM] Queue finished";
    })
  }

  Map::StripModel* StreamProcessing::model() { return ImageProcessing::get()->stripModel(); }

  void StreamProcessing::append(const QByteArray& data) noexcept
  {
    m_queue.push(data);
    qDebug() << "$ [STREAM] Current queue size:" << m_queue.size();

    if(m_queue.size() == 1)
    {
      emit passQueue();
      qDebug() << "$ [STREAM] Starting processing of queue";
    }
  }

  void StreamProcessing::processChunk() noexcept
  {
    if(m_queue.empty())
    {
      emit finishedQueue();
      return;
    }


    emit passQueue();
  }

  void StreamProcessing::passChunk(Map::StripImage image) { model()->add(image); }
} // Processing