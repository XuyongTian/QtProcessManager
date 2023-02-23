#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "yprocess.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ss_clicked();

    void on_pushButton_load_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_test_clicked();

private:
    Ui::MainWindow *ui;

private:
    void readConfigFile();
    void writeConfigFile();

    void initializeProcesses();
    void startProcesses();

private:
    QProcess* process1;
    QProcess* process2;
    QProcess* process3;

    YProcess* m_p;
};
#endif // MAINWINDOW_H
