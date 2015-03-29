#ifndef REMOTEPING_H
#define REMOTEPING_H

#include<QObject>
#include<QHostAddress>

class QUdpSocket;

class RemotePing : public QObject
{
    Q_OBJECT

public:
    RemotePing(QObject* parent = 0);
    ~RemotePing();

signals:
    void remoteIdentify(const QHostAddress& remote);

public slots:
    void sendPing();

private slots:
    void readPendingDatagrams();

private:
    QUdpSocket* m_Pinger;
    QUdpSocket* m_Receiver;
};

#endif // REMOTEPING_H
