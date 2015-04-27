#ifndef POINTSECTION_H
#define POINTSECTION_H

#include <QObject>

#include "tracksection.h"

class PointSection : public QObject
{
    Q_OBJECT

    Q_PROPERTY(SwitchDirection direction READ direction WRITE setDirection NOTIFY directionChanged)

    Q_ENUMS(SwitchDirection)

public:
    enum SwitchDirection {
        eSwitchLeft,
        eSwitchRight
    };

    explicit PointSection(TrackSection* pCommon,
                          TrackSection* pLeftBranch,
                          TrackSection* pRightBranch,
                          SwitchDirection defaultDirection = eSwitchLeft,
                          QObject *parent = 0);

    SwitchDirection direction() const { return m_SwitchDirection; }

    void setDirection(SwitchDirection newVal);

signals:
    void directionChanged();

public slots:

private:
    void configureDirection();

    SwitchDirection m_SwitchDirection;
    TrackSection* m_pCommon;
    TrackSection* m_pLeft;
    TrackSection* m_pRight;
};

#endif // POINTSECTION_H
