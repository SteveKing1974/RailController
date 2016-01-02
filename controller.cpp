#include "controller.h"

#include "commandclient.h"
#include "servermodel.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    m_pClient = new CommandClient(this);
    m_pServerModel = new ServerModel(this);

    connect(m_pClient, SIGNAL(connectedChanged()), this, SIGNAL(connectedChanged()));
    connect(m_pClient, SIGNAL(connectedChanged()), m_pClient, SLOT(refreshState()));
}

Controller::~Controller()
{

}

bool Controller::connected() const
{
    return m_pClient->connected();
}

void Controller::refreshClients()
{
    m_pServerModel->refresh();
}

void Controller::connectToServer(const QString &address)
{
    m_pClient->connectToServer(address);
}

void Controller::refreshState()
{
    m_pClient->refreshState();
}

