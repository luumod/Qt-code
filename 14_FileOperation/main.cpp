#include "widget.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QDataStream>
#include <QDate>
#include <QFileInfo>
#include <QDir>
#include <QStandardPaths>
#include <QSettings>

//文件读写操作
void fileReadWrite(){
    QFile file("Qt.txt");
    if (!file.open(QFile::OpenModeFlag::WriteOnly)){
        qInfo()<<"open file failed";
        return ;
    }
    file.write("你好，我是于良浩\n");

    qInfo()<<file.fileName();

    qInfo()<<file.size();

    //关闭文件
    file.close();

    //重新打开
    file.setFileName("test.txt");
    if (!file.open(QFile::OpenModeFlag::ReadOnly)){
        qInfo()<<"open file failed";
        return;
    }
    auto data = file.read(10);
    qInfo()<<QString::fromUtf8(data);

    data = file.readLine();
    qInfo()<<QString::fromUtf8(data);

    data = file.readLine();
    qInfo()<<QString::fromUtf8(data);

    //读取全部
    data = file.readAll();
    qInfo()<<QString::fromUtf8(data);
}

//文本流类
void streamClass(){

    QByteArray data = "123 我爱你 789654";
    QTextStream in(data);

    int number;
    QString str;
    long lnumber;
    //格式化读取
    in>>number>>str>>lnumber;
    qInfo()<<number<<str<<lnumber;

    QByteArray buff;
    QTextStream out(&buff); //往buff写入
    //格式化写入
    out<<number<<str<<lnumber;
    out.flush();
    qInfo()<<buff; //输出写入的字符串

    //结合QFile
    QFile file("test.txt");
    if (!file.open(QFile::OpenModeFlag::ReadOnly)){
        qInfo()<<"open file failed";
        return;
    }
    //关联文本流
    QTextStream fs(&file);
    //qInfo()<<fs.readAll();
    //循环读取
    while (!fs.atEnd()){
        qInfo()<<fs.readLine();
    }
}

//二进制数据流
struct Information{
    QString name;
    QString sex;
    QString number;
    QDate date;
    int nums;
    Information(){}
    Information(QString name,
                QString sex,
                QString number,
                QDate date,
                int nums):name(name),sex(sex),number(number),date(date),nums(nums){}
};

void dataStreamClass(){
    //序列化与反序列化

    Information my_info("于良浩","男","123456789",QDate(2003,7,8),1433223);

    QByteArray data;
    QDataStream Ostream(&data,QFile::OpenModeFlag::ReadWrite);
    //序列化: 保存进QByteArray中
    Ostream<<my_info.name<<my_info.sex<<my_info.number<<my_info.date<<my_info.nums;
    qInfo()<<data;

    //反序列化
    Information your_info;
    QDataStream Istream(data); //从二进制流中读取
    Istream>>your_info.name>>your_info.sex>>your_info.number>>your_info.date>>your_info.nums;
    qInfo()<<your_info.date<<your_info.nums;
}

//文件信息
void testFileInfo(){
    QFileInfo file("test.txt");
    if (!file.exists()){
        qInfo()<<"file is not exists";
        return;
    }

    //获取文件大小
    qInfo()<<file.size();
    //获取文件名
    qInfo()<<file.fileName();
    //获取文件相对路径
    qInfo()<<file.filePath();
    //获取绝对路径
    qInfo()<<file.absoluteFilePath();

    QFileInfo flink("test.txt - 快捷方式.lnk");
    if (flink.exists()){
        if (flink.isSymLink()){
            //获取连接的目标： 绝对路径
            qInfo()<<flink.symLinkTarget();
        }
    }

    //获取目标文件
    qInfo()<<file.birthTime()<<file.lastModified()<<file.lastRead();
}

//目录
void testQDir(){
    QDir dir(".");
    if (!dir.exists()){
        qInfo()<<"dir not exists";
        return;
    }
    //创建目录
    dir.mkdir("test");
    //删除目录
    dir.rmdir("test");
    //递归创建目录
    dir.mkpath("a/b/c");
    //删除目录
    dir.rmpath("a/b/c");
    //递归删除文件目录
    //dir.removeRecursively();

    dir.rename("1.txt","1.mp4");

    //回到上一级
    dir.cdUp();
    qInfo()<<dir;

    dir.cd("14_FileOperation");
    qInfo()<<dir;

    //静态方法
    qInfo()<<QDir::homePath();
    qInfo()<<QDir::currentPath();

    //获取目录下面所有项: 设置过滤，不要 . 和 .. ，要文件和目录
    QStringList str = dir.entryList(QDir::Filter::NoDotAndDotDot |
                             QDir::Filter::Files | QDir::Filter::Dirs);
    qInfo()<<str;
}

//标准目录位置
void testStandardPaths(){
    //标准路径
    for (int i=0;i<19;i++){
        qInfo()<<QStandardPaths::StandardLocation(i)<<"\t\t"<<QStandardPaths::standardLocations(QStandardPaths::StandardLocation(i));
    }
    qInfo()<<"\n\n\n";
    //应该写入的路径
    for (int i=0;i<19;i++){
        qInfo()<<QStandardPaths::StandardLocation(i)<<"\t\t"<<QStandardPaths::writableLocation(QStandardPaths::StandardLocation(i));
    }

    //返回其名称
    qInfo()<<QStandardPaths::displayName(QStandardPaths::ApplicationsLocation);

    //查找exe执行文件路径：在指定路径中查找，否则到环境变量中寻找
    qInfo()<<QStandardPaths::findExecutable("cmake.exe");
    qInfo()<<QStandardPaths::findExecutable("g++.exe");
    qInfo()<<QStandardPaths::findExecutable("python.exe");
    qInfo()<<QStandardPaths::findExecutable("QQ.exe",QStringList()<<"D:\\于良浩\\Bin"); //指定路径
}

void testQSettings(){
    //组织名称应用程序信息
    //QSettings sets("强盛集团","ylh");

    //显式指定ini的路径
    QSettings sets("ylh.ini",QSettings::Format::IniFormat); //QApplication提前设置了
    //保存数据
    sets.setValue("username","hugeYlh");
    sets.setValue("password","123456");

    //获取保存位置
    //\\HKEY_CURRENT_USER\\Software\\强盛集团\\ylh
    qInfo()<<sets.fileName();

    auto username = sets.value("username").toString();
    auto password = sets.value("password").toString();
    qInfo()<<username<<password;

    QStringList strs = QStringList()<<"name1"<<"name2"<<"name3";
    QStringList pass = QStringList()<<"123"<<"456"<<"789";
    //写入数组
    sets.beginWriteArray("ylh");
    for (int i=0;i<strs.length();i++){
        sets.setArrayIndex(i);
        sets.setValue("user",strs[i]);
        sets.setValue("pass",pass[i]);
    }

    //分组
    sets.beginGroup("python");
    sets.setValue("version","3.10");
    sets.endGroup();

    sets.setValue("python/path","F:\\vscode\\mingw64\\opt\\bin");

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //提前指定
    QApplication::setOrganizationName("强盛集团");
    QApplication::setApplicationName("ylh");

    Widget w;
    w.show();

    return a.exec();
}
