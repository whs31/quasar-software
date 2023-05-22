#include "lpvlmatrixplot.h"
#include "LPVL/GLGeometry"
#include "LPVL/Math"
#include <QtQuick/QSGSimpleMaterial>
#include <QtQuick/QSGVertexColorMaterial>
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

    void MatrixPlot::set(const vector<float>& array2d, int rows, int columns)
    {
        data.clear();
        data.resize(rows);
        for(size_t i = 0; i < rows; ++i)
        {
                data[i].resize(columns);
                for(size_t j = 0; j < columns; ++j)
                data[i][j] = array2d[j + columns * i];
        }
        this->update();
    }

    void MatrixPlot::set(const vector<int> array2d, int rows, int columns)
    {
        data.clear();
        data.resize(rows);
        for(size_t i = 0; i < rows; ++i)
        {
                data[i].resize(columns);
                for(size_t j = 0; j < columns; ++j)
                data[i][j] = (float)array2d[j + columns * i];
        }
        this->update();
    }

    void MatrixPlot::set(const vector<uint8_t> array2d, int rows, int columns)
    {
        data.clear();
            data.resize(rows);
        for(size_t i = 0; i < rows; ++i)
        {
            data[i].resize(columns);
            for(size_t j = 0; j < columns; ++j)
                data[i][j] = (float)array2d[j + columns * i];
        }
        this->update();
    }

    QSGNode* MatrixPlot::updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*)
    {
        QSGGeometry* geometry = nullptr;
        QSGGeometryNode* node = static_cast<QSGGeometryNode*>(old_node);
        if(node == nullptr)
        {
            node = new QSGGeometryNode;

            /*QSGSimpleMaterial<State>* material = new QSGFlatColorMaterial;*//*GLGradientShader::createMaterial();*/
            /*material->setFlag(QSGMaterial::Blending);*/
            QSGVertexColorMaterial* material = new QSGVertexColorMaterial;

            node->setMaterial(material);
            node->setFlag(QSGNode::OwnsMaterial);
            /*static_cast<QSGSimpleMaterial<State>*>(node->material())->state()->color = QColor("red");*/

            geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), 0, 0, QSGGeometry::UnsignedIntType);
            node->setGeometry(geometry);
            node->setFlag(QSGNode::OwnsGeometry);
            geometry->setLineWidth(1);
            geometry->setDrawingMode(GL_POINTS);
        }

        geometry = node->geometry();

        vector<VertexC> gl;
        float dx = width() / data.front().size();
        float dy = height() / data.size();
        for(size_t row = 0; row < data.size(); ++row)
        {
            for(size_t column = 0; column < data[row].size(); ++column)
            {
                gl.push_back(VertexC(column * dx, row * dy, data[row][column], data[row][column], data[row][column], 1));
            }
        }

        geometry->allocate(gl.size());
        for(size_t i = 0; i < gl.size(); i++)
            geometry->vertexDataAsColoredPoint2D()[i].set(gl.at(i).x, gl.at(i).y,
                                                          gl.at(i).r, gl.at(i).g,
                                                          gl.at(i).b, gl.at(i).a);

        node->markDirty(QSGNode::DirtyGeometry);
        return node;
    }

} // LPVL
