#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "NetworkPacket.h"
#include "MyClient.h"
#include <QtXml>
#include <QStyleFactory>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    void scene_update();

private slots:

    //���� ���������� ���� ������ �� ������ � ����
    void fromSimPac(const QByteArray &pack);

    //���� ���������� ���� ������ �� ����� � �����
    void CopPac();

    //��������� �����������
    void on_buttonTempUp_clicked();

    //��������� �����������
    void on_buttonTempDown_clicked();

    //��������� ���� ������ �������
    void on_buttonGradUp_clicked();

    //��������� ���� ������ �������
    void on_buttonGradDown_clicked();

    //��������� ����������� ������� ������ ������������ (����� ����� 1-3)
    void on_buttonOn1_toggled(bool checked);
    void on_buttonOn2_toggled(bool checked);
    void on_buttonOn3_toggled(bool checked);

    //�����  ���������� ���� ������ � XML
    void onSave();

    //�����  �������� ���� ������ �� XML
    void onLoad();

    //������� � ������� ����������
    void on_action_toFaren_triggered();

    //������� � ������� �������
    void on_action_toCelsi_triggered();

    //������� � ��������
    void on_action_toKelv_triggered();

    //������� � ��.��.��.
    void on_action_toMm_triggered();

    //������� � �������
    void on_action_toPascal_triggered();

    // ���� ���������� ����� ������ ��� ��������� ������ ��� �������� ����������
    void on_darkPushButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    //����� ����� � 3� ���������������
    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
    QGraphicsRectItem *rect2;
    QGraphicsRectItem *rect3;

    MyClient client;

    //����� ��� �������� ������ � �����
    NetworkPacket packet;

};

#endif // MAINWINDOW_H
