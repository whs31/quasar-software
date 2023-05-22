#include "lpvlmatrixplot.h"
#include "LPVL/GLGeometry"
#include "LPVL/Math"
#include <QtQuick/QSGSimpleMaterial>

namespace LPVL
{

__attribute__((constructor)) static void register_qml() {
    qmlRegisterType<MatrixPlot>("LPVL.Charts", 1, 0, "LPVLMatrixPlot");
}

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

} // LPVL
