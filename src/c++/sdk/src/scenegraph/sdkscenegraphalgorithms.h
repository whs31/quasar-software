#pragma once

#include <cstdint>
#include <vector>

using std::vector;

class QSGGeometry;
class QSGFlatColorMaterial;
class QSGGeometryNode;
class QString;

namespace SDK::Scenegraph
{
  struct Vertex
  {
    Vertex() : x(0), y(0) {}
    Vertex(float x, float y) : x(x), y(y) {}
    float x, y;
  };

  struct VertexT
  {
    VertexT() : x(0), y(0), u(0), v(0) {}
    VertexT(float x, float y, float u, float v) : x(x), y(y), u(u), v(v) {}
    VertexT(const Vertex &xy, float u, float v) : x(xy.x), y(xy.y), u(u), v(v) {}
    float x, y, u, v;
  };

  struct VertexC
  {
    VertexC() : x(0), y(0), r(0), g(0), b(0), a(1) {}
    VertexC(float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : x(x), y(y), r(r), g(g), b(b), a(a) {}
    float x, y;
    uint8_t r, g, b, a;
  };

  QSGGeometry* createLineStripNode(const vector<float>& v, float dx, float dy, float w, float h, float line_width = 1);
  QSGGeometry* createSimpleGraphNode(const vector<float>& v, float dx, float dy, float w, float h);

  QSGFlatColorMaterial* createFlatTransparentMaterial(const QString& col, float alpha = 1);

  QSGGeometryNode* createBackgroundNode(const QString& col, float w, float h);
  QSGGeometryNode* createLineStripNode(const vector<float>& v, float dx, float dy, float w, float h, const QString& col, float alpha = 1, float line_width = 1);
  QSGGeometryNode* createGraphNode(const vector<float>& v, float dx, float dy, float w, float h, const QString& col, float alpha = 1);

} // SDK::Scenegraph