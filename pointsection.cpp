#include "pointsection.h"

PointSection::PointSection(TrackSection* pCommon,
                           TrackSection* pLeftBranch,
                           TrackSection* pRightBranch,
                           SwitchDirection defaultDirection,
                           QObject *parent) :
    m_pCommon(pCommon),
    m_pLeft(pLeftBranch),
    m_pRight(pRightBranch),
    m_SwitchDirection(defaultDirection),
    QObject(parent)
{
    // Set up common connections
    pCommon->connectSection(pLeftBranch, TrackSection::eLeft);
    pCommon->connectSection(pRightBranch, TrackSection::eRight);

    confirgureDirection();
}

void PointSection::setDirection(SwitchDirection newVal)
{
    if (newVal!= m_SwitchDirection)
    {
        m_SwitchDirection= newVal;

        configureDirection();
        emit directionChanged();
    }
}

void PointSection::confirgureDirection()
{
    if (m_SwitchDirection==eSwitchLeft)
    {
        m_pCommon->disconnectSection(m_pRight, TrackSection::eLeft);
        m_pCommon->connectSection(m_pLeft, TrackSection::eRight);
    }
    else
    {
        m_pCommon->disconnectSection(m_pLeft, TrackSection::eRight);
        m_pCommon->connectSection(m_pRight, TrackSection::eLeft);
    }
}
