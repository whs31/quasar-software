#pragma once

#include <utility>
#include <QtCore/QList>
#include "neuraldata.h"

using std::pair;

namespace QuasarSDK
{
  class NeuralParser
  {
    public:
      static auto parseJSON(const QByteArray& json) -> pair<QString, QList<NeuralData>>;
  };
} // QuasarSDK