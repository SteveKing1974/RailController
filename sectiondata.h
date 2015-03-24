#ifndef SECTIONDATA_H
#define SECTIONDATA_H

#include <QJsonObject>
#include <QVariant>

class SectionData {
public:
    static QList<SectionData> fromJsonDoc(const QJsonDocument& init);
    SectionData(const QString &init);
    SectionData();

    int m_Id;
    QString m_Name;
    int m_ControllerId;
    QVariantList m_PossibleControllers;
};

#endif // SECTIONDATA_H
