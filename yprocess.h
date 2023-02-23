#ifndef YPROCESS_H
#define YPROCESS_H

#include <QProcess>
#include <QObject>

class YProcess : public QProcess
{
    Q_OBJECT
public:
    YProcess();
    YProcess(QString exePath);
    YProcess(QString exePath, QStringList argList);

public:
    void startProcess();
    void stopProcess();
    void stopProcessByName();
    void stopProcessById();
    bool isProcessExist();
    // another method to check program is running or not
    // a global function, not just could be uesd in this class
    bool isProcessExist(QString exeName);

private:
    QString getExeName();

private:
    QProcess* m_process;
    QString m_exePath;
    QString m_exeName;
    QStringList m_argList;
    bool m_state;
    qint64 m_pid;

};

#endif // YPROCESS_H
