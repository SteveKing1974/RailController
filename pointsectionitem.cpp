#include "pointsectionitem.h"

#include "pointsection.h"


#include <QSGNode>
#include <QSGSimpleRectNode>
#include <QTransform>

PointSectionItem::PointSectionItem(QQuickItem *parent) :
    QQuickItem(parent),
    m_Direction(PointSection::eSwitchLeft),
    m_pPointSection(0),
    m_pLeft(0),
    m_pRight(0)
{
    setFlag(QQuickItem::ItemHasContents);
}

QObject *PointSectionItem::leftSection() const
{
    return m_pLeft;
}

QObject *PointSectionItem::rightSection() const
{
    return m_pRight;
}

QObject *PointSectionItem::commonSection() const
{
    return m_pCommon;
}

void PointSectionItem::setLeftSection(QObject *pSec)
{
    if (pSec != m_pLeft)
    {
        Q_ASSERT(m_pLeft==0);
        m_pLeft = pSec;
        createPoint();
        emit leftSectionChanged();
    }
}

void PointSectionItem::setRightSection(QObject *pSec)
{
    if (pSec != m_pRight)
    {
        Q_ASSERT(m_pRight==0);
        m_pRight = pSec;
        createPoint();
        emit rightSectionChanged();
    }
}

void PointSectionItem::setCommonSection(QObject *pSec)
{
    if (pSec != m_pCommon)
    {
        Q_ASSERT(m_pCommon==0);
        m_pCommon = pSec;
        createPoint();
        emit commonSectionChanged();
    }
}

bool PointSectionItem::direction() const
{
    return m_Direction;
}

void PointSectionItem::setDirection(int newVal)
{
    if (m_Direction!=newVal)
    {
        m_Direction = newVal;
        if (m_pPointSection)
        {
            m_pPointSection->setDirection(static_cast<PointSection::SwitchDirection>(m_Direction));
        }
        emit directionChanged();
    }
}

QSGNode *PointSectionItem::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *)
{
    if (!node) {
        node = new QSGNode();

        node->appendChildNode(new QSGSimpleRectNode());

        QSGTransformNode* txNode = new QSGTransformNode();
        node->appendChildNode(txNode);
        txNode->appendChildNode(new QSGSimpleRectNode());

        node->appendChildNode(new QSGSimpleRectNode());
        node->appendChildNode(new QSGSimpleRectNode());

        txNode = new QSGTransformNode();
        node->appendChildNode(txNode);
        txNode->appendChildNode(new QSGSimpleRectNode());

        txNode = new QSGTransformNode();
        node->appendChildNode(txNode);
        txNode->appendChildNode(new QSGSimpleRectNode());
    }

    Q_ASSERT(node->childCount()==6);

    // Bottom line
    QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(0));
    n->setRect(0, 2*height()/3, width(), 3);
    n->setColor(Qt::black);

    QSGTransformNode* txNode = static_cast<QSGTransformNode *>(node->childAtIndex(1));
    QTransform t;
    t.translate(width()/3.0,height()/3.0);
    t.rotate(m_Direction ? 0 : -45);
    txNode->setMatrix(QMatrix4x4(t));
    n = static_cast<QSGSimpleRectNode *>(txNode->childAtIndex(0));
    n->setRect(0, 0, width()/3, 3);
    n->setColor(Qt::black);

    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(2));
    n->setRect(0, height()/3, width()/3, 3);
    n->setColor(Qt::black);

    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(3));
    n->setRect(2*width()/3, height()/3, width()/3, 3);
    n->setColor(Qt::black);

    txNode = static_cast<QSGTransformNode *>(node->childAtIndex(4));
    QTransform t2;
    t2.translate(2*width()/3.0,height()/3.0);
    t2.rotate(m_Direction ? 0 : -45);
    txNode->setMatrix(QMatrix4x4(t2));
    n = static_cast<QSGSimpleRectNode *>(txNode->childAtIndex(0));
    n->setRect(0, 0, width()/3, 3);
    n->setColor(Qt::black);

    txNode = static_cast<QSGTransformNode *>(node->childAtIndex(5));
    QTransform t3;
    t3.translate(width()/3.0,2*height()/3.0);
    t3.rotate(m_Direction ? 0 : -45);
    txNode->setMatrix(QMatrix4x4(t3));
    n = static_cast<QSGSimpleRectNode *>(txNode->childAtIndex(0));
    n->setRect(0, 0, 1.4*width()/3, 3);
    n->setColor(Qt::black);


    return node;
}

void PointSectionItem::createPoint()
{
    Q_ASSERT(m_pPointSection==0);
    if (m_pLeft==0 || m_pRight==0 || m_pCommon==0)  return;

    m_pPointSection = new PointSection(qobject_cast<TrackSection*>(m_pLeft),
                                       qobject_cast<TrackSection*>(m_pRight),
                                       qobject_cast<TrackSection*>(m_pCommon),
                                       static_cast<PointSection::SwitchDirection>(m_Direction),
                                       this);
}
