#ifndef BREAKSECTION_H
#define BREAKSECTION_H

#include <QObject>

#include "tracksection.h"

class BreakSection : public QObject
{
    Q_OBJECT

    Q_PROPERTY(SwitchState state READ state WRITE setState NOTIFY stateChanged)

    Q_ENUMS(SwitchState)

public:
    enum SwitchState {
        eSwitchOpen,
        eSwitchClosed
    };

    explicit BreakSection(TrackSection* pLeftBranch,
                          TrackSection* pRightBranch,
                          SwitchState defaultState = eSwitchOpen,
                          QObject *parent = 0);



    SwitchState state() const { return m_SwitchState; }

    void setState(SwitchState newVal);

signals:
    void stateChanged();
    void voltageChanged();


private:
    void configureState();

    SwitchState m_SwitchState;
    TrackSection* m_pLeft;
    TrackSection* m_pRight;
};


#endif // BREAKSECTION_H
