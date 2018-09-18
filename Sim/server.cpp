#include "server.h"

server::server() : state(false)
{
    socket = NULL;
}
server::~server(){}

void server::startServer()
{
    if (this->listen(QHostAddress::Any, 33333))
    {
        qDebug() << "Listening";
    }
    else
    {
        qDebug() << "Not Listening";
    }
}
//����� ����������
void server::incomingConnection(int socketDescriptor)
{
    socket = new QTcpSocket(this);                                  //����� �����
    socket->setSocketDescriptor(socketDescriptor);                  //������� ���.������ ������

    state = true;
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));     //������ � ���������� ������
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisk()));   //������ ������������
    emit connected();                                               //������ � ��������� ����������
/*�������� ����������
    qDebug()<< socket->isValid ();
    qDebug()<< socket->localAddress ();
    qDebug()<< socket->localPort ();
    qDebug()<< socket->peerAddress ();
    qDebug()<< socket->peerName ();
    qDebug()<< socket->peerPort ();
*/
    qDebug() << socketDescriptor << "Client connected";
}
void server::sockReady()
{
    socket-> waitForReadyRead(500);
    data = socket->readAll();
    emit packReady(data);
}
//����� ������ � ����� "������� ������"
void server::sockWrite(QByteArray xzc)
{

    if (!state) return;
    if (socket != NULL)
    {

        socket->write(xzc);
        socket->waitForBytesWritten(500);
    }
}
//����� ������������
void server::sockDisk()
{
    qDebug() << "Disconnect";
    state = false;
    socket->deleteLater();
}
