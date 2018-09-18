#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QWidget>

#include <QtNetwork>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QDebug>

#include "NetworkPacket.h"
#include "server.h"

#include <QtXml>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QFile>

namespace Ui
{
class Simulator;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    NetworkPacket packet;

    server Server;

    QXmlStreamWriter xmlWriter();
    QXmlStreamReader xmlReader();

private slots:
    //���� �� ��������� ������������
    void on_tempSpinBox_valueChanged(const QString &arg1);
    //���� �� ��������� ���������
    void on_humiSpinBox_valueChanged(const QString &arg1);
    //���� �� ��������� ������� �������
    void on_gradSpinBox_valueChanged(const QString &arg1);
    //���� �� ��������� ��������
    void on_pressSpinBox_valueChanged(const QString &arg1);

    //���� �� ��������� ��������� ������ ��������� ������  1-3
    void on_pushButton_1_toggled(bool checked);
    void on_pushButton_2_toggled(bool checked);
    void on_pushButton_3_toggled(bool checked);


    //���� ���������� ���� ������ �� ����� � ����
    void fromCopPac(const QByteArray &pack);

    void onSave();

    void onLoad();

public slots:
    //���� ���������� ���� ������ �� ����� � �����
    void SimPac();

private:

    Ui::Simulator *ui;
    //���� �� ����������� � XML

signals:

};

#endif // MAINWINDOW_H
