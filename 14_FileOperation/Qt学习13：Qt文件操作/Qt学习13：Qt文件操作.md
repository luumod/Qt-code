# Qt学习13：Qt文件操作

category: 后端开发
date: 2023/06/30
status: Published
summary: Qt学习记录：文件操作QFile， QTextStream，QDataStream，QDir，QStandardPaths，QSettings等详解
tags: Qt
type: Post

**文章首发于我的个人博客：[欢迎大佬们来逛逛](https://www.helloylh.com/)**

## **QFile**

QFile是一个用于读写文本、二进制文件和资源的I/O设备。 QFile可以单独使用，或者更方便地与`QTextStream`或`QDataStream`一起使用。

文件名通常在构造函数中传递，但它可以在任何时候使用setFileName()设置。 setFileName可以重新打开一个文件。

可以使用`exists`检查文件是否存在，并使用remove()删除文件。 (更高级的文件系统相关操作由QFileInfo和QDir提供。

常用函数：

- 构造函数打开一个文件
- fileName：输出文件的名称
- size：输出文件所占的字节大小
- read：读取一个文件
- readLine：读取文件的一行
- readAll：读取文件的所有
- open：打开文件
- close：关闭文件
- flush：刷新
- exist：检查文件是否存在
- remove：删除文件

```cpp
//文件读写操作    
void fileReadWrite(){
    QFile file("Qt.txt");
    if (!file.open(QFile::OpenModeFlag::WriteOnly)){
        qInfo()<<"open file failed";
        return ;
    }
    file.write("你好，我是xxx\n");

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
```

---

## 文本流类

QTextStream类提供了对于**字符数据**的输入输出的操作。

构造函数：

注意第一个和第二个的区别：如果传递的是一个QByteArray，则默认时只读的，重载了输入流。

如果传递的是QByteArray的地址，则是可读可写的，重载了输出流。

```cpp
QTextStream(const QByteArray &array, QIODeviceBase::OpenMode openMode = ReadOnly)
QTextStream(QByteArray *array, QIODeviceBase::OpenMode openMode = ReadWrite)
QTextStream(FILE *fileHandle, QIODeviceBase::OpenMode openMode = ReadWrite)
```

- 通过 >> 可以重定向输入。
- 通过 << 可以重定向输出。

```cpp
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
```

## QDataStream

QDataStream提供了以**二进制字节**的形式进行操作。

常用于序列化与反序列化。

- 序列化：将数据通过QDataStream存储在QByteArray中
- 反序列化：将数据通过QDataStream从QByteArray中读取出来。

```cpp
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

    Information my_info("ylh","男","123456789",QDate(2003,7,8),1433223);

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
```

---

## **QFileInfo**

QFileInfo类提供与系统无关的**文件信息**。

```cpp
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
```

---

## **QDir**

QDir类提供对**目录结构及其内容的访问**。

QDir可以进行类似于命令行的操作。

```cpp
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
```

## **QFileSystemWatcher**

QFileSystemWatcher类提供了一个接口，用于监视文件和目录的修改。

当文件被修改、重命名或从磁盘中删除时，将发出fileChanged()信号。

类似地，当目录或其内容被修改或删除时，也会发出directoryChanged()信号。 注意，一旦文件被重命名或从磁盘中删除，QFileSystemWatcher就会停止监视文件，而目录则会从磁盘中删除。

```cpp
class FileWatcher : public QFileSystemWatcher
{
public:
    FileWatcher()
    {
        connect(this, &FileWatcher::directoryChanged, this, &FileWatcher::onDirChanged);
        connect(this, &FileWatcher::fileChanged, this, &FileWatcher::onFileChanged);
    };
public slots:
    void onDirChanged(const QString& path)
    {
        qDebug() << path << "dirChanged";
    }
    void onFileChanged(const QString& path)
    {
        qDebug() << path << "fileChanged";
    }
private:
};
void test()
{
    FileWatcher watcher;
    watcher.addPath("./");
}
```

## **QStandardPaths**

QStandardPaths类提供了访问标准路径的方法。 所谓系统标准路径指的是本地文件系统中，用户的特定目录或系统的配置目录。比如在Windows系统中的“我的文档”，“视频”，“图片”等目录位置。

对于一个大型项目，系统的标准目录是保存数据，配置信息的一个非常有用的地方。例如，一个应用程序需要将下载好的文档保存在本地文件系统的某个地方，而它不能假设某个定好的路径是存在于磁盘上的。有的人可能会将这个文档保存在应用程序所在的工作目录中，当然这是个好方法，但有时应用程序并不希望将数据放在工作目录中，这是因为：

- 这会使得程序工作目录变得复杂，让用户来干预工作目录，这无疑是一件危险的事情，很可能会破坏程序。
- 有的程序会希望工作目录是只读的，所以禁止其它用户来对其进行修改。
- 如果某些配置文件是和其它程序是共享的，如若放置这些文件在某个程序的工作目录中，显然是不明智的做法，而最好的做法就是放在这些标准目录中啦。

对于系统标准目录，我们可以认定它是必然存在的（即使不存在，也可自动创建），但是不同的操作系统，可能有不一样的系统标准目录。例如“我的文档”目录位置

- Windows：C:/Users/username/Documents
- MacOs ：~/Documents
- Linux : ~/Documents
- Android :/Documents,//Documents
- IOS :/Documents

如果想要做跨平台的系统，像这些路径，你都得想办法获取，这只是一个我的文档，如果再加上“下载”，“图片”等标准路径，想想是不是都很麻烦。

然而，Qt却给我们提供了非常方便的类来获取这些标准目录路径，它就是马上要学习的QStandardPaths类。所有函数均为**静态函数**。

### **枚举：标准位置**

enum QStandardPaths::StandardLocation 描述了各种路径的位置，可用以下函数查询。

- `QString displayName(QStandardPaths::StandardLocation type)`
    
    根据路径类型，返回对应的本地路径名称，未找到返回空QString。
    
    **Example**
    
    ```cpp
    qDebug()<<QStandardPaths::displayName(QStandardPaths::DesktopLocation);
    输出:"Desktop"
    ```
    
- `QString writableLocation(QStandardPaths::StandardLocation type)`
    
    根据路径类型，返回对应的本地路径，未找到返回空QString。
    
    **Example**
    
    ```cpp
    qDebug()<< QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    输出:"C:/Users/Maye/Desktop"
    ```
    
- `QStringList standardLocations(QStandardPaths::StandardLocation type)`
    
    根据路径类型，返回该类型对应的所有目录路径。 如果可以确定的话，目录列表从高优先级到低优先级排序。 如果type没有定义，则此列表为空
    
    **Example**
    
    ```cpp
    qDebug()<<QStandardPaths::standardLocations(QStandardPaths::DataLocation);
    输出:("C:/Users/Maye/AppData/Local/test", "C:/ProgramData/test", "F:/MyCode/QtCode/build-QtCourse-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/test/debug", "F:/MyCode/QtCode/build-QtCourse-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/test/debug/data", "F:/MyCode/QtCode/build-QtCourse-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/test/debug/data/test"
    ```
    

---

### **在指定位置查找文件**

- `QString findExecutable(const QString &executableName, const QStringList &paths = QStringList())`

在指定的路径中查找名为executableName的可执行文件，如果paths为空，则在系统路径中查找。 系统路径指PATH环境变量的值。 如果存在，返回可执行文件的绝对文件路径，如果没有找到，则返回空字符串。

**Example**

```cpp
qDebug()<<QStandardPaths::findExecutable("calc.exe");   //只要设置了path环境变量，都可以找到
qDebug()<<QStandardPaths::findExecutable("7z.exe",QStringList()<<"D:\\MySoftWare\\7-Zip");  //如果没有设置path环境变量，可以自己指定多个路径
```

- `QString locate(QStandardPaths::StandardLocation type, const QString &fileName, QStandardPaths::LocateOptions options = LocateFile)`
- `QStringList locateAll(QStandardPaths::StandardLocation type, const QString &fileName, QStandardPaths::LocateOptions options = LocateFile)`
    
    根据标准目录类型，在该目录中查找名为fileName的文件或目录。 返回找到的文件或目录的完整路径(取决于options)。 如果找不到这样的文件或目录，则返回一个空字符串
    

**Example**

```cpp
qDebug()<< QStandardPaths::locate(QStandardPaths::StandardLocation::DownloadLocation,"下拉.png");
```

```cpp
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
```

---

## **QSettings**

QSettings提供了关于注册表的操作：

```cpp
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
```