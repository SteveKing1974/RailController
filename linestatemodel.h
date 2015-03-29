#ifndef LINESTATEMODEL_H
#define LINESTATEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QColor>

#include "sectiondata.h"

class LineStateModel : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(LineRoles)
    Q_ENUMS(ControllerID)
public:
    enum LineRoles {
        eNameRole = Qt::DisplayRole,
        eSectionRole = Qt::UserRole,
        eControllerIDRole,
        ePossibleControllersRole
    };

    enum ControllerID {
        eNoController,
        eController1,
        eController2,
        eController3
    };

    LineStateModel(QObject *parent = 0);
    ~LineStateModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QString controllerName(ControllerID id) const;
    Q_INVOKABLE QColor controllerColour(ControllerID id) const;

    Q_INVOKABLE QColor sectionColour(int sectionIndex) const;

public slots:
    void changeController(int sectionIndex, int controllerId);
    void stateChanged(const QList<SectionData> data);

private:

    QList<SectionData> m_Data;
};

#endif // LINESTATEMODEL_H
