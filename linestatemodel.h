#ifndef LINESTATEMODEL_H
#define LINESTATEMODEL_H

#include <QObject>
#include <QHash>
#include <QJsonDocument>

class BreakSection;
class PointSection;

class LineStateModel : public QObject
{
    Q_OBJECT

public:

    LineStateModel(QObject *parent = 0);
    ~LineStateModel();

     void updateFromJson(const QJsonDocument& source);
    QJsonDocument toJson() const;

public slots:
    void regsiterItem(const QString& name, BreakSection* pSec);
    void regsiterItem(const QString& name, PointSection* pSec);

signals:

private:
    QHash<QString, BreakSection*> m_Breaks;
    QHash<QString, PointSection*> m_Points;
};

#endif // LINESTATEMODEL_H
