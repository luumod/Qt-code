#ifndef FINDQTENV_H
#define FINDQTENV_H

#include <QObject>

class findQtEnv:public QObject
{
    Q_OBJECT
public:
    explicit findQtEnv(QObject* parant=nullptr);
    //获取Qt版本字符串列表
    QStringList QtVersionList();
    //获取Qt编译套件字符串列表
    QStringList QtCompilerList();
    void test();
    void generate();
public:
    void setQtVersion(const QString& version);
    QString qtVersion()const;
    void setQtCompiler(const QString& compiler);
    QString qtCompiler()const;

    void setExeFilePath(const QString& compiler);
    QString exeFilePath()const;

    QString setEnvPath(const QString& path);

signals:
    void qtVersionChanged(const QString& version);
    void qtCompilerChanged(const QString& compiler);
    void testFinished(bool ok);
    void generateFinished();
private:
    QString m_currentQtVersion;  //当前Qt版本
    QString m_currentQtCompiler; //当前Qt编译套件
    QString m_qtRootPath;
    QString m_exeFilePath;
};

#endif // FINDQTVERSION_H
