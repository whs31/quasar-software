#pragma once

#include <definitions.h>
#include <QtQuick/QQuickItem>
#include <QtQuick/QSGRenderNode>
#include <QtGui/QImage>

struct ImGuiContext;
class QOpenGLTexture;
class QOpenGLShaderProgram;
class QOpenGLBuffer;
class QOpenGLVertexArrayObject;
class ImGuiInputEventFilter;

class ImGuiRenderer : public QSGRenderNode
{
    public:
        struct FrameDesc
        {
            QVector<QImage> textures;

            struct Cmd
            {
                uint elemCount;
                const void *indexOffset;
                QPointF scissorPixelBottomLeft;
                QSizeF scissorPixelSize;
                uint textureIndex;
            };

            struct CmdListEntry
            {
                QByteArray vbuf;
                QByteArray ibuf;
                QVector<Cmd> cmds;
            };

            QVector<CmdListEntry> cmdList;
        };

    private:
        QPointF m_scenePixelPosBottomLeft;
        QSizeF m_itemPixelSize;
        QSizeF m_itemSize;
        float m_dpr;
        FrameDesc m_frameDesc;
        QVector<QOpenGLTexture*> m_textures;
        QOpenGLShaderProgram* m_program = nullptr;
        int m_mvpLoc;
        int m_texLoc;
        int m_opacityLoc;
        QOpenGLVertexArrayObject* m_vao = nullptr;
        QOpenGLBuffer* m_vbo = nullptr;
        QOpenGLBuffer* m_ibo = nullptr;

        friend class ImGuiItem;

    public:
        ImGuiRenderer();
        ~ImGuiRenderer();

        void render(const RenderState *state) override;
        void releaseResources() override;
        StateFlags changedStates() const override;
        RenderingFlags flags() const override;
        QRectF rect() const override;
};

class ImGuiItem : public QQuickItem
{
    Q_OBJECT

    public:
        ImGuiItem(QQuickItem *parent = nullptr);
        ~ImGuiItem();

        signals:
            __signal frame();

    private:
        QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*) override;
        void itemChange(ItemChange, const ItemChangeData&) override;
        void updatePolish() override;

        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void mouseDoubleClickEvent(QMouseEvent* event) override;

        #if QT_CONFIG(wheelevent)
        void wheelEvent(QWheelEvent *event) override;
        #endif

        void hoverMoveEvent(QHoverEvent* event) override;
        void touchEvent(QTouchEvent* event) override;

        void initialize();
        void cleanup();

        void setInputEventSource(QObject* src);
        void updateInput();

        QQuickWindow* m_w = nullptr;
        qreal m_dpr;
        QMetaObject::Connection m_c;
        ImGuiContext* m_imGuiContext = nullptr;
        ImGuiRenderer::FrameDesc m_frameDesc;
        bool m_inputInitialized = false;
        ImGuiInputEventFilter* m_inputEventFilter = nullptr;
        QObject* m_inputEventSource = nullptr;
        QObject m_dummy;
};

