#include "tracksection.h"
#include <QDebug>

TrackSection::TrackSection(QObject *parent) :
    QObject(parent),
    m_LeftVoltage(-1),
    m_RightVoltage(-1)
{
}

void TrackSection::setLeftVoltage(int val)
{
    if (val != m_LeftVoltage)
    {
        qDebug() << "Left voltage of" << this << "is" << val << "Current" << m_LeftVoltage;
        m_LeftVoltage  = val;
        emit leftVoltageChanged(val);
    }
}



void TrackSection::setRightVoltage(int val)
{
    if (val != m_RightVoltage)
    {
        qDebug() << "Right voltage of" << this << "is" << val;
        m_RightVoltage  = val;
        emit rightVoltageChanged(val);
    }
}


QColor TrackSection::voltageToColor(int voltage)
{
    switch (voltage)
    {
    case -1: return Qt::black;
    case 0: return Qt::black;
    case 1: return Qt::red;
    case 2: return Qt::blue;
    case 3: return Qt::green;
    default:
        Q_ASSERT(0);
        return Qt::gray;
    }
}

void TrackSection::connectSection(TrackSection* pSec, int arg)
{
    const Sides s(arg);
    if (s.testFlag(eLeft))
    {
        connect(this, SIGNAL(leftVoltageChanged(int)), pSec, SLOT(setLeftVoltage(int)));
        connect(pSec, SIGNAL(leftVoltageChanged(int)), this, SLOT(setLeftVoltage(int)));

        if (m_LeftVoltage != pSec->leftVoltage())
        {
            if (m_LeftVoltage == -1)
            {
                setLeftVoltage(pSec->leftVoltage());
            }
            else
            {
                pSec->setLeftVoltage(m_LeftVoltage);
            }
        }
    }
    if (s.testFlag(eRight))
    {
        connect(this, SIGNAL(rightVoltageChanged(int)), pSec, SLOT(setRightVoltage(int)));
        connect(pSec, SIGNAL(rightVoltageChanged(int)), this, SLOT(setRightVoltage(int)));

        if (m_RightVoltage != pSec->rightVoltage())
        {
            if (m_RightVoltage == -1)
            {
                setRightVoltage(pSec->rightVoltage());
            }
            else
            {
                pSec->setRightVoltage(m_RightVoltage);
            }
        }
    }
}

void TrackSection::disconnectSection(TrackSection* pSec, int arg)
{
    const Sides s(arg);
    if (s.testFlag(eLeft))
    {
        disconnect(this, SIGNAL(leftVoltageChanged(int)), pSec, SLOT(setLeftVoltage(int)));
        disconnect(pSec, SIGNAL(leftVoltageChanged(int)), this, SLOT(setLeftVoltage(int)));

        setLeftVoltage(-1);
        pSec->setLeftVoltage(-1);
    }
    if (s.testFlag(eRight))
    {
        disconnect(this, SIGNAL(rightVoltageChanged(int)), pSec, SLOT(setRightVoltage(int)));
        disconnect(pSec, SIGNAL(rightVoltageChanged(int)), this, SLOT(setRightVoltage(int)));

        setRightVoltage(-1);
        pSec->setRightVoltage(-1);
    }
}
