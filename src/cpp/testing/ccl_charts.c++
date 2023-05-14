#include "ccl_charts.h"
#include <QtQuick/QSGGeometryNode>
#include <vector>

using namespace ccl::charts;

int State::compare(const State* other) const
{
    if(color.rgba() == other->color.rgba())
        return 0;
    if(color.rgba() < other->color.rgba())
        return -1;
    return 1;
}

Vertex::Vertex(float x, float y)
    : x(x), y(y) {}

VertexT::VertexT(float x, float y, float u, float v)
    : x(x), y(y), u(u), v(v) {}


const char* GLGradientShader::vertexShader() const {
    return "attribute highp vec4 aVertex;           \n"
           "attribute highp vec2 aTexCoord;         \n"
           "uniform highp mat4 qt_Matrix;           \n"
           "varying highp vec2 texCoord;            \n"
           "void main() {                           \n"
           "    gl_Position = qt_Matrix * aVertex;  \n"
           "    texCoord = aTexCoord;               \n"
           "}";
}

const char* GLGradientShader::fragmentShader() const {
    return "uniform lowp float qt_Opacity;                                           \n"
           "uniform lowp vec4 color;                                                 \n"
           "varying highp vec2 texCoord;                                             \n"
           "void main () {                                                           \n"
           "    gl_FragColor = 1 * min(1.3 - texCoord.y, 1.0) * color * qt_Opacity;  \n"
           "}";
}

QList<QByteArray> GLGradientShader::attributes() const {
    return QList<QByteArray>() << "aVertex" << "aTexCoord";
}

void GLGradientShader::updateState(const State* state, const State*) {
    program()->setUniformValue(id_color, state->color);
}

void GLGradientShader::resolveUniforms() {
    id_color = program()->uniformLocation("color");
}

RealtimeHistogram::RealtimeHistogram(QQuickItem* parent)
    : QQuickItem{parent}
{
    setFlag(ItemHasContents);
    //    connect(this, &RealtimeHistogram::axisColorChanged, this, &RealtimeHistogram::update);
    //    connect(this, &RealtimeHistogram::axisFontChanged, this, &RealtimeHistogram::update);
    //    connect(this, &RealtimeHistogram::histogramColorChanged, this, &RealtimeHistogram::update);
    //    connect(this, &RealtimeHistogram::backgroundColorChanged, this, &RealtimeHistogram::update);
    //    connect(this, &RealtimeHistogram::intervalChanged, this, &RealtimeHistogram::update); // add timer restart
    //    connect(this, &RealtimeHistogram::horizontalAxisMaxValue, this, &RealtimeHistogram::update);
    //    connect(this, &RealtimeHistogram::verticalAxisMaxValue, this, &RealtimeHistogram::update);
}

void RealtimeHistogram::append(float value)
{

}

QSGNode* RealtimeHistogram::updatePaintNode(QSGNode* old_node, UpdatePaintNodeData* upnd)
{
    unused_parameter(upnd);

    QSGGeometry* geometry = nullptr;
    QSGGeometryNode* node = static_cast<QSGGeometryNode*>(old_node);

    if(node == nullptr)
    {
        node = new QSGGeometryNode;

        /* Для простой заливки цветом.
        QSGFlatColorMaterial* material = new QSGFlatColorMaterial;
        material->setColor(QColor(color()));
        */

        /* Для кастомных шейдеров внутри QQI. У такого шейдера тип точки - VertexT, а не Vertex. */
        QSGSimpleMaterial<State>* material = GLGradientShader::createMaterial();
        material->setFlag(QSGMaterial::Blending);

        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
        static_cast<QSGSimpleMaterial<State>*>(node->material())->state()->color = QColor(histogramColor());

        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 0, 0, QSGGeometry::UnsignedIntType);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
    }

    geometry = node->geometry();
    geometry->setLineWidth(5);
    geometry->setDrawingMode(GL_QUADS);

    std::vector<VertexT> gl;
    gl.push_back(VertexT(0, 0, 0, 0));
    gl.push_back(VertexT(width(), 0, 1, 0));
    gl.push_back(VertexT(width(), height(), 1, 1));
    gl.push_back(VertexT(0, height(), 0, 1));

    geometry->allocate(gl.size());
    for(size_t i = 0; i < gl.size(); i++)
        geometry->vertexDataAsTexturedPoint2D()[i].set(gl.at(i).x, gl.at(i).y, gl.at(i).u, gl.at(i).v);

    node->markDirty(QSGNode::DirtyGeometry);
    return node;
}
