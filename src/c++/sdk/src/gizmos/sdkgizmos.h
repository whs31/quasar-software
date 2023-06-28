#pragma once

#include <QtCore/QList>
#include <QtQuick/QQuickItem>

namespace SDK::Gizmos
{
  class Gizmos : public QQuickItem
  {
    Q_OBJECT

    public:
      enum GizmoType
      {
        Move,
        Rotate,
        Scale,
        Hidden
      };

    private:
      Q_ENUM(GizmoType)
      Q_PROPERTY(GizmoType type READ type WRITE setType NOTIFY typeChanged)
      Q_PROPERTY(QList<QString> colors READ colors WRITE setColors NOTIFY colorsChanged)

    public:
      explicit Gizmos(QQuickItem* parent = nullptr);

      [[nodiscard]] GizmoType type() const; void setType(GizmoType);
      [[nodiscard]] QList<QString> colors() const; void setColors(const QList<QString>&);

    signals:
      void typeChanged();
      void colorsChanged();

    protected:
      QSGNode* updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*) final;

    private:
      GizmoType m_type;
      QList<QString> m_colors;
  };
} // SDK::Gizmos