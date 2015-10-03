#ifndef TRACKSECTIONITEM_H
#define TRACKSECTIONITEM_H

#include <QQuickItem>

#include "tracksection.h"

class TrackSectionItem : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QObject* section READ section CONSTANT)

public:
    explicit TrackSectionItem(QQuickItem *parent = 0);

    QObject* section() { return m_pSection; }
signals:

public slots:

protected:
    QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *);

private:
    TrackSection* m_pSection;
};

#endif // TRACKSECTIONITEM_H
