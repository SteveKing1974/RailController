#ifndef COMMANDCLIENT_H
#define COMMANDCLIENT_H

#include <QObject>
#include <QByteArray>
#include "sectiondata.h"

class QTcpSocket;

class CommandClient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
public:
    explicit CommandClient(QObject *parent = 0);
    ~CommandClient();

    bool connected() const;

public slots:
    void connectToServer(const QString& s);
    void disconnectFromServer();

    void refreshState();

signals:
    void connectedChanged();

    void error();

    void gotState(const QList<SectionData>& data);

private slots:
    void gotData();

private:
    QTcpSocket* m_pSock;
};

#endif // COMMANDCLIENT_H
