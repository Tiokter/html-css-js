#ifndef MYCLIENT.H
#define MYCLIENT.H

#include <QObject>
#include <QWidget>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include "networkpacket.h"
#include <QCoreApplication>

class MyClient : public QObject

{

Q_OBJECT

private:
    //QCoreApplication w;
    QTcpSocket *socket;
    QByteArray packet;
    bool state;

public:

    MyClient();

public slots:

    void makeSocket(const QString& strHost,int nPort);
    void sockReady();                               //���������� � ������ ������
    void sockWrite(QByteArray);                     //������ ������
    void sockDisk();                                //������������ ������

signals:

    void packReady(QByteArray);
};

#endif  // MYCLIENT.H
