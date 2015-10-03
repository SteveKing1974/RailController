#ifndef POWERSUPPLT_H
#define POWERSUPPLT_H

#include <QQuickItem>

class TrackSection;

class PowerSupply : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QObject* connectedSection READ connectedSection WRITE setConnectedSection NOTIFY connectedSectionChanged)
    Q_PROPERTY(int leftVoltage READ leftVoltage WRITE setLeftVoltage NOTIFY leftVoltageChanged)
    Q_PROPERTY(int rightVoltage READ rightVoltage WRITE setRightVoltage  NOTIFY rightVoltageChanged)

public:
    explicit PowerSupply(QQuickItem *parent = 0);

    QObject* connectedSection() const;
    void setConnectedSection(QObject* pArg);


    int leftVoltage() const { return m_LeftVoltage; }
    int rightVoltage() const { return m_RightVoltage; }

    void setLeftVoltage(int val);
    void setRightVoltage(int val);

signals:
    void leftVoltageChanged();
    void rightVoltageChanged();
    void connectedSectionChanged();

private slots:
    void sectionVoltageChanged();
    void correctVoltages();

private:
    int m_LeftVoltage;
    int m_RightVoltage;

    TrackSection* m_ConnectedSection;
};

#endif // POWERSUPPLT_H
