#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "linestatemodel.h"
#include "servermodel.h"
class CommandClient;


class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* lineModel READ lineModel CONSTANT)
    Q_PROPERTY(QObject* serverModel READ serverModel CONSTANT)

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)

public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

    QObject* lineModel() const { return m_pLineState; }
    QObject* serverModel() const { return m_pServerModel; }

    bool connected() const;

signals:
    void connectedChanged();

public slots:
    void refreshClients();
    void connectToServer(const QString& address);
    void refreshState();

private:
    LineStateModel* m_pLineState;

    CommandClient* m_pClient;
    ServerModel* m_pServerModel;
};

#endif // CONTROLLER_H
