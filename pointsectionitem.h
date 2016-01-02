#ifndef POINTSECTIONITEM_H
#define POINTSECTIONITEM_H

#include <QQuickItem>

class PointSection;
class TrackSection;

class PointSectionItem : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QObject* leftSection READ leftSection WRITE setLeftSection NOTIFY leftSectionChanged)
    Q_PROPERTY(QObject* rightSection READ rightSection WRITE setRightSection NOTIFY rightSectionChanged)
    Q_PROPERTY(QObject* commonSection READ commonSection WRITE setCommonSection NOTIFY commonSectionChanged)

    Q_PROPERTY(int direction READ direction WRITE setDirection NOTIFY directionChanged)

public:
    explicit PointSectionItem(QQuickItem *parent = 0);

    QObject* leftSection() const;
    QObject* rightSection() const;
    QObject* commonSection() const;

    void setLeftSection(QObject* pArg);
    void setRightSection(QObject* pArg);
    void setCommonSection(QObject* pArg);

    bool direction() const;
    void setDirection(int newVal);

signals:
    void leftSectionChanged();
    void rightSectionChanged();
    void commonSectionChanged();
    void directionChanged();
    void sectionCreated(const QString& name, PointSection* pSec);

private slots:
    void nameChanged(const QString& newName);

protected:
    QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *);

private:
    void createPoint();

    int m_Direction;
    PointSection* m_pPointSection;

    TrackSection* m_pLeft;
    TrackSection* m_pRight;
    TrackSection* m_pCommon;
};

#endif // POINTSECTIONITEM_H
