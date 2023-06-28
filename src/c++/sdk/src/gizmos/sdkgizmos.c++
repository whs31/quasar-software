#include "sdkgizmos.h"

namespace SDK::Gizmos
{

  Gizmos::Gizmos(QQuickItem* parent)
    : QQuickItem(parent)
    , m_type(Hidden)
    , m_colors({"red", "green", "blue"})
  {
    this->setFlags(ItemHasContents);
  }

  QSGNode* Gizmos::updatePaintNode(QSGNode* old_node, QQuickItem::UpdatePaintNodeData*)
  {
    return old_node;
  }

  Gizmos::GizmoType Gizmos::type() const { return m_type; }
  void Gizmos::setType(Gizmos::GizmoType o)
  {
    if(m_type == o)
      return;
    m_type = o;
    emit typeChanged();
  }

  QList<QString> Gizmos::colors() const { return m_colors; }
  void Gizmos::setColors(const QList<QString>& o)
  {
    if(m_colors == o)
      return;
    m_colors = o;
    emit colorsChanged();
  }

} // SDK::Gizmos