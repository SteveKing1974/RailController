#include "powersupply.h"
#include "tracksection.h"
#include <QDebug>
#include <QTimer>

PowerSupply::PowerSupply(QQuickItem *parent) :
    QQuickItem(parent),
    m_LeftVoltage(-1),
    m_RightVoltage(-1),
    m_ConnectedSection(0)
{
}

QObject* PowerSupply::connectedSection() const
{
    return m_ConnectedSection;
}

void PowerSupply::setConnectedSection(QObject *pArg)
{
    if (pArg != m_ConnectedSection)
    {
        if (m_ConnectedSection)
        {
            m_ConnectedSection->setLeftVoltage(-1);
            m_ConnectedSection->setRightVoltage(-1);
            disconnect(m_ConnectedSection, 0, this, 0);
        }
        m_ConnectedSection = qobject_cast<TrackSection*>(pArg);
        if (m_ConnectedSection)
        {
            connect(m_ConnectedSection, SIGNAL(leftVoltageChanged(int)), this, SLOT(sectionVoltageChanged()));
            connect(m_ConnectedSection, SIGNAL(rightVoltageChanged(int)), this, SLOT(sectionVoltageChanged()));
            m_ConnectedSection->setLeftVoltage(m_LeftVoltage);
            m_ConnectedSection->setRightVoltage(m_RightVoltage);
        }
    }
}

void PowerSupply::setLeftVoltage(int val)
{
    if (val != m_LeftVoltage)
    {
        m_LeftVoltage = val;
        if (m_ConnectedSection)
        {
            m_ConnectedSection->setLeftVoltage(m_LeftVoltage);
        }
        emit leftVoltageChanged();
    }
}

void PowerSupply::setRightVoltage(int val)
{
    if (val != m_RightVoltage)
    {
        m_RightVoltage = val;
        if (m_ConnectedSection)
        {
            m_ConnectedSection->setRightVoltage(m_RightVoltage);
        }
        emit rightVoltageChanged();
    }
}

void PowerSupply::sectionVoltageChanged()
{
    QTimer::singleShot(100, this, SLOT(correctVoltages()));
}

void PowerSupply::correctVoltages()
{
    if (m_ConnectedSection)
    {
        if (m_ConnectedSection->leftVoltage()==-1)
        {
            m_ConnectedSection->setLeftVoltage(m_LeftVoltage);
        }
        else if (m_ConnectedSection->leftVoltage() != m_LeftVoltage)
        {
            qDebug() << "Crapped out";
        }

        if (m_ConnectedSection->rightVoltage()==-1)
        {
            m_ConnectedSection->setRightVoltage(m_RightVoltage);
        }
        else if (m_ConnectedSection->rightVoltage() != m_RightVoltage)
        {
            qDebug() << "Crapped out";
        }
    }
}
