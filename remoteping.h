#ifndef REMOTEPING_H
#define REMOTEPING_H

#include<QObject>
#include<QHostAddress>

class QUdpSocket;

class RemotePing : public QObject
{
    Q_OBJECT

public:
    RemotePing();
    ~RemotePing();
    void init();

signals:
    void remoteIdentify(const QHostAddress& remote);

private slots:
    void readPendingDatagrams();
    void sendPing();

private:
    QUdpSocket* m_Pinger;
    QUdpSocket* m_Receiver;
};

#endif // REMOTEPING_H
