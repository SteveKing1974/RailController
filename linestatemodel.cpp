#include "linestatemodel.h"

#include <QDebug>

LineStateModel::LineStateModel(QObject* parent) : QAbstractListModel(parent)
{
//    m_Data.push_back(SectionData("0;Outer Top;0;0,1"));
//    m_Data.push_back(SectionData("1;Outer Bottom;0;0,1"));
//    m_Data.push_back(SectionData("2;Inner Top;0;0,2"));
//    m_Data.push_back(SectionData("3;Inner Bottom;0;0,1,2"));
//    m_Data.push_back(SectionData("4;Station Outer;0;0,1,2,3"));
//    m_Data.push_back(SectionData("5;Run Around;0;0,1,2,3"));
//    m_Data.push_back(SectionData("6;Station Inner;0;0,1,2,3"));

//    m_Data.push_back(SectionData("7;Left Siding Bottom;0;0,1,2,3"));
//    m_Data.push_back(SectionData("8;Left Siding Middle;0;0,1,2,3"));
//    m_Data.push_back(SectionData("9;Left Siding Top;0;0,1,2,3"));

//    m_Data.push_back(SectionData("10;Right Hand Loading;0;0,1,2,3"));

//    m_Data.push_back(SectionData("11;Right Siding Lower;0;0,1,2,3"));
//    m_Data.push_back(SectionData("12;Right Siding Middle;0;0,1,2,3"));
//    m_Data.push_back(SectionData("13;Right Siding Bottom;0;0,1,2,3"));
}

LineStateModel::~LineStateModel()
{

}

int LineStateModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_Data.count();
}

QVariant LineStateModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();

    switch (role)
    {
    case eNameRole:
        return QVariant(m_Data.at(row).m_Name);
        break;
    case eSectionRole:
        return QVariant(m_Data.at(row).m_Id);
        break;
    case eControllerIDRole:
        return QVariant(m_Data.at(row).m_ControllerId);
        break;
    case ePossibleControllersRole:
        return QVariant(m_Data.at(row).m_PossibleControllers);
        break;
    default:
        return QVariant("None");
    }

    return QVariant();
}

QHash<int, QByteArray> LineStateModel::roleNames() const
{
    static QHash<int, QByteArray> names;

    if (names.isEmpty())
    {
        names.insert(eNameRole, "name");
        names.insert(eSectionRole, "section");
        names.insert(eControllerIDRole, "controllerID");
        names.insert(ePossibleControllersRole, "possibleControllers");
    }

    return names;
}

QString LineStateModel::controllerName(LineStateModel::ControllerID id) const
{
    switch (id)
    {
    case eNoController:
        return "None";
        break;
    case eController1:
        return "Controller 1";
        break;
    case eController2:
        return "Controller 2";
        break;
    case eController3:
        return "Controller 3";
        break;
    }

    return "";
}

QColor LineStateModel::controllerColour(LineStateModel::ControllerID id) const
{
    switch (id)
    {
    case eNoController:
        return Qt::black;
        break;
    case eController1:
        return Qt::blue;
        break;
    case eController2:
        return Qt::red;
        break;
    case eController3:
        return Qt::green;
        break;
    }

    return Qt::gray;
}

QColor LineStateModel::sectionColour(int sectionIndex) const
{
    if (sectionIndex<0 || sectionIndex>=m_Data.count())
    {
        //qWarning() << "Invalid index" << sectionIndex;
        return Qt::black;
    }

    return controllerColour(static_cast<LineStateModel::ControllerID>(m_Data.at(sectionIndex).m_ControllerId));
}

void LineStateModel::changeController(int sectionIndex, int controllerId)
{
    if (sectionIndex<0 || sectionIndex>=m_Data.count())
    {
        qWarning() << "Invalid index" << sectionIndex;
        return;
    }

    m_Data[sectionIndex].m_ControllerId = static_cast<LineStateModel::ControllerID>(controllerId);
    emit dataChanged(index(sectionIndex), index(sectionIndex));
}

void LineStateModel::stateChanged(const QList<SectionData> data)
{
    beginRemoveRows(QModelIndex(), 0, m_Data.count()-1);
    m_Data.clear();
    endRemoveRows();

    beginInsertRows(QModelIndex(), 0, data.count()-1);
    m_Data = data;
    endInsertRows();
}


