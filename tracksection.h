#ifndef TRACKSECTION_H
#define TRACKSECTION_H

#include <QObject>

class TrackSection : public QObject
{
    Q_OBJECT

    Q_PROPERTY(TYPE int READ leftVolatge NOTIFY leftVoltageChanged)
    Q_PROPERTY(TYPE int READ rightVolatge NOTIFY rightVoltageChanged)

public:
    enum {
        eLeft  = 0x1,
        eRight = 0x2
    } Side;

    Q_DECLARE_FLAGS(Sides, Side)

    explicit TrackSection(QObject *parent = 0);

    int leftVoltage() const { return m_LeftVoltage; }
    int rightVoltage() const { return m_RightVoltage; }

    void connectSection(TrackSection* pSec, Sides s);
    void disconnectSection(TrackSection* pSec, Sides s);

signals:
    void leftVoltageChanged(int val);
    void rightVoltageChanged(int val);

public slots:
    void setLeftVoltage(int val);
    void setRightVoltage(int val);

private:
    int m_LeftVoltage;
    int m_RightVoltage;

};

#endif // TRACKSECTION_H
