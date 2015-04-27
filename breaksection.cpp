#include "breaksection.h"

BreakSection::BreakSection(TrackSection* pLeft,
                           TrackSection* pRight,
                           SwitchState defaultState,
                           QObject *parent) :
    QObject(parent),
    m_SwitchState(defaultState),
    m_pLeft(pLeft),
    m_pRight(pRight)
{
    configureState();
}

void BreakSection::setState(SwitchState newVal)
{
    if (newVal != m_SwitchState)
    {
        m_SwitchState = newVal;
        configureState();
    }
}

void BreakSection::configureState()
{
    if (m_SwitchState==eSwitchOpen)
    {
        m_pLeft->disconnectSection(m_pRight, TrackSection::eRight | TrackSection::eLeft);
    }
    else
    {
        m_pLeft->connectSection(m_pRight, TrackSection::eRight | TrackSection::eLeft);
    }
}
