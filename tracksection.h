#ifndef TRACKSECTION_H
#define TRACKSECTION_H

#include <QObject>

class TrackSection : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int leftVoltage READ leftVoltage NOTIFY leftVoltageChanged)
    Q_PROPERTY(int rightVoltage READ rightVoltage NOTIFY rightVoltageChanged)

public:
    enum Side {
        eLeft  = 0x1,
        eRight = 0x2
    };

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

Q_DECLARE_OPERATORS_FOR_FLAGS(TrackSection::Sides)

#endif // TRACKSECTION_H
