#include "lpvlmatrixplot.h"
#include "LPVL/GLGeometry"
#include "LPVL/Math"
#include <QtQuick/QSGSimpleMaterial>
#include <QtQuick/QSGGeometryNode>

namespace LPVL
{

LPVL_REGISTER_QML("LPVLMatrixPlot", "LPVL.Charts");

struct State
{
    QColor color;
    int compare(const State* other) const
    {
        if(color.rgba() == other->color.rgba())
            return 0;
        if(color.rgba() < other->color.rgba())
            return -1;
        return 1;
    }
};

class GLGradientShader : public QSGSimpleMaterialShader<State>
{
    QSG_DECLARE_SIMPLE_COMPARABLE_SHADER(GLGradientShader, State)

    public:
        const char* vertexShader() const override
        {
            return "attribute highp vec4 aVertex;           \n"
                   "attribute highp vec2 aTexCoord;         \n"
                   "uniform highp mat4 qt_Matrix;           \n"
                   "varying highp vec2 texCoord;            \n"
                   "void main() {                           \n"
                   "    gl_Position = qt_Matrix * aVertex;  \n"
                   "    texCoord = aTexCoord;               \n"
                   "}";
        }
        const char* fragmentShader() const override
        {
            return "uniform lowp float qt_Opacity;                                           \n"
                   "uniform lowp vec4 color;                                                 \n"
                   "varying highp vec2 texCoord;                                             \n"
                   "void main () {                                                           \n"
                   "    gl_FragColor = 1 * min(1.3 - texCoord.y, 1.0) * color * qt_Opacity;  \n"
                   "}";
        }
        QList<QByteArray> attributes() const override
        {
            return QList<QByteArray>() << "aVertex" << "aTexCoord";
        }
        void updateState(const State* state, const State*) override
        {
            program()->setUniformValue(id_color, state->color);
        }
        void resolveUniforms() override
        {
            id_color = program()->uniformLocation("color");
        }

    private:
        int id_color;
};

MatrixPlot::MatrixPlot(QQuickItem* parent)
    : QQuickItem{parent}
{
    setFlag(ItemHasContents);
}

void MatrixPlot::set(const QVector<QVector<float> >& array2d)
{

}

void MatrixPlot::set(const vector<vector<int> > array2d)
{

}

void MatrixPlot::set(const vector<vector<uint8_t> > array2d)
{

}

QSGNode* MatrixPlot::updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*)
{
    QSGGeometry* geometry = nullptr;
    QSGGeometryNode* node = static_cast<QSGGeometryNode*>(old_node);
    if(node == nullptr)
    {
        node = new QSGGeometryNode;

        QSGSimpleMaterial<State>* material = GLGradientShader::createMaterial();
        material->setFlag(QSGMaterial::Blending);

        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
        static_cast<QSGSimpleMaterial<State>*>(node->material())->state()->color = QColor("red");

        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 0, 0, QSGGeometry::UnsignedIntType);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        geometry->setLineWidth(2);
        geometry->setDrawingMode(GL_POINTS);
    }

    geometry = node->geometry();

    vector<VertexT> gl;
//    float spacing = width() / storage_size;
//    float cell_size = spacing / 1.2f;
//    for(size_t i = 0; i < storage.size(); ++i) {
//            gl.push_back(VertexT((float)i * spacing, height() - storage[i] * height(), (float)i / storage_size, 1 - storage[i]));
//            gl.push_back(VertexT((float)i * spacing, height(), (float)i / storage_size, 0));
//            gl.push_back(VertexT((float)i * spacing + cell_size, height(), ((float)i * spacing + cell_size) / width(), 0));
//            gl.push_back(VertexT((float)i * spacing + cell_size, height() - storage[i] * height(), ((float)i * spacing + cell_size) / width(), 1 - storage[i]));
//    }

    geometry->allocate(gl.size());
    for(size_t i = 0; i < gl.size(); i++)
            geometry->vertexDataAsTexturedPoint2D()[i].set(gl.at(i).x, gl.at(i).y, gl.at(i).u, gl.at(i).v);

    node->markDirty(QSGNode::DirtyGeometry);
    return node;

}

} // LPVL
