#ifndef CLIENTSMODEL_H
#define CLIENTSMODEL_H

#include <QObject>
#include <QAbstractListModel>


class QHostAddress;
class RemotePing;

class ServerModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ServerRoles {
        eIPAddressRole = Qt::DisplayRole
    };

    ServerModel(QObject* parent = 0);
    ~ServerModel();


    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;
public slots:
    void refresh();

private slots:
    void serverIdentify(const QHostAddress& s);

private:
    QStringList m_Servers;

    RemotePing* m_pPinger;
};

#endif // CLIENTSMODEL_H
