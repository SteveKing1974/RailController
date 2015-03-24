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

