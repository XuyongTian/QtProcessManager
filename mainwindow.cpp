#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QThread>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    readConfigFile();
    initializeProcesses();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_ss_clicked()
{
    QString sText = ui->pushButton_ss->text();
    if (sText == "Start")
    {
        m_p->startProcess();
        ui->pushButton_ss->setText("Stop");
    }
    else
    {
        m_p->stopProcess();
        ui->pushButton_ss->setText("Start");
    }
}

void MainWindow::readConfigFile()
{
    QFile file("./config.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int nIdx = 0;
    QTextStream in(&file);

    ui->lineEdit_ip_pc1->setText(in.readLine());
    ui->lineEdit_cams_pc1->setText(in.readLine());
    ui->lineEdit_ip_pc2->setText(in.readLine());
    ui->lineEdit_cams_pc2->setText(in.readLine());
    ui->lineEdit_ip_pc3->setText(in.readLine());
    ui->lineEdit_cams_pc3->setText(in.readLine());

    file.close();
}

void MainWindow::writeConfigFile()
{
    QFile file("./config.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << ui->lineEdit_ip_pc1->text();
    out << "\n";
    out << ui->lineEdit_cams_pc1->text();
    out << "\n";
    out << ui->lineEdit_ip_pc2->text();
    out << "\n";
    out << ui->lineEdit_cams_pc2->text();
    out << "\n";
    out << ui->lineEdit_ip_pc3->text();
    out << "\n";
    out << ui->lineEdit_cams_pc3->text();

    file.close();
}

void MainWindow::on_pushButton_load_clicked()
{
    readConfigFile();
}


void MainWindow::on_pushButton_save_clicked()
{
    writeConfigFile();
}


void MainWindow::initializeProcesses()
{
    process1 = new QProcess(this);
    process2 = new QProcess(this);
    process3 = new QProcess(this);

    m_p = new YProcess("D:/Software/NetAssist.exe");
}


void MainWindow::startProcesses()
{

}

void MainWindow::on_pushButton_test_clicked()
{
}

