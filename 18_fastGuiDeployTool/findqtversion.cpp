#include "findqtversion.h"
#include <QStandardPaths>
#include <QDebug>
#include <QDir>
#define Application QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation)
findQtVersion::findQtEnv(QObject* parent)
    :QObject(parent)
{
    //开始菜单程序目录
    //QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);

    qInfo()<<QtVersionList();
    //先set然后找编译套件
    setQtVersion(QtVersionList().first());
    qInfo()<<QtCompilerList();

}

QStringList findQtVersion::QtVersionList()
{
    QDir AppDir(Application);

    auto list = AppDir.entryList(QStringList("Qt*"));
    if (list.isEmpty()){
        return QStringList();
    }
    AppDir.cd(list.first());
    m_qtRootPath = AppDir.path(); //C:\Users\woshishuaige\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Qt

    return AppDir.entryList(QDir::Filter::Dirs | QDir::Filter::NoDotAndDotDot);//找到Qt6.2.4目录，返回名称
}

QStringList findQtVersion::QtCompilerList()
{
    qInfo()<<m_currentQtVersion;
    QDir AppDir(m_qtRootPath);
    if (!AppDir.cd(m_currentQtVersion)){  //打开Qt 6.2.4文件夹
        qInfo()<<"打开 "<<m_qtRootPath<<" 失败!";
        return QStringList();
    }
    return AppDir.entryList(QDir::Filter::Dirs | QDir::Filter::NoDotAndDotDot);//返回mingw和msvc名称
}

void findQtVersion::setQtVersion(const QString &version)
{
    if (m_currentQtVersion!=version){
        m_currentQtVersion = version;
        emit qtVersionChanged(m_currentQtVersion);
    }
}

