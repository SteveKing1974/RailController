#include "tracksectionitem.h"

#include <QSGNode>
#include <QSGSimpleRectNode>
#include "tracksection.h"

TrackSectionItem::TrackSectionItem(QQuickItem *parent) :
    QQuickItem(parent),
    m_pSection(new TrackSection(this))
{
    setFlag(QQuickItem::ItemHasContents);
}

QSGNode *TrackSectionItem::updatePaintNode(QSGNode *node, UpdatePaintNodeData *)
{
    if (!node) {
        node = new QSGNode();

        node->appendChildNode(new QSGSimpleRectNode());
        node->appendChildNode(new QSGSimpleRectNode());
    }

    Q_ASSERT(node->childCount()==2);

    QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(0));
    n->setRect(0, height()/3, width(), 3);
    n->setColor(voltageToColor(m_pSection->leftVoltage()));

    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(1));
    n->setRect(0, 2*height()/3, width(), 3);
    n->setColor(voltageToColor(m_pSection->rightVoltage()));


    return node;
}

QColor TrackSectionItem::voltageToColor(int voltage) const
{
    switch (voltage)
    {
    case -1: return Qt::black;
    case 0: return Qt::black;
    case 1: return Qt::red;
    case 2: return Qt::blue;
    case 3: return Qt::green;
    default:
        Q_ASSERT(0);
        return Qt::gray;
    }
}
