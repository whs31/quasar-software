#include "neuralparser.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

namespace QuasarSDK
{
  auto NeuralParser::parseJSON(const QByteArray& json) -> pair<QString, QList<NeuralData>>
  {
    pair<QString, QList<NeuralData>> ret;

    QJsonDocument document = QJsonDocument::fromJson(json);
    QJsonObject object = document.object();
    ret.first = object["name"].toString();

    QJsonArray array = object["obj"].toArray();
    auto list = array.toVariantList();
    for(const auto& var : list)
    {
      auto x = var.toJsonObject();
      ret.second.push_back(NeuralData(x["tag"].toString(),
                                      static_cast<float>(x["x1"].toInt()),
                                      static_cast<float>(x["x2"].toInt()),
                                      static_cast<float>(x["y1"].toInt()),
                                      static_cast<float>(x["y2"].toInt()),
                                      QColor(x["color"].toString())));
    }

    qDebug() << "$ [NEURAL] Parsed json package data:";
    for(const auto& a : ret.second)
      qDebug() << "$" << a.tag() << a.rect() << a.color();
    return ret;
  }
} // QuasarSDK