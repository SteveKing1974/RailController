#include "breaksection.h"

BreakSection::BreakSection(TrackSection* pLeft,
                           TrackSection* pRight,
                           SwitchState defaultState,
                           QObject *parent) :
    m_pLeft(pLeft),
    m_pRight(pRight),
    m_SwitchState(defaultState),
    QObject(parent)
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
