#include "breaksectionitem.h"

#include "breaksection.h"


#include <QSGNode>
#include <QSGSimpleRectNode>
#include <QTransform>

BreakSectionItem::BreakSectionItem(QQuickItem *parent) :
    QQuickItem(parent),
    m_pBreakSection(0),
    m_pLeft(0),
    m_pRight(0)
{
    setFlag(QQuickItem::ItemHasContents);
}

QObject *BreakSectionItem::leftSection() const
{
    return m_pLeft;
}

QObject *BreakSectionItem::rightSection() const
{
    return m_pRight;
}

void BreakSectionItem::setLeftSection(QObject *pSec)
{
    if (pSec != m_pLeft)
    {
        Q_ASSERT(m_pLeft==0);
        m_pLeft = pSec;
        createBreak();
        emit leftSectionChanged();
    }
}

void BreakSectionItem::setRightSection(QObject *pSec)
{
    if (pSec != m_pRight)
    {
        Q_ASSERT(m_pRight==0);
        m_pRight = pSec;
        createBreak();
        emit rightSectionChanged();
    }
}

bool BreakSectionItem::enabled() const
{
    return m_Enabled;
}

void BreakSectionItem::setEnabled(bool newVal)
{
    if (m_Enabled!=newVal)
    {
        m_Enabled = newVal;
        if (m_pBreakSection)
        {
            m_pBreakSection->setState(m_Enabled ? BreakSection::eSwitchOpen : BreakSection::eSwitchClosed);
        }
        emit enabledChanged();
    }
}

QSGNode *BreakSectionItem::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *)
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

        node->appendChildNode(new QSGSimpleRectNode());
    }

    Q_ASSERT(node->childCount()==6);

    QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(0));
    n->setRect(0, height()/3, width()/3, 3);
    n->setColor(Qt::black);

    QSGTransformNode* txNode = static_cast<QSGTransformNode *>(node->childAtIndex(1));
    QTransform t;
    t.translate(width()/3.0,height()/3.0);
    t.rotate(m_Enabled ? 0 : -45);
    txNode->setMatrix(QMatrix4x4(t));
    n = static_cast<QSGSimpleRectNode *>(txNode->childAtIndex(0));
    n->setRect(0, 0, width()/3, 3);
    n->setColor(Qt::black);

    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(2));
    n->setRect(2*width()/3, height()/3, width()/3, 3);
    n->setColor(Qt::black);

    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(3));
    n->setRect(0, 2*height()/3, width()/3, 3);
    n->setColor(Qt::black);

    txNode = static_cast<QSGTransformNode *>(node->childAtIndex(4));
    QTransform t2;
    t2.translate(width()/3.0,2*height()/3.0);
    t2.rotate(m_Enabled ? 0 : -45);
    txNode->setMatrix(QMatrix4x4(t2));
    n = static_cast<QSGSimpleRectNode *>(txNode->childAtIndex(0));
    n->setRect(0, 0, width()/3, 3);
    n->setColor(Qt::black);

    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(5));
    n->setRect(2*width()/3, 2*height()/3, width()/3, 3);
    n->setColor(Qt::black);


    return node;
}

void BreakSectionItem::createBreak()
{
    Q_ASSERT(m_pBreakSection==0);
    if (m_pLeft==0 || m_pRight==0)  return;

    m_pBreakSection = new BreakSection(qobject_cast<TrackSection*>(m_pLeft),
                                       qobject_cast<TrackSection*>(m_pRight),
                                       m_Enabled ? BreakSection::eSwitchOpen : BreakSection::eSwitchClosed,
                                       this);
}
