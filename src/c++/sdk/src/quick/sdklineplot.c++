#include "sdklineplot.h"
#include <QtQuick/QSGGeometryNode>
#include <QtQuick/QSGFlatColorMaterial>
#include "SDK/ScenegraphAlgorithms"

namespace SDK::Quick
{
  LinePlot::LinePlot(QQuickItem* parent)
      : ChartBase(parent)
      , m_drawAxes(true)
      , m_fill(true)
      , x_size(0)
      , y_max(0)
      , y_min(0)
  {
    this->setFlags(ItemHasContents);
  }

  void LinePlot::set(const vector<float>& vec, float max, float min)
  {
    if(v == vec)
      return;

    v = vec;
    y_max = max;
    y_min = min;
    this->calculate_bounds((max != 0 or min != 0));
    this->update();
  }

  void LinePlot::clear()
  {
    v.clear();
    y_max = 0;
    y_min = 0;
    this->update();
  }

  QSGNode *LinePlot::updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*)
  {
    QSGGeometry* geometry;
    QSGGeometry* axis_geometry;
    QSGGeometryNode* plot_node;
    auto* node = dynamic_cast<QSGGeometryNode*>(old_node);

    if(node == nullptr)
    {
      node = new QSGGeometryNode;

      auto* material = new QSGFlatColorMaterial;
      material->setColor(QColor(plottingColor()));
      geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0, 0, QSGGeometry::UnsignedIntType);

      node->setMaterial(material);
      node->setGeometry(geometry);
      node->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);
    }

    node->removeAllChildNodes();

    if(drawBackground())
      node->appendChildNode(SDK::Scenegraph::createBackgroundNode(backgroundColor(), (float)width(), (float)height()));

    axis_geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0, 0, QSGGeometry::UnsignedIntType);
    axis_geometry->setDrawingMode(QSGGeometry::DrawLines);
    axis_geometry->setLineWidth(2);
    auto* axis_node = new QSGGeometryNode;
    axis_node->setMaterial(SDK::Scenegraph::createFlatTransparentMaterial(foregroundColor(), .3));
    axis_node->setGeometry(axis_geometry);
    axis_node->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);
    node->appendChildNode(axis_node);

    float dx = (float)width() / (x_size - 1);
    float dy = (float)height() / (y_max - y_min);

    if(fill())
    {
      plot_node = new QSGGeometryNode;
      plot_node->setMaterial(SDK::Scenegraph::createFlatTransparentMaterial(plottingColor(), .4));
      plot_node->setGeometry(SDK::Scenegraph::createSimpleGraphNode(v, dx, dy, (float)width(), (float)height()));
      plot_node->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);
      node->appendChildNode(plot_node);
    }

    auto* outline_node = new QSGGeometryNode;
    outline_node->setMaterial(SDK::Scenegraph::createFlatTransparentMaterial(plottingColor()));
    outline_node->setGeometry(SDK::Scenegraph::createLineStripNode(v, dx, dy, (float)width(), (float)height(), 3));
    outline_node->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);
    node->appendChildNode(outline_node);

    if(drawAxes())
    {
      vector<SDK::Scenegraph::Vertex> gla;
      float ox_dx = (float)width() / 5;
      float x = ox_dx;
      while(x < width())
      {
        gla.emplace_back(x, 0);
        gla.emplace_back(x, (float)height());
        x += ox_dx;
      }

      float oy_dy = (float)height() / 4;
      float y = oy_dy;
      while(y < height())
      {
        gla.emplace_back(0, y);
        gla.emplace_back((float)width(), y);
        y += oy_dy;
      }

      axis_geometry->allocate((int)gla.size());
      for(size_t i = 0; i < gla.size(); ++i)
        axis_geometry->vertexDataAsPoint2D()[i].set(gla[i].x, gla[i].y);
    }

    node->markDirty(QSGNode::DirtyGeometry);
    return node;
  }

  void LinePlot::calculate_bounds(bool skip)
  {
    x_size = static_cast<float>(v.size());
    if(not skip)
    {
      const auto [min, max] = std::minmax_element(v.begin(), v.end());
      y_max = (float)*max;
      y_min = (float)*min;
    }
  }

  bool LinePlot::drawAxes() const { return m_drawAxes; }
  void LinePlot::setDrawAxes(bool o) {
    if (m_drawAxes == o)
      return;
    m_drawAxes = o;
    emit drawAxesChanged();
  }

  bool LinePlot::fill() const { return m_fill; }
  void LinePlot::setFill(bool o) {
    if (m_fill == o)
      return;
    m_fill = o;
    emit fillChanged();
  }
} // SDK::Quick