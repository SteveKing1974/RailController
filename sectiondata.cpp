#include "sectiondata.h"

#include <QJsonDocument>
#include <QJsonArray>

SectionData::SectionData() :
    m_Id(-1),
    m_Name(""),
    m_ControllerId(0),
    m_PossibleControllers()
{

}


QList<SectionData> SectionData::fromJsonDoc(const QJsonDocument &init)
{
    QList<SectionData> out;
    QJsonObject obj = init.object();

    if (obj.value("Command").toString() == "GetState")
    {
        QJsonArray data = obj.value("State").toArray();
        foreach (const QJsonValue& v, data)
        {
            out.push_back(SectionData(v.toString()));
        }
    }

    return out;
}

SectionData::SectionData(const QString &init)
{
    const QStringList i = init.split(";");

    m_Id = i.at(0).toInt();
    m_Name = i.at(1);
    m_ControllerId = i.at(2).toInt();

    foreach (const QString& s, i.at(3).split(","))
    {
        m_PossibleControllers.push_back(QVariant(s.toInt(0)));
    }
}
