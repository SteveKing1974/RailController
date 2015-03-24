#ifndef COMMANDCLIENT_H
#define COMMANDCLIENT_H

#include <QObject>
#include <QByteArray>
#include "sectiondata.h"

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

signals:
    void connected();
    void error();
    void gotState(const QList<SectionData>& data);


private:
    QTcpSocket* m_pSock;

    bool m_WaitingForHeader;
    int m_BytesExpected;
    QByteArray m_Data;
};

#endif // COMMANDCLIENT_H
