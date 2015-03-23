#include "commandclient.h"
#include <QDebug>
#include <QTimer>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>

const int k_HeaderSize = 4;

CommandClient::CommandClient(QObject *parent) : QObject(parent),
    m_WaitingForHeader(true),
    m_BytesExpected(k_HeaderSize)
{
    m_pSock = new QTcpSocket(this);

    m_pSock->connectToHost("192.168.1.153", 7757);

    connect(m_pSock, SIGNAL(readyRead()), this, SLOT(gotData()));

    QTimer::singleShot(2000, this, SLOT(sendData()));
}

CommandClient::~CommandClient()
{

}

void CommandClient::sendData()
{
    QJsonDocument cmdDoc;
    QJsonObject cmdObj;

    cmdObj.insert("Command", QJsonValue("GetState"));
    cmdDoc.setObject(cmdObj);
    QByteArray outBin = cmdDoc.toBinaryData();

    QDataStream out(m_pSock);
    out.writeBytes(outBin.data(), outBin.length());
    QTimer::singleShot(2000, this, SLOT(sendData()));
}

void CommandClient::gotData()
{
    while (m_pSock->bytesAvailable())
    {
        m_Data.append(m_pSock->read(m_BytesExpected - m_Data.length()));

        if ((m_BytesExpected - m_Data.length()) == 0)
        {
            if (m_WaitingForHeader)
            {
                m_BytesExpected = m_Data.toInt();
            }
        }
    }
}

