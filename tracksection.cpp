#include "tracksection.h"

TrackSection::TrackSection(QObject *parent) :
    QObject(parent)
{
}

void TrackSection::setLeftVoltage(int val)
{
    if (val != m_LeftVoltage)
    {
        m_LeftVoltage  = val;
        emit leftVoltageChanged();
    }
}

void TrackSection::setRightVoltage(int val)
{
    if (val != m_RightVoltage)
    {
        m_RightVoltage  = val;
        emit rightVoltageChanged();
    }
}

void TrackSection::connectSection(TrackSection* pSec, Sides s)
{
    if (s.testFlag(eLeft))
    {
        connect(this, SIGNAL(leftVoltageChanged(int)), pSec, SLOT(setLeftVoltage(int)));
        connect(pSec, SIGNAL(leftVoltageChanged(int)), this, SLOT(setLeftVoltage(int)));
    }
    if (s.testFlag(eRight))
    {
        connect(this, SIGNAL(rightVoltageChanged(int)), pSec, SLOT(setRightVoltage(int)));
        connect(pSec, SIGNAL(rightVoltageChanged(int)), this, SLOT(setRightVoltage(int)));
    }
}

void TrackSection::disconnectSection(TrackSection* pSec, Sides s)
{
    if (s.testFlag(eLeft))
    {
        disconnect(this, SIGNAL(leftVoltageChanged(int)), pSec, SLOT(setLeftVoltage(int)));
        disconnect(pSec, SIGNAL(leftVoltageChanged(int)), this, SLOT(setLeftVoltage(int)));
    }
    if (s.testFlag(eRight))
    {
        disconnect(this, SIGNAL(rightVoltageChanged(int)), pSec, SLOT(setRightVoltage(int)));
        disconnect(pSec, SIGNAL(rightVoltageChanged(int)), this, SLOT(setRightVoltage(int)));
    }
}
