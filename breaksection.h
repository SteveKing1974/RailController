#ifndef BREAKSECTION_H
#define BREAKSECTION_H

#include <QObject>

#include "tracksection.h"

class BreakSection : public QObject
{
    Q_OBJECT

    Q_PROPERTY(SwitchState state READ state WRITE setState NOTIFY stateChaned)

    Q_ENUMS(SwitchState)

public:
    enum {
        eSwitchOpen,
        eSwitchClosed
    } SwitchState;

    explicit BreakSection(TrackSection* pLeftBranch,
                          TrackSection* pRightBranch,
                          SwitchState defaultState = eSwitchOpen,
                          QObject *parent = 0);



    void state() const { return m_SwitchState; }

    void setState(SwitchState newVal);

signals:
    void stateChaned();

public slots:

private:
    void configureState();

    SwitchState m_SwitchState;
    TrackSection* m_pLeft;
    TrackSection* m_pRight;
};

#endif // BREAKSECTION_H
