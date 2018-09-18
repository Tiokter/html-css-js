#include "MyClient.h"

MyClient::MyClient () :state(false)
{

}
void MyClient::makeSocket(const QString& strHost,int nPort)
{
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisk()));

    while(socket->state()!= QAbstractSocket::ConnectedState)
    {
        QCoreApplication::instance()->processEvents();
        if (NULL != socket)
        {
            socket->connectToHost(strHost, nPort);
            bool controlRetValue = socket->waitForConnected(5000);
            if (false != controlRetValue)
            {
                qDebug() << "Connected!";
                qDebug() << socket->state();
                state = true;
            }
            else
            {
                qDebug() << "Not connected!";
                qDebug() << socket->state();
            }
        }
    }
}
void MyClient::sockReady()
{
    socket-> waitForReadyRead(500);
    packet = socket->readAll();

    //������ ������� ��� ����� ������
    emit packReady(packet);
}
void MyClient::sockWrite(QByteArray xzc)
{
    if (socket != NULL)
    {
        if (!state) return;
        socket->write(xzc);
        socket->waitForBytesWritten(800);
    }
}
void MyClient::sockDisk()
{
    qDebug() << "Disconnect";
    state = false;
    socket->deleteLater();
    //��� ������ ������ (�����������) ����� ���� ������
    //makeSocket("localhost",33333);
}
