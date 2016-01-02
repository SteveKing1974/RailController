#include "breaksectionitem.h"

#include "breaksection.h"


#include <QSGNode>
#include <QSGSimpleRectNode>
#include <QTransform>

BreakSectionItem::BreakSectionItem(QQuickItem *parent) :
    QQuickItem(parent),
    m_pBreakSection(0),
    m_pLeft(0),
    m_pRight(0),
    m_Enabled(false)
{
    QObject* pModel = qApp->property("LineStateModel").value<QObject*>();
    connect(this, SIGNAL(sectionCreated(QString,BreakSection*)), pModel, SLOT(regsiterItem(QString, BreakSection*)));
    connect(this, SIGNAL(objectNameChanged(QString)), this, SLOT(nameChanged(QString)));

    setLeftSection(new TrackSection(this));
    setRightSection(new TrackSection(this));
    setFlag(QQuickItem::ItemHasContents);

    connect(this, SIGNAL(enabledChanged()), this, SLOT(update()));
}

QObject *BreakSectionItem::leftSection() const
{
    return m_pLeft;
}

QObject *BreakSectionItem::rightSection() const
{
    return m_pRight;
}

void BreakSectionItem::setLeftSection(QObject *pArg)
{
    TrackSection* pSec = qobject_cast<TrackSection*>(pArg);
    if (pSec != m_pLeft)
    {
        Q_ASSERT(m_pLeft==0);
        m_pLeft = pSec;
        createBreak();
        emit leftSectionChanged();
    }
}

void BreakSectionItem::setRightSection(QObject *pArg)
{
    TrackSection* pSec = qobject_cast<TrackSection*>(pArg);
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
            m_pBreakSection->setState(m_Enabled ? BreakSection::eSwitchClosed : BreakSection::eSwitchOpen);
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

    const qreal heightVal = height()/3.0;
    const qreal midPoint = width() / 2.0;
    const qreal lineWidth = 3.0;
    const qreal straightLength = midPoint - heightVal/2.0;
    const qreal topLine = height()/3.0 - lineWidth/2;
    const qreal bottomLine = 2.0*height()/3.0 - lineWidth/2;

    QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(0));
    n->setRect(0, topLine, straightLength, lineWidth);
    n->setColor(TrackSection::voltageToColor(m_pLeft->leftVoltage()));

    QSGTransformNode* txNode = static_cast<QSGTransformNode *>(node->childAtIndex(1));
    QTransform t;
    t.translate(straightLength,topLine);
    t.rotate(m_Enabled ? 0 : -45);
    txNode->setMatrix(QMatrix4x4(t));
    n = static_cast<QSGSimpleRectNode *>(txNode->childAtIndex(0));
    n->setRect(0, 0, heightVal, lineWidth);
    n->setColor(TrackSection::voltageToColor(m_pLeft->leftVoltage()));

    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(2));
    n->setRect(midPoint + heightVal/2, topLine, straightLength, lineWidth);
    n->setColor(TrackSection::voltageToColor(m_pRight->leftVoltage()));

    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(3));
    n->setRect(0, bottomLine, straightLength, lineWidth);
    n->setColor(TrackSection::voltageToColor(m_pLeft->rightVoltage()));

    txNode = static_cast<QSGTransformNode *>(node->childAtIndex(4));
    QTransform t2;
    t2.translate(straightLength,bottomLine);
    t2.rotate(m_Enabled ? 0 : -45);
    txNode->setMatrix(QMatrix4x4(t2));
    n = static_cast<QSGSimpleRectNode *>(txNode->childAtIndex(0));
    n->setRect(0, 0, heightVal, lineWidth);
    n->setColor(TrackSection::voltageToColor(m_pLeft->rightVoltage()));

    n = static_cast<QSGSimpleRectNode *>(node->childAtIndex(5));
    n->setRect(midPoint + heightVal/2, bottomLine, straightLength, lineWidth);
    n->setColor(TrackSection::voltageToColor(m_pRight->rightVoltage()));


    return node;
}

void BreakSectionItem::nameChanged(const QString &newName)
{
    emit sectionCreated(objectName(), m_pBreakSection);
}

void BreakSectionItem::createBreak()
{
    Q_ASSERT(m_pBreakSection==0);
    if (m_pLeft==0 || m_pRight==0)  return;

    m_pBreakSection = new BreakSection(qobject_cast<TrackSection*>(m_pLeft),
                                       qobject_cast<TrackSection*>(m_pRight),
                                       m_Enabled ? BreakSection::eSwitchClosed : BreakSection::eSwitchOpen,
                                       this);
    connect(m_pBreakSection, SIGNAL(voltageChanged()), this, SLOT(update()));

    emit sectionCreated(objectName(), m_pBreakSection);
}
