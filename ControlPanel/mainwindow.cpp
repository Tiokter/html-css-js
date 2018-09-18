#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

    //client("localhost",33333)
{
    connect(&client,SIGNAL(packReady(QByteArray)),this,SLOT(fromSimPac(const QByteArray &)));

    //���������� �������� �����
    qApp->setStyle(QStyleFactory::create("Cleanlooks"));

    ui->setupUi(this);
    onLoad();

    // ��������� ����������� �����
    scene = new QGraphicsScene(this);

    scene->setBackgroundBrush(QColor(255, 52, 52));

    ui->graphicsView->setScene(scene);

    //����� ����� �������, ���� � ������� ����� ��� ���������
    QBrush greenBrush(Qt::green);
    QBrush redBrush(QColor(255, 52, 52));
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    // ������ ���������� (x,y,w,h,pen,brush)
    rect = scene->addRect(0, 0, 50, 50, outlinePen, redBrush);
    rect2 = scene->addRect(50, 0, 50, 50, outlinePen, redBrush);
    rect3 = scene->addRect(100, 0, 50, 50, outlinePen, redBrush);

    setWindowTitle("Control panel");
    client.makeSocket("localhost",33333);
}

MainWindow::~MainWindow()
{
    onSave();
    delete ui;
}
void MainWindow::scene_update()
{
    //���� ������ ������
    if(ui->buttonOn1->isChecked())
    {
        //����������� ��������� � �����(���) ������
        rect->setBrush(QBrush(QColor(145, 190, 22)));
        scene->setBackgroundBrush(QColor(145, 190, 22));
        update();
    }
    //���� �� ������
    else
    {
        //����������� ��������� �������
        rect->setBrush(QBrush(QColor(255, 52, 52)));
        update();
    }
    if(ui->buttonOn2->isChecked())
    {
        rect2->setBrush(QBrush(QColor(145, 190, 22)));
        scene->setBackgroundBrush(QColor(145, 190, 22));
        update();
    }
    else
    {
        rect2->setBrush(QBrush(QColor(255, 52, 52)));
        update();
    }
    if(ui->buttonOn3->isChecked())
    {
        rect3->setBrush(QBrush(QColor(145, 190, 22)));
        scene->setBackgroundBrush(QColor(145, 190, 22));
        update();
    }
    else
    {
        rect3->setBrush(QBrush(QColor(255, 52, 52)));
        update();
    }
    //���� ��� ���������� �� ������ ����������� ����� �������
    if (!ui->buttonOn1->isChecked() && !ui->buttonOn2->isChecked() && !ui->buttonOn3->isChecked())
    {
        scene->setBackgroundBrush(QColor(255, 52, 52));
        update();
    }
}
// ======================================================================
//��������� �������� ������������ ���������� �� �������(���������)
void MainWindow::fromSimPac(const QByteArray &pack)
{
    packet.byByteArray(pack);

    ui->tempLbl->blockSignals(true);
    if (ui->label_tempIndex->text() == "�C")
    {
        ui->tempLbl-> setText(packet.getTemp());
    }
    //�������  � ������� ����������
    else if (ui->label_tempIndex->text() == "�F")
    {
        ui->tempLbl-> setText(packet.getTemp());
        ui->tempLbl->setText(QString::number((ui->tempLbl->text()).toFloat()/ 5 * 9 + 32));
    }
    //�������  � ��������
    else if (ui->label_tempIndex->text() == "K")
    {
        ui->tempLbl-> setText(packet.getTemp());
        ui->tempLbl->setText(QString::number((ui->tempLbl->text()).toFloat()+ 273.15));
    }
    ui->tempLbl->blockSignals(false);

    ui->humiLbl->blockSignals(true);
    ui->humiLbl-> setText(packet.getHumi());
    ui->humiLbl->blockSignals(false);

    ui->gradLbl->blockSignals(true);
    ui->gradLbl-> setText(packet.getGrad());
    ui->gradLbl->blockSignals(false);


    //������� ������, ���� � ������������ ���� ��������� ��������� ����������� �������� � ��������, ��������� �������� � ��
    ui->pressLbl->blockSignals(true);
    if (ui->label_pressIndex->text() == "Pa")
    {
        ui->pressLbl-> setText(packet.getPress());
        ui->pressLbl->setText(QString::number((ui->pressLbl->text()).toFloat() * 133.322));
    }
    else
    {
        ui->pressLbl-> setText(packet.getPress());
    }
    ui->pressLbl->blockSignals(false);

    ui->buttonOn1->blockSignals(true);
    ui->buttonOn1-> setChecked(packet.getButton1());
    ui->buttonOn1->blockSignals(false);

    ui->buttonOn2->blockSignals(true);
    ui->buttonOn2-> setChecked(packet.getButton2());
    ui->buttonOn2->blockSignals(false);

    ui->buttonOn3->blockSignals(true);
    ui->buttonOn3-> setChecked(packet.getButton3());
    ui->buttonOn3->blockSignals(false);
    scene_update();
}
// ======================================================================
//�����  ���������� ���� ������ �� ����� � �����
void MainWindow::CopPac()
{
    if (ui->label_tempIndex->text() == "�C")
    {
        packet.setTemp(ui->tempLbl-> text());
    }
    //�������  � ������� ������� �� ����������
    else if (ui->label_tempIndex->text() == "�F")
    {
        packet.setTemp(QString::number(((ui->tempLbl->text()).toFloat()- 32) * 5 / 9));
    }
    //������� � ������� ������� �� ���������
    else if (ui->label_tempIndex->text() == "K")
    {
        packet.setTemp(QString::number((ui->tempLbl->text()).toFloat()- 273.15));
    }

    packet.setHumi(ui->humiLbl-> text());
    packet.setGrad(ui->gradLbl-> text());

    if (ui->label_pressIndex->text() == "Pa")
    {
        packet.setPress(QString::number((ui->pressLbl->text()).toFloat() / 133.322));
    }
    else
    {
        packet.setPress(ui->pressLbl-> text());
    }
    packet.setbuttonOn1(ui->buttonOn1-> isChecked());
    packet.setbuttonOn2(ui->buttonOn2-> isChecked());
    packet.setbuttonOn3(ui->buttonOn3-> isChecked());

    client.sockWrite(packet.toByteArray());
}
// ======================================================================
//��������� �����������
void MainWindow::on_buttonTempUp_clicked()
{
    if (ui->label_tempIndex->text() == "�C")
    {
        if ((ui->tempLbl->text()).toFloat() < 80 )
        {
        ui->tempLbl->setText(QString::number((ui->tempLbl->text()).toFloat() + 0.5));
        CopPac();
        }
    }
    // �� ����������
    else if (ui->label_tempIndex->text() == "�F")
    {
        if ((ui->tempLbl->text()).toFloat() < 176 )
        {
        ui->tempLbl->setText(QString::number((ui->tempLbl->text()).toFloat() + 0.5));
        //������ ��������� � �����
        CopPac();
        }
    }
    //������� �� ���������
    else if (ui->label_tempIndex->text() == "K")
    {
        if ((ui->tempLbl->text()).toFloat() < 353 )
        {
        ui->tempLbl->setText(QString::number((ui->tempLbl->text()).toFloat() + 0.5));
        //������ ��������� � �����
        CopPac();
        }
    }
}
//��������� �����������
void MainWindow::on_buttonTempDown_clicked()
{
    if (ui->label_tempIndex->text() == "�C")
    {
        if ((ui->tempLbl->text()).toFloat() > -50)
        {
        ui->tempLbl->setText(QString::number((ui->tempLbl->text()).toFloat() - 0.5));
        CopPac();
        }
    }
    // �� ����������
    else if (ui->label_tempIndex->text() == "�F")
    {
        if ((ui->tempLbl->text()).toFloat() > -58)
        {
        ui->tempLbl->setText(QString::number((ui->tempLbl->text()).toFloat() - 0.5));
        //������ ��������� � �����
        CopPac();
        }
    }
    //������� �� ���������
    else if (ui->label_tempIndex->text() == "K")
    {
        if ((ui->tempLbl->text()).toFloat() > 223.3)
        {
        ui->tempLbl->setText(QString::number((ui->tempLbl->text()).toFloat() - 0.5));
        //������ ��������� � �����
        CopPac();
        }
    }
}
// ======================================================================
//��������� ���� ������ �������
void MainWindow::on_buttonGradUp_clicked()
{
    if (ui->gradLbl->text().toFloat() < 130 && ui->gradLbl->text().toFloat() > 40)
    {
        ui->gradLbl->setText(QString::number((ui->gradLbl->text()).toFloat() + 10));
    }
    CopPac();
}
//��������� ���� ������ �������
void MainWindow::on_buttonGradDown_clicked()
{
    if (ui->gradLbl->text().toFloat() <= 130 && ui->gradLbl->text().toFloat() > 50)
    {
        ui->gradLbl->setText(QString::number((ui->gradLbl->text()).toFloat() - 10));
    }
    CopPac();
}
// ======================================================================
//��������� ����������� ������� ������ ������������ (����� ����� 1)
void MainWindow::on_buttonOn1_toggled(bool checked)
{
    scene_update();
    CopPac();
}
//��������� ����������� ������� ������ ������������ (����� ����� 2)
void MainWindow::on_buttonOn2_toggled(bool checked)
{
    scene_update();
    CopPac();
}
//��������� ����������� ������� ������ ������������ (����� ����� 3)
void MainWindow::on_buttonOn3_toggled(bool checked)
{
    scene_update();
    CopPac();
}
// ======================================================================
//�����  ���������� ���� ������ � XML
void MainWindow::onSave()
{
    QFile file("D:/Condi/ControlPanel/ControlPanel/cpXML.xml");
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("Values");

    xmlWriter.writeStartElement("label_tempIndex");
    xmlWriter.writeCharacters(ui->label_tempIndex-> text());
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("label_pressIndex");
    xmlWriter.writeCharacters(ui->label_pressIndex-> text());
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("darkPushButton");
    xmlWriter.writeAttribute("boolean", ui->darkPushButton-> isChecked() ? "true" : "false");
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    //��������� ������ � ��������
    xmlWriter.writeEndDocument();

    file.close();
    qDebug() << "file save";
}
//�����  �������� ���� ������ �� XML
void MainWindow::onLoad()
{
    QFile file("D:/Condi/ControlPanel/ControlPanel/cpXML.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "file open error";
    }
    else
    {
        QXmlStreamReader xmlReader(&file);
        xmlReader.readNext();
        while(!xmlReader.atEnd())
        {
            if(xmlReader.isStartElement())
            {
                if(xmlReader.name() == "label_tempIndex")
                {
                     ui->label_tempIndex->setText(xmlReader.readElementText());
                }
                else if (xmlReader.name() == "label_pressIndex")
                {
                    ui->label_pressIndex->setText(xmlReader.readElementText());
                }
                else if (xmlReader.name() == "darkPushButton")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "boolean")
                        {
                        QString attribute_value = attr.value().toString();
                        ui->darkPushButton->setChecked((QString::compare(attribute_value , "true") == 0) ? true : false);
                        }
                    }
                }
            }
            xmlReader.readNext();
        }
        file.close();
    }
}
// ======================================================================
//�������  � ������� ����������
void MainWindow::on_action_toFaren_triggered()
{
      // �� �������
      if (ui->label_tempIndex->text() == "�C")
      {
        ui->tempLbl->setText(QString::number((ui->tempLbl->text()).toFloat()/ 5 * 9 + 32));
      }
      // �� ��������
      else if (ui->label_tempIndex->text() == "K")
      {
        ui->tempLbl->setText(QString::number(((ui->tempLbl->text()).toFloat()- 273.15) / 5 * 9 + 32));
      }
      ui->label_tempIndex->setText("�F");
}
//�������  � ������� �������
void MainWindow::on_action_toCelsi_triggered()
{
    // �� ����������
    if (ui->label_tempIndex->text() == "�F")
    {
        ui->tempLbl->setText(QString::number(((ui->tempLbl->text()).toFloat()- 32) * 5 / 9));
    }
    // �� ��������
    else if (ui->label_tempIndex->text() == "K")
    {
        ui->tempLbl->setText(QString::number((ui->tempLbl->text()).toFloat() - 273.15));
    }
    ui->label_tempIndex->setText("�C");
}
//�������  � ��������
void MainWindow::on_action_toKelv_triggered()
{
    // �� �������
    if (ui->label_tempIndex->text() == "�C")
    {
        ui->tempLbl->setText(QString::number((ui->tempLbl->text()).toFloat()+ 273.15));
    }
    // �� ����������
    else if (ui->label_tempIndex->text() == "�F")
    {
        ui->tempLbl->setText(QString::number(((ui->tempLbl->text()).toFloat()- 32) * 5 / 9 + 273.15));
    }
    ui->label_tempIndex->setText("K");
}
// ======================================================================
// ������� �������� � ��.��.��
void MainWindow::on_action_toMm_triggered()
{
    if (ui->label_pressIndex->text() == "Pa")
    {
        ui->pressLbl->setText(QString::number((ui->pressLbl->text()).toFloat() / 133.322));
    }
    ui->label_pressIndex->setText("mm");
}
// ������� �������� � ��
void MainWindow::on_action_toPascal_triggered()
{
    if (ui->label_pressIndex->text() == "mm")
    {
        ui->pressLbl->setText(QString::number((ui->pressLbl->text()).toFloat() * 133.322));
    }
    ui->label_pressIndex->setText("Pa");
}
// ======================================================================
// ���� ���������� ����� ������ ��� ��������� ������ ��� �������� ����������
void MainWindow::on_darkPushButton_toggled(bool checked)
{
    if(checked)
    {// ������ ������� ��� ����� ���� ����������
        QPalette darkPalette;

        // ����������� ������� ��� �������� ����� ��������� ����������
        darkPalette.setColor(QPalette::Window, QColor(80, 77, 30));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(178, 172, 68));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);

        // ������������� ������ �������
        qApp->setPalette(darkPalette);
        //������ ����� ������
        ui->darkPushButton->setText("Light");
    }
    else
    {
        // ��� �������� � ������� ������� ������������� ����������� ������� �� ���� ����������
        qApp->setPalette(style()->standardPalette());
        ui->darkPushButton->setText("Dark");
    }
}
