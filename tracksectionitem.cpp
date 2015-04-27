#include "tracksectionitem.h"

#include <QSGSimpleRectNode>

TrackSectionItem::TrackSectionItem(QQuickItem *parent) :
    QQuickItem(parent),
    m_pSection(new TrackSection(this))
{
    setFlag(QQuickItem::ItemHasContents);
}

QSGNode *TrackSectionItem::updatePaintNode(QSGNode *node, UpdatePaintNodeData *)
{
    QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>(node);
    if (!n) {
        n = new QSGSimpleRectNode();
        n->setColor(Qt::red);
    }
    n->setRect(boundingRect());
    return n;
}
