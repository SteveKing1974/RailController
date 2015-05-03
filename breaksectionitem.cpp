#include "breaksectionitem.h"

#include "breaksection.h"

BreakSectionItem::BreakSectionItem(QQuickItem *parent) :
    QQuickItem(parent),
    m_pBreakSection(0),
    m_pLeft(0),
    m_pRight(0)
{
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
