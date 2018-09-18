#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QTcpServer>
#include <QByteArray>

class server : public QTcpServer
{
    Q_OBJECT

public:
    server();
    ~server();

    QTcpSocket *socket;
    QByteArray data;

private:

    bool state;

public slots:

    void startServer();                             //����� ��������
    void incomingConnection(int socketDescriptor);  //����� ����������
    void sockReady();                               //���������� � ������ ������
    void sockWrite(QByteArray);                     //������ ������
    void sockDisk();                                //������������ ������

signals:

    void packReady(QByteArray);

    void connected();                               //������ � ����� ������������� �������
};

#endif // SERVER_H
