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
    m_pRight(0),
    m_pCommon(0)
{
    QObject* pModel = qApp->property("LineStateModel").value<QObject*>();
    connect(this, SIGNAL(sectionCreated(QString,PointSection*)), pModel, SLOT(regsiterItem(QString, PointSection*)));
    connect(this, SIGNAL(objectNameChanged(QString)), this, SLOT(nameChanged(QString)));

    setLeftSection(new TrackSection(this));
    setRightSection(new TrackSection(this));
    setCommonSection(new TrackSection(this));

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

void PointSectionItem::setLeftSection(QObject *pArg)
{
    TrackSection* pSec = qobject_cast<TrackSection*>(pArg);
    if (pSec != m_pLeft)
    {
        Q_ASSERT(m_pLeft==0);
        m_pLeft = pSec;
        createPoint();
        emit leftSectionChanged();
    }
}

void PointSectionItem::setRightSection(QObject *pArg)
{
    TrackSection* pSec = qobject_cast<TrackSection*>(pArg);
    if (pSec != m_pRight)
    {
        Q_ASSERT(m_pRight==0);
        m_pRight = pSec;
        createPoint();
        emit rightSectionChanged();
    }
}

void PointSectionItem::setCommonSection(QObject *pArg)
{
    TrackSection* pSec = qobject_cast<TrackSection*>(pArg);
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
        update();
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

        node->appendChildNode(new QSGSimpleRectNode());
        node->appendChildNode(new QSGSimpleRectNode());
        node->appendChildNode(new QSGSimpleRectNode());
    }

    Q_ASSERT(node->childCount()==9);

    const qreal midPoint = width() / 2.0;
    const qreal lineWidth = 3.0;
    const qreal heightVal = height()/3.0;
    const qreal straightLength = midPoint - 3.0*heightVal / 2.0;
    const qreal topLine = height()/3.0 - lineWidth/2;
    const qreal angleLength = 1.5 * height()/3.0;
    const qreal bottomLine = 2.0*height()/3.0 - lineWidth/2;

    // Bottom line
    QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(0));
    n->setRect(0, bottomLine, width(), lineWidth);
    n->setColor(TrackSection::voltageToColor(m_pCommon->rightVoltage()));

    // Angle left from top line
    QSGTransformNode* txNode = static_cast<QSGTransformNode *>(node->childAtIndex(1));
    QTransform t;
    t.translate(straightLength-4, heightVal);
    t.rotate(-45);
    txNode->setMatrix(QMatrix4x4(t));
    n = static_cast<QSGSimpleRectNode *>(txNode->childAtIndex(0));
    n->setRect(0, 0, angleLength, lineWidth);
    n->setColor(TrackSection::voltageToColor(m_pLeft->leftVoltage()));

    // Common side
    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(2));
    n->setRect(0, topLine, straightLength, lineWidth);
    n->setColor(TrackSection::voltageToColor(m_pCommon->leftVoltage()));

        // Right side, top
    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(3));
    n->setRect(midPoint-heightVal/2.0, topLine, straightLength + 2*heightVal, lineWidth);
    n->setColor(TrackSection::voltageToColor(m_pRight->leftVoltage()));

    // Angle right from top line
    txNode = static_cast<QSGTransformNode *>(node->childAtIndex(4));
    QTransform t2;
    t2.translate(midPoint-heightVal/2.0 + 1, topLine);
    t2.rotate(-45);
    txNode->setMatrix(QMatrix4x4(t2));
    n = static_cast<QSGSimpleRectNode *>(txNode->childAtIndex(0));
    n->setRect(0, 0, angleLength, lineWidth);
    n->setColor(TrackSection::voltageToColor(m_pLeft->rightVoltage()));

    // Switch node
    txNode = static_cast<QSGTransformNode *>(node->childAtIndex(5));
    QTransform t3;
    n = static_cast<QSGSimpleRectNode *>(txNode->childAtIndex(0));

    if (m_Direction)
    {
        t3.translate(straightLength,topLine);
        t3.rotate(0);
        n->setRect(0, 0, heightVal, lineWidth);
    }
    else
    {
        t3.translate(straightLength,bottomLine);
        t3.rotate(-45);
        n->setRect(0, 0, angleLength, lineWidth);
    }


    txNode->setMatrix(QMatrix4x4(t3));
    n->setColor(m_Direction ? TrackSection::voltageToColor(m_pCommon->leftVoltage()) : TrackSection::voltageToColor(m_pCommon->rightVoltage()));

    // Debug display of squares
#if 0
    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(6));
    n->setRect(0, height()/2, 10, 10);
    n->setColor(Qt::red);

    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(7));
    n->setRect(width() - 10, height()/2, 10, 10);
    n->setColor(Qt::green);

    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(8));
    n->setRect(width()/2, 10, 10, 10);
    n->setColor(Qt::blue);
#endif

    return node;
}

void PointSectionItem::nameChanged(const QString &newName)
{
    emit sectionCreated(objectName(), m_pPointSection);
}

void PointSectionItem::createPoint()
{
    Q_ASSERT(m_pPointSection==0);
    if (m_pLeft==0 || m_pRight==0 || m_pCommon==0)  return;

    m_pPointSection = new PointSection(qobject_cast<TrackSection*>(m_pCommon),
                                       qobject_cast<TrackSection*>(m_pLeft),
                                       qobject_cast<TrackSection*>(m_pRight),
                                       static_cast<PointSection::SwitchDirection>(m_Direction),
                                       this);

     connect(m_pPointSection, SIGNAL(voltageChanged()), this, SLOT(update()));

     emit sectionCreated(objectName(), m_pPointSection);
}
