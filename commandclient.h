#ifndef COMMANDCLIENT_H
#define COMMANDCLIENT_H

#include <QObject>
#include <QByteArray>

class QTcpSocket;

class CommandClient : public QObject
{
    Q_OBJECT
public:
    explicit CommandClient(QObject *parent = 0);
    ~CommandClient();

signals:

public slots:
    void sendData();
    void gotData();

private:
    QTcpSocket* m_pSock;

    bool m_WaitingForHeader;
    int m_BytesExpected;
    QByteArray m_Data;
};

#endif // COMMANDCLIENT_H
