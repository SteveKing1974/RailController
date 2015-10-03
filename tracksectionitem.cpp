#include "tracksectionitem.h"

#include <QSGNode>
#include <QSGSimpleRectNode>
#include "tracksection.h"

TrackSectionItem::TrackSectionItem(QQuickItem *parent) :
    QQuickItem(parent),
    m_pSection(new TrackSection(this))
{
    connect(m_pSection, SIGNAL(leftVoltageChanged(int)), this, SLOT(update()));
    connect(m_pSection, SIGNAL(rightVoltageChanged(int)), this, SLOT(update()));
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

    const qreal lineWidth = 3.0;
    const qreal topLine = height()/3.0 - lineWidth/2;
    const qreal bottomLine = 2.0*height()/3.0 - lineWidth/2;


    QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(0));
    n->setRect(0, topLine, width(), lineWidth);
    n->setColor( TrackSection::voltageToColor(m_pSection->leftVoltage()));

    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(1));
    n->setRect(0, bottomLine, width(), lineWidth);
    n->setColor( TrackSection::voltageToColor(m_pSection->rightVoltage()));


    return node;
}

