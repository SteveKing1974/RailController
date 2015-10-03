#include "pointsection.h"

PointSection::PointSection(TrackSection* pCommon,
                           TrackSection* pLeftBranch,
                           TrackSection* pRightBranch,
                           SwitchDirection defaultDirection,
                           QObject *parent) :
    QObject(parent),
    m_SwitchDirection(defaultDirection),
    m_pCommon(pCommon),
    m_pLeft(pLeftBranch),
    m_pRight(pRightBranch)
{
    // Set up common connections
    pCommon->connectSection(pLeftBranch, TrackSection::eLeft);
    pCommon->connectSection(pRightBranch, TrackSection::eRight);

    configureDirection();

    connect(m_pLeft, SIGNAL(leftVoltageChanged(int)), this, SIGNAL(voltageChanged()));
    connect(m_pLeft, SIGNAL(rightVoltageChanged(int)), this, SIGNAL(voltageChanged()));
    connect(m_pRight, SIGNAL(leftVoltageChanged(int)), this, SIGNAL(voltageChanged()));
    connect(m_pRight, SIGNAL(rightVoltageChanged(int)), this, SIGNAL(voltageChanged()));
    connect(m_pCommon, SIGNAL(leftVoltageChanged(int)), this, SIGNAL(voltageChanged()));
    connect(m_pCommon, SIGNAL(rightVoltageChanged(int)), this, SIGNAL(voltageChanged()));
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

void PointSection::configureDirection()
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
