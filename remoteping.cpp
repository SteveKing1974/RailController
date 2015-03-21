#include "remoteping.h"

#include <QHostAddress>
#include <QUdpSocket>
#include <QTimer>

RemotePing::RemotePing() : QObject(0)
{
    m_Pinger = new QUdpSocket(this);
    m_Receiver = new QUdpSocket(this);

    m_Pinger->bind(QHostAddress::Broadcast, 7755);
    m_Receiver->bind(7756);

    connect(m_Receiver, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void RemotePing::sendPing()
{
    QByteArray test("hello");
    m_Pinger->writeDatagram(test.data(), test.size(), QHostAddress::Broadcast, 7755);
}

RemotePing::~RemotePing()
{

}

void RemotePing::readPendingDatagrams()
{
    while (m_Receiver->hasPendingDatagrams()) {
        qDebug() << "Host identify";
        QByteArray datagram;
        datagram.resize(m_Receiver->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        m_Receiver->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        emit remoteIdentify(sender);
    }
}
