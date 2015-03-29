#include "servermodel.h"

#include "remoteping.h"
#include <QHostAddress>

ServerModel::ServerModel(QObject *parent) : QAbstractListModel(parent)
{
    m_pPinger = new RemotePing(this);

    connect(m_pPinger, SIGNAL(remoteIdentify(QHostAddress)), this, SLOT(serverIdentify(QHostAddress)));
}

ServerModel::~ServerModel()
{

}

int ServerModel::rowCount(const QModelIndex &parent) const
{
    return m_Servers.count();
}

QVariant ServerModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    return QVariant(m_Servers.at(row));
}

void ServerModel::refresh()
{
    beginRemoveRows(QModelIndex(), 0, m_Servers.count()-1);
    m_Servers.clear();
    endRemoveRows();
    m_pPinger->sendPing();
}

void ServerModel::serverIdentify(const QHostAddress &s)
{
    beginInsertRows(QModelIndex(), m_Servers.count(), m_Servers.count());
    m_Servers.push_back(s.toString());
    endInsertRows();
}

QHash<int, QByteArray> ServerModel::roleNames() const
{
    static QHash<int, QByteArray> names;

    if (names.isEmpty())
    {
        names.insert(eIPAddressRole, "ipAddress");
    }

    return names;
}
