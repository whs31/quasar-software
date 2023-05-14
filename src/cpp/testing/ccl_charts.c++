#include "ccl_charts.h"
#include <QtCore/QTimer>
#include <QtQuick/QSGGeometryNode>

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
    , timer(new QTimer(this))
{
    setFlag(ItemHasContents);
    timer->start(interval());
    connect(timer, &QTimer::timeout, this, [this](){
        storage_size = interval() * horizontalAxisMaxValue() / 1'000'000;
        if(storage.size() >= storage_size and storage.size() > 0)
            storage.erase(storage.begin());
        storage.push_back(stored);
        stored = 0;
        update();
    });
}

void RealtimeHistogram::append(float value)
{
    float f = value > verticalAxisMaxValue() ? verticalAxisMaxValue() : value;
    stored += f / verticalAxisMaxValue() / 2.5;
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
        geometry->setLineWidth(2);
        geometry->setDrawingMode(GL_QUADS);
    }

    geometry = node->geometry();

    vector<VertexT> gl;
    float spacing = width() / storage_size;
    float cell_size = spacing / 1.2f;
    for(size_t i = 0; i < storage.size(); ++i) {
        gl.push_back(VertexT((float)i * spacing, height() - storage[i] * height(), (float)i / storage_size, 1 - storage[i]));
        gl.push_back(VertexT((float)i * spacing, height(), (float)i / storage_size, 0));
        gl.push_back(VertexT((float)i * spacing + cell_size, height(), ((float)i * spacing + cell_size) / width(), 0));
        gl.push_back(VertexT((float)i * spacing + cell_size, height() - storage[i] * height(), ((float)i * spacing + cell_size) / width(), 1 - storage[i]));
    }

    geometry->allocate(gl.size());
    for(size_t i = 0; i < gl.size(); i++)
        geometry->vertexDataAsTexturedPoint2D()[i].set(gl.at(i).x, gl.at(i).y, gl.at(i).u, gl.at(i).v);

    node->markDirty(QSGNode::DirtyGeometry);
    return node;
}

float RealtimeHistogram::interval() const { return m_interval; }
void RealtimeHistogram::setInterval(float other)
{
    if (qFuzzyCompare(m_interval, other))
        return;
    m_interval = other;
    emit intervalChanged();

    timer->start(interval());
    storage_size = interval() * horizontalAxisMaxValue() / 1'000'000;
    storage.clear();
    update();
}

float RealtimeHistogram::horizontalAxisMaxValue() const{ return m_horizontalAxisMaxValue; }
void RealtimeHistogram::setHorizontalAxisMaxValue(float other)
{
    if (qFuzzyCompare(m_horizontalAxisMaxValue, other))
        return;
    m_horizontalAxisMaxValue = other;
    emit horizontalAxisMaxValueChanged();
    storage.clear();
    update();
}

float RealtimeHistogram::verticalAxisMaxValue() const { return m_verticalAxisMaxValue; }
void RealtimeHistogram::setVerticalAxisMaxValue(float other)
{
    if(qFuzzyCompare(m_verticalAxisMaxValue, other))
        return;
    m_verticalAxisMaxValue = other;
    emit verticalAxisMaxValueChanged();
    storage.clear();
    update();
}

QString RealtimeHistogram::histogramColor() const { return m_histogramColor; }
void RealtimeHistogram::setHistogramColor(const QString& other)
{
    if (m_histogramColor == other)
        return;
    m_histogramColor = other;
    emit histogramColorChanged();
    update();
}
