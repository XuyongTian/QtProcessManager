#include "yprocess.h"
#include <QDebug>

YProcess::YProcess()
{
    m_process = new QProcess();
    m_exePath = "cmd.exe";
    m_argList << "";
    bool m_state = false;
}

YProcess::YProcess(QString exePath)
{
    m_process = new QProcess();
    m_exePath = exePath;
    m_argList << "";
    bool m_state = false;
}

YProcess::YProcess(QString exePath, QStringList argList)
{
    m_process = new QProcess();
    m_exePath = exePath;
    m_argList << argList;
    bool m_state = false;
}

void YProcess::startProcess()
{
    m_process->setProgram(m_exePath);
    m_process->setArguments(m_argList);
    m_process->start();
    qDebug() << "Program state:" << m_process->state();
    bool bRet = m_process->waitForStarted();
    if (!bRet)
    {
        qDebug() << "Start program:" << m_exePath << " timeout";
        m_state = false;
        return;
    }
//    qDebug()<<QString::fromLocal8Bit(m_process->readAllStandardOutput());
    m_pid = m_process->processId();
    m_state = true;
    qDebug() << m_exePath << " PID is " << m_pid;
}

void YProcess::stopProcess()
{
    m_process->close();
//    qDebug() << "Program state:" << m_process->state();
//    bool bRet = m_process->waitForFinished();
    if (m_process->state() == QProcess::Running)
    {
        qDebug() << "Stop program:" << m_exePath << " timeout";
        m_state = false;
        return;
    }

}

void YProcess::stopProcessByName()
{
    if (m_process->state() == QProcess::NotRunning)
    {
        qDebug() << m_exePath << " is not running, not need to kill again";
        return;
    }
    QString exeName = getExeName();
    QProcess::startDetached("taskkill -t  -f /IM " + exeName);
}

void YProcess::stopProcessById()
{
    if (m_pid < 0)
    {
        qDebug() << "Last program is killed, not need to kill again";
        return;
    }
    if (m_process->state() == QProcess::NotRunning)
    {
        qDebug() << m_exePath << " is not running, not need to kill again";
        return;
    }
    m_pid = m_process->processId();
    QProcess::startDetached("taskkill -t  -f /pid " + QString::number(m_pid));
    // in case kill another program has the same pid
    m_pid = -1;
}

bool YProcess::isProcessExist()
{
    QProcess proc;
    proc.setProgram("tasklist");
    proc.start();
    // 等待 tasklist 启动
    proc.waitForFinished();

    QByteArray result = proc.readAllStandardOutput();
    QString str = result;
    QString exeName = getExeName();
    if(str.contains(exeName))
    {
        qDebug() << exeName <<"is Running";
        return true;
    }
    else
    {
        qDebug() << "Can't find " << exeName;
        return false;
    }
}

// this function has something wrong, not use
bool YProcess::isProcessExist(QString exeName)
{
//    QString strInfo = QString::number(QProcess::execute("tasklist", QStringList() << "-fi" << "imagename eq influxd.exe"));
    QString strInfo = QString::number(QProcess::execute("tasklist", QStringList() << "-fi" << "imagename eq " + exeName));
    qDebug() << strInfo;
    if(strInfo.contains(exeName))
    {
        qDebug() << exeName << " is Running";
        return true;
    }
    else
    {
        qDebug() << "Can't find " << exeName;
        return false;
    }
}

QString YProcess::getExeName()
{
    int idx = m_exePath.lastIndexOf('/');
    m_exeName = m_exePath.mid(idx + 1, -1);
//    qDebug() << "Program name:" << m_exeName;
    return m_exeName;
}
