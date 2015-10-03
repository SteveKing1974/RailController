#ifndef POINTSECTIONITEM_H
#define POINTSECTIONITEM_H

#include <QQuickItem>

class PointSection;

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

public slots:

protected:
    QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *);

private:
    void createPoint();

    int m_Direction;
    PointSection* m_pPointSection;

    QObject* m_pLeft;
    QObject* m_pRight;
    QObject* m_pCommon;
};

#endif // POINTSECTIONITEM_H
