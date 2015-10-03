#ifndef BREAKSECTIONITEM_H
#define BREAKSECTIONITEM_H

#include <QQuickItem>

class BreakSection;
class TrackSection;

class BreakSectionItem : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QObject* leftSection READ leftSection WRITE setLeftSection NOTIFY leftSectionChanged)
    Q_PROPERTY(QObject* rightSection READ rightSection WRITE setRightSection NOTIFY rightSectionChanged)

    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

public:
    explicit BreakSectionItem(QQuickItem *parent = 0);

    QObject* leftSection() const;
    QObject* rightSection() const;

    void setLeftSection(QObject* pArg);
    void setRightSection(QObject* pArg);

    bool enabled() const;
    void setEnabled(bool newVal);

signals:
    void leftSectionChanged();
    void rightSectionChanged();
    void enabledChanged();

public slots:

protected:
    QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *);

private:
    void createBreak();

    bool m_Enabled;
    BreakSection* m_pBreakSection;

    TrackSection* m_pLeft;
    TrackSection* m_pRight;
};

#endif // BREAKSECTIONITEM_H
