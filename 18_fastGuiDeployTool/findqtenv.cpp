#include "findqtenv.h"
#include <QStandardPaths>
#include <QDebug>
#include <QDir>
#include <iostream>
#include <QProcess>
#include <QMessageBox>

// 获取应用程序各种快捷方式的存放位置：
// C:\Users\woshishuaige\AppData\Roaming\Microsoft\Windows\Start Menu\Programs
#define Application QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation)

findQtEnv::findQtEnv(QObject* parent)
    :QObject(parent)
{
}

QStringList findQtEnv::QtVersionList()
{
    QDir AppDir(Application); //获取应用程序Link路径

    auto list = AppDir.entryList(QStringList("Qt*")); //寻找Qt
    //返回QStringList代表所有的文件和目录
    if (list.isEmpty()){
        qInfo()<<"寻找Qt程序路径失败";
        return QStringList();
    }
    AppDir.cd(list.first());      //进入目录
    m_qtRootPath = AppDir.path(); //保存Qt的路径 C:\Users\woshishuaige\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Qt

    //找到Qt6.2.4目录，返回名称，这就是版本号
    return AppDir.entryList(QDir::Filter::Dirs | QDir::Filter::NoDotAndDotDot);
}

QStringList findQtEnv::QtCompilerList()
{
    QDir AppDir(m_qtRootPath);
    if (!AppDir.cd(m_currentQtVersion)){  //打开6.2.4文件夹，进入当前编译套件文件夹中
        qInfo()<<"打开 "<<m_currentQtVersion<<" 失败!";
        return QStringList();
    }
    //返回mingw和msvc名称
    return AppDir.entryList(QDir::Filter::Dirs | QDir::Filter::NoDotAndDotDot);
}

void findQtEnv::test()
{
    //测试生成后是否成功打开
    emit testFinished(QProcess::startDetached(m_exeFilePath));
}

void findQtEnv::setQtVersion(const QString &version)
{
    if (m_currentQtVersion!=version){
        m_currentQtVersion = version;
        emit qtVersionChanged(m_currentQtVersion); //发送版本修改信号
    }
}

QString findQtEnv::qtVersion() const
{
    return m_currentQtVersion;
}

void findQtEnv::setQtCompiler(const QString &compiler)
{
    if (m_currentQtCompiler!= compiler){
        m_currentQtCompiler = compiler;
        emit qtCompilerChanged(m_currentQtCompiler); //发送套件修改信号
    }
}

QString findQtEnv::qtCompiler() const
{
    return m_currentQtCompiler;
}

void findQtEnv::setExeFilePath(const QString &exefile)
{
    m_exeFilePath = exefile;
}

QString findQtEnv::exeFilePath() const
{
    return m_exeFilePath;
}

void findQtEnv::generate()
{
    // dir =  .../Qt/6.2.4/MSVC 2019 (64-bit)
    QDir dir(m_qtRootPath + "/" + m_currentQtVersion + "/" + m_currentQtCompiler);

    //获取套件下面的所有文件
    auto files = dir.entryList(QDir::Filter::Files);
    if (files.isEmpty()){
        qInfo()<<"获取快捷方式失败!";
        return;
    }
    //获取快捷方式的路径
    QFileInfo info(dir.path() + "/" + files.front()); //随便获取一个files即可，他们都是相同的Link
    //拿到快捷方式所指向的文件所在目录
    QString binPath = QFileInfo(info.symLinkTarget()).path();

    //设置应用程序的当前环境遍历
    const char* path =  QString(getenv("PATH") + setEnvPath(binPath)).toLocal8Bit().data();
    _putenv(path);

#if 0
    auto destFilePathFormat = QString(binPath + "/" + "windeployqt.exe" + " " + m_exeFilePath).toLocal8Bit().data();
    //qInfo()<<QString(binPath + "/" + "windeployqt.exe" + " " + m_exeFilePath);
    system(destFilePathFormat);
#elif 0
    QProcess pro;
    pro.start(binPath + "/" + "windeployqt.exe",QStringList()<<m_exeFilePath);
    pro.waitForStarted();
    pro.waitForFinished();


    //查看输出结果
    qInfo()<<pro.readAllStandardOutput();

#elif 1
    QProcess* pro= new QProcess(this);
    //不会阻塞
    connect(pro,&QProcess::finished,this,[=](){
        qInfo()<<QString(pro->readAllStandardOutput()).toStdString().data();
        if (!m_exeFilePath.isEmpty()){
            emit generateFinished(); //打包完成
        }
    });
    pro->start(binPath + "/" + "windeployqt.exe",QStringList()<<m_exeFilePath);
#endif
}


QString findQtEnv::setEnvPath(const QString& path)
{
    QFile file(path + "/" + "qtenv2.bat");
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("qtenv2.bat open failed");
        return QString();
    }
    QString ret;
    while (!file.atEnd())
    {
        QString line =  file.readLine();
        if (line.indexOf("PATH") != -1)
        {
            ret = line.mid(9).remove("%PATH%").trimmed();
            break;
        }
    }
    return path;
}








