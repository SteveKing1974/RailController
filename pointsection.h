#ifndef POINTSECTION_H
#define POINTSECTION_H

#include <QObject>

#include "tracksection.h"

class PointSection : public QObject
{
    Q_OBJECT

    Q_PROPERTY(SwitchDirection direction READ direction WRITE setDirection NOTIFY directionChaned)

    Q_ENUMS(SwitchDirection)

public:
    enum {
        eSwitchLeft,
        eSwitchRight
    } SwitchDirection;

    explicit PointSection(TrackSection* pCommon,
                          TrackSection* pLeftBranch,
                          TrackSection* pRightBranch,
                          SwitchDirection defaultDirection = eSwitchLeft,
                          QObject *parent = 0);

    void direction() const { return m_SwitchDirection; }

    void setDirection(SwitchDirection newVal);

signals:
    void directionChanged();

public slots:

private:
    void confirgureDirection();

    SwitchDirection m_SwitchDirection;
    TrackSection* m_pCommon;
    TrackSection* m_pLeft;
    TrackSection* m_pRight;
};

#endif // POINTSECTION_H
