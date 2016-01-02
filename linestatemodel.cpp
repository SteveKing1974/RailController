#include "linestatemodel.h"
#include "breaksection.h"
#include "pointsection.h"

#include <QDebug>
#include <QJsonObject>


bool listsEqual(QStringList left, QStringList right, const QString& title)
{
    left.sort();
    right.sort();
    if (left != right)
    {
        qDebug() << title << " mismatch. Got:";
        qDebug() << left;
        qDebug() << "Expected:";
        qDebug() << right;
        return false;
    }

    return true;
}

LineStateModel::LineStateModel(QObject* parent) : QObject(parent)
{
}

LineStateModel::~LineStateModel()
{

}

void LineStateModel::regsiterItem(const QString &name, BreakSection *pSec)
{
    if (name.isEmpty())
    {
        return;
    }

    m_Breaks.insert(name, pSec);
}

void LineStateModel::regsiterItem(const QString &name, PointSection *pSec)
{
    if (name.isEmpty())
    {
        return;
    }

    m_Points.insert(name, pSec);
}


void LineStateModel::updateFromJson(const QJsonDocument &source)
{
    QJsonObject obj = source.object();

    QHash<QString, int> breakVals;
    QHash<QString, int> pointVals;

    QJsonObject points = obj.value("points").toObject();
    QJsonObject::const_iterator it = points.constBegin();
    while (it != points.constEnd())
    {
        pointVals.insert(it.key(), it.value().toObject().value("state").toInt());
        ++it;
    }

    QJsonObject breaks = obj.value("breaks").toObject();
    it = breaks.constBegin();
    while (it != breaks.constEnd())
    {
        breakVals.insert(it.key(), it.value().toObject().value("state").toInt());
        ++it;
    }

    // Do a check that the names received are the same
    if (!listsEqual(breakVals.keys(), m_Breaks.keys(), "Breaks") ||
            !listsEqual(pointVals.keys(), m_Points.keys(), "Points"))
    {
        return;
    }

    QHashIterator<QString, int> i(breakVals);
    while (i.hasNext()) {
        i.next();
        m_Breaks.value(i.key())->setState(static_cast<BreakSection::SwitchState>(i.value()));
    }

    i = pointVals;
    while (i.hasNext()) {
        i.next();
        m_Points.value(i.key())->setDirection(static_cast<PointSection::SwitchDirection>(i.value()));
    }
}

QJsonDocument LineStateModel::toJson() const
{
    QJsonObject points;

    QHashIterator<QString, PointSection*> pIter(m_Points);
    while (pIter.hasNext()) {
        pIter.next();
        QJsonObject nextPoint;
        nextPoint.insert("state", static_cast<int>(pIter.value()->direction()));
        points.insert(pIter.key(), nextPoint);
    }


    QJsonObject breaks;
    QHashIterator<QString, BreakSection*> bIter(m_Breaks);
    while (bIter.hasNext()) {
        bIter.next();
        QJsonObject nextBreak;
        nextBreak.insert("state", static_cast<int>(bIter.value()->state()));
        breaks.insert(bIter.key(), nextBreak);
    }

    QJsonObject topLevel;
    topLevel.insert("points", points);
    topLevel.insert("breaks", breaks);

    QJsonDocument doc(topLevel);

    return doc;
}
