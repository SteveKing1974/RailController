#include "commandclient.h"
#include <QDebug>
#include <QTimer>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>

CommandClient::CommandClient(QObject *parent) : QObject(parent)
{
    m_pSock = new QTcpSocket(this);

    connect(m_pSock, SIGNAL(readyRead()), this, SLOT(gotData()));
    connect(m_pSock, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SIGNAL(connectedChanged()));
}

CommandClient::~CommandClient()
{

}

bool CommandClient::connected() const
{
    return (m_pSock->state()==QAbstractSocket::ConnectedState);
}

void CommandClient::connectToServer(const QString &s)
{
    m_pSock->connectToHost(s, 7757);
}

void CommandClient::disconnectFromServer()
{
    m_pSock->disconnectFromHost();
}

void CommandClient::refreshState()
{
    emit gotState(QList<SectionData>());
    if (m_pSock->state()!=QAbstractSocket::ConnectedState)
    {
        return;
    }

    QJsonDocument cmdDoc;
    QJsonObject cmdObj;

    cmdObj.insert("Command", QJsonValue("GetState"));
    cmdDoc.setObject(cmdObj);
    QByteArray outBin = cmdDoc.toBinaryData();

    QDataStream out(m_pSock);
    out.writeBytes(outBin.data(), outBin.length());
}

void CommandClient::gotData()
{
    QDataStream strm(m_pSock);

    char* s = 0;
    uint l = 0;
    strm.readBytes(s, l);
    QByteArray data(s, l);
    delete [] s;

    QJsonDocument cmdDoc = QJsonDocument::fromBinaryData(data);
    QJsonObject cmdObj = cmdDoc.object();
    if (cmdObj.value("Command").toString()=="GetState")
    {
        emit gotState(SectionData::fromJsonDoc(cmdDoc));
    }
}

