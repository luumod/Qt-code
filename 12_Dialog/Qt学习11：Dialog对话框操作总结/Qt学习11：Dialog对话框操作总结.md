# Qt学习11：Dialog对话框操作总结

category: 后端开发
date: 2023/06/18
status: Published
summary: Qt学习记录：各种对话框QDialog的操作总结：QDialog，QFileDialog，QMessageBox，QFontDialog，QColorDialog等
tags: Qt
type: Post

**文章首发于我的个人博客：[欢迎大佬们来逛逛](https://www.helloylh.com/)**

# **QDialog**

Qt中使用QDialog来实现对话框，QDialog继承自QWidget，对话框分为**`三种`**：

- **模态对话框**：在弹出模态对话框时，除了该对话框整个应用程序窗口**都无法接受用户响应**，处于等待状态，直到模态对话框被关闭
- **半模态对话框**：又叫做无模式对话框，即弹出非模态对话框时，**用户仍然可以对其他窗口进行操作**，不会因为这个对话框未关闭就不能操作其他窗口。
- **非模态对话框**：半模态对话框区别于模态与非模态对话框，或者说是介于两者之间，也就是说半模态对话框**会阻塞窗口的响应，但是不会影响后续代码的执行**。

常用操作：

- **exec**：显示模态对话框
- **open**：显示半模态对话框
- **show**：显示非模态对话框
- **setModal**：设置模式，如果为true，则show显示的是模态对话框，如果为false，则show显示的是非模态对话框，默认为false
- **setSizeGripEnabled**：设置显示右下角的拖动图标

```cpp
// 构造函数
QDialog::QDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

void setSizeGripEnabled(bool)   //设置启用大小手柄

[virtual slot] void open()                  // 半模态显示窗口
[virtual slot] int QDialog::exec();         // 模态显示窗口

// 隐藏模态窗口, 并且解除模态窗口的阻塞, 将 exec() 的返回值设置为 QDialog::Accepted
[virtual slot] void QDialog::accept();
// 隐藏模态窗口, 并且解除模态窗口的阻塞, 将 exec() 的返回值设置为 QDialog::Rejected
[virtual slot] void QDialog::reject();
// 关闭对话框并将其结果代码设置为r。finished()信号将发出r;如果r是QDialog::Accepted 或 QDialog::Rejected，则还将分别发出accept()或Rejected()信号。
[virtual slot] void QDialog::done(int r);
```

常用信号：

```cpp
void QDialog::accepted();
void QDialog::rejected();
void QDialog::finished(int result);示例
```

简单示例：

如下显示的是一个**半模态对话框**：

```cpp
void MainWindow::actionOnHalfDialog()
{
    //半模态对话框
    QDialog* dlg=new QDialog(this);
    dlg->open(); //不会阻塞程序，即可以执行下面的代码
    dlg->setAttribute(Qt::WA_DeleteOnClose); //关闭隐藏
    qInfo()<<__FUNCTION__;
}
```

---

# **QDialogButtonBox**

QDialogButtongBox类是一个包含**很多按钮的控件**，在对话框中有多个按钮需要**分组排列**的按钮时，可以使用QDialogButtongBox类。

简而言之就是在**同一个对话框中添加按钮**，类似于QButtonGroup。

常用函数：

- **addButton**：添加按钮，注意其具有重载，一个是系统的标准按钮：**`StandardButtons`**  ；另一个是具有一个**`ButtonRole`**的属性，即可以指定按钮的角色，然后可以根据不同的角色进行区分操作。
- **buttonRole**：返回某个按钮的角色
- **buttons**：返回一个QList，其包含所有的按钮。

```cpp
void addButton(QAbstractButton *button, QDialogButtonBox::ButtonRole role)
QPushButton *addButton(const QString &text, QDialogButtonBox::ButtonRole role)
QPushButton *addButton(QDialogButtonBox::StandardButton button)
void setStandardButtons(QDialogButtonBox::StandardButtons buttons)
```

常用信号：

```cpp
void accepted()     //当单击按钮框中的按钮时将发出此信号，只要该按钮是用AcceptRole或YesRole定义的。
void clicked(QAbstractButton *button)   //当单击按钮框中的按钮时，将发出此信号,具体按钮由button指定
void helpRequested() //当按钮框中的按钮被单击时，这个信号就会发出，只要它是用HelpRole定义的。
void rejected()      //当单击按钮框中的按钮时，此信号将被触发，只要它是用RejectRole或NoRole定义的
```

简单示例：

```cpp
void MainWindow::actionOnNoDialog()
{
    //非模态对话框
    QDialog* dlg=new QDialog(this);
    dlg->setSizeGripEnabled(true); //设置抓取手柄

    //添加对话框按钮组
    auto* _dbbox=new QDialogButtonBox(dlg);
    //设置系统标准按钮
    _dbbox->addButton(QDialogButtonBox::StandardButton::Ok);
    _dbbox->addButton(QDialogButtonBox::StandardButton::Yes);
    _dbbox->addButton(QDialogButtonBox::StandardButton::No);
    //设置角色
    _dbbox->addButton("选择",QDialogButtonBox::ApplyRole);

    //系统标准按钮直接具有信号
    connect(_dbbox,&QDialogButtonBox::accepted,this,[=](){
        qInfo()<<"accepted";
    });
    connect(_dbbox,&QDialogButtonBox::rejected,this,[=](){
        qInfo()<<"rejected";
    });

    //自定义的角色需要获取这个角色然后进行判断操作
    connect(_dbbox,&QDialogButtonBox::clicked,this,[=](QAbstractButton* btn){
        if (_dbbox->buttonRole(btn)==QDialogButtonBox::ApplyRole){
            dlg->accept();
            dlg->hide();
        }
    });
    dlg->show();
    qInfo()<<__FUNCTION__;
}
```

![Untitled](Qt%E5%AD%A6%E4%B9%A011%EF%BC%9ADialog%E5%AF%B9%E8%AF%9D%E6%A1%86%E6%93%8D%E4%BD%9C%E6%80%BB%E7%BB%93%2057e59474f6a34f92b224e50c4aeb4c31/Untitled.png)

---

# **QMessageBox**

![Untitled](Qt%E5%AD%A6%E4%B9%A011%EF%BC%9ADialog%E5%AF%B9%E8%AF%9D%E6%A1%86%E6%93%8D%E4%BD%9C%E6%80%BB%E7%BB%93%2057e59474f6a34f92b224e50c4aeb4c31/Untitled%201.png)

QMessageBox 对话框类是 QDialog 类的子类, 通过这个类可以**显示一些简单的提示框.**

用于展示警告、错误、问题等信息。

关于这个类我们只需要掌握一些静态方法的使用就可以了。

常用操作：

- **about**：关于提示框
- **critical**：严重警告提示框
- **information**：提示框
- **question**：问题提示框
- **warning**：警告提示框

```cpp
void MainWindow::testMessage()
{
    //QMessageBox::aboutQt(this);
    //QMessageBox::about(this,"关于","<a href='https://www.helloylh.com'>异性交友网站</a>");
    //QMessageBox::critical(this,"致命错误","请重启电脑",QMessageBox::StandardButton::Cancel);

    if (QMessageBox::StandardButton::Ok == QMessageBox::information(this,"提示","请重启电脑!")){
        qInfo()<<"OK!";
    }
    else{
        qInfo()<<"NO!";
    }

}
```

---

# **QFileDialog**

![Untitled](Qt%E5%AD%A6%E4%B9%A011%EF%BC%9ADialog%E5%AF%B9%E8%AF%9D%E6%A1%86%E6%93%8D%E4%BD%9C%E6%80%BB%E7%BB%93%2057e59474f6a34f92b224e50c4aeb4c31/Untitled%202.png)

QFileDialog 对话框类是 QDialog 类的子类, 通过这个类可以选择要打开/保存的文件或者目录。

关于这个类我们只需要掌握一些静态方法的使用就可以了。

常用操作：

- **getExistingDirectory**：获取已存在的**目录路径**
- **getOpenFileName**：获取打开的**文件**的名字
- **getOpenFileUrl**：获取**文件的url**
- **getSaveFileName**：获取保存文件的名字，**可以用于文件的保存**。

```cpp
void MainWindow::testQFileDialog()
{
    //获取当前存在的目录
    //auto Dir = QFileDialog::getExistingDirectory(this,"请选择文件","C:\\users");
    //qInfo()<<Dir;

    //获取url形式
    //auto DirUrl=QFileDialog::getExistingDirectoryUrl();
    //qInfo()<<DirUrl;

    //QString filename = QFileDialog::getOpenFileName(this,"选择文件","."
    //    ,"images (*.png *.jpg *.bmp);;Video(*.avi *.mp4 *.wav)");
    //qInfo()<<filename;

    QStringList filenames = QFileDialog::getOpenFileNames(this,"选择文件","./");
    qInfo()<<filenames;
}
```

注意我们可以为选择的文件添加**过滤器**：

直接在其静态成员函数的：**const QString &filter = QString()** 进行指定即可

如： 

- images (*.png  *.bmp *.jpg)
- exe (*.exe)
- vedio (*.avi *.mp4)

---

# **QFontDialog**

![Untitled](Qt%E5%AD%A6%E4%B9%A011%EF%BC%9ADialog%E5%AF%B9%E8%AF%9D%E6%A1%86%E6%93%8D%E4%BD%9C%E6%80%BB%E7%BB%93%2057e59474f6a34f92b224e50c4aeb4c31/Untitled%203.png)

设置字体的对话框。

```cpp
QFont::QFont();
/*
参数:
    - family: 本地字库中的字体名, 通过 office 等文件软件可以查看
    - pointSize: 字体的字号
    - weight: 字体的粗细, 有效范围为 0 ~ 99
    - italic: 字体是否倾斜显示, 默认不倾斜
*/
QFont::QFont(const QString &family, int pointSize = -1, int weight = -1, bool italic = false);

// 设置字体
void QFont::setFamily(const QString &family);
// 根据字号设置字体大小
void QFont::setPointSize(int pointSize);
// 根据像素设置字体大小
void QFont::setPixelSize(int pixelSize);
// 设置字体的粗细程度, 有效范围: 0 ~ 99
void QFont::setWeight(int weight);
// 设置字体是否加粗显示
void QFont::setBold(bool enable);
// 设置字体是否要倾斜显示
void QFont::setItalic(bool enable);

// 获取字体相关属性(一般规律: 去掉设置函数的 set 就是获取相关属性对应的函数名)
QString QFont::family() const;
bool QFont::italic() const;
int QFont::pixelSize() const;
int QFont::pointSize() const;
bool QFont::bold() const;
int QFont::weight() const;
```

静态函数：

- setFont …

```cpp
[static] QFont QFontDialog::getFont(bool *ok, const QFont &initial, QWidget *parent = nullptr, const QString &title = QString(), QFontDialog::FontDialogOptions options = FontDialogOptions());

[static] QFont QFontDialog::getFont(bool *ok, QWidget *parent = nullptr);窗口字体的设置
```

示例如下：

我们为一个**Label**设置字体。

```nix
void MainWindow::testFontDialog()
{
    lab=new QLabel(this);
    lab->setText("测试字体 helloylh");
    lab->setGeometry(200,200,200,200);
    auto btn=new QPushButton("选择字体",this);
    btn->setGeometry(10,50,80,30);
    connect(btn,&QPushButton::clicked,this,[=](){
        bool ok=false;
        auto font = QFontDialog::getFont(&ok,this);
        lab->setFont(font);
    });

}
```

---

# **QColorDialog**

![Untitled](Qt%E5%AD%A6%E4%B9%A011%EF%BC%9ADialog%E5%AF%B9%E8%AF%9D%E6%A1%86%E6%93%8D%E4%BD%9C%E6%80%BB%E7%BB%93%2057e59474f6a34f92b224e50c4aeb4c31/Untitled%204.png)

配合字体选择框一起使用，可以指定**颜色**。它是一个颜色选择框。

```cpp
// 构造函数
QColor::QColor(Qt::GlobalColor color);
QColor::QColor(int r, int g, int b, int a = ...);
QColor::QColor();

// 参数 red, green, blue, alpha 取值范围是 0-255
void QColor::setRed(int red);
void QColor::setGreen(int green);
void QColor::setBlue(int blue);
void QColor::setAlpha(int alpha);
void QColor::setRgb(int r, int g, int b, int a = 255);

int QColor::red() const;
int QColor::green() const;
int QColor::blue() const;
int QColor::alpha() const;
void QColor::getRgb(int *r, int *g, int *b, int *a = nullptr) const;
```

静态函数：

```cpp
// 弹出颜色选择对话框, 并返回选中的颜色信息
[static] QColor QColorDialog::getColor(const QColor &initial = Qt::white, QWidget *parent = nullptr, const QString &title = QString(), QColorDialog::ColorDialogOptions options = ColorDialogOptions());
```

测试代码：

为**label**设置颜色。

```cpp
void MainWindow::testQColorDialog()
{
    auto btn=new QPushButton("选择颜色",this);
    btn->setGeometry(80,50,80,30);
    connect(btn,&QPushButton::clicked,this,[=](){
        auto color=QColorDialog::getColor();
        lab->setStyleSheet(QString("color: rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue()));
    });
}
```

---

## **2.5 QInputDialog**

```cpp
[static] double QInputDialog::getDouble(QWidget *parent, const QString &title, const QString &label, double value = 0, double min = -2147483647, double max = 2147483647, int decimals = 1, bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

[static] int QInputDialog::getInt(QWidget *parent, const QString &title, const QString &label, int value = 0, int min = -2147483647, int max = 2147483647, int step = 1, bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

[static] QString QInputDialog::getItem(QWidget *parent, const QString &title, const QString &label, const QStringList &items, int current = 0, bool editable = true, bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags(), Qt::InputMethodHints inputMethodHints = Qt::ImhNone)

[static] QString QInputDialog::getMultiLineText(QWidget *parent, const QString &title, const QString &label, const QString &text = QString(), bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags(), Qt::InputMethodHints inputMethodHints = Qt::ImhNone);

[static] QString QInputDialog::getText(QWidget *parent, const QString &title, const QString &label, QLineEdit::EchoMode mode = QLineEdit::Normal, const QString &text = QString(), bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags(), Qt::InputMethodHints inputMethodHints = Qt::ImhNone);
```

## **2.6 QProgressDialog**

```cpp
// 构造函数
/*
参数:
    - labelText: 对话框中显示的提示信息
    - cancelButtonText: 取消按钮上显示的文本信息
    - minimum: 进度条最小值
    - maximum: 进度条最大值
    - parent: 当前窗口的父对象
    - f: 当前进度窗口的flag属性, 使用默认属性即可, 无需设置
*/
QProgressDialog::QProgressDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
QProgressDialog::QProgressDialog(const QString &labelText, const QString &cancelButtonText, int minimum, int maximum, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

// 设置取消按钮显示的文本信息
[slot] void QProgressDialog::setCancelButtonText(const QString &cancelButtonText);

// 公共成员函数和槽函数
QString QProgressDialog::labelText() const;
void QProgressDialog::setLabelText(const QString &text);

// 得到进度条最小值
int QProgressDialog::minimum() const;
// 设置进度条最小值
void QProgressDialog::setMinimum(int minimum);

// 得到进度条最大值
int QProgressDialog::maximum() const;
// 设置进度条最大值
void QProgressDialog::setMaximum(int maximum);

// 设置进度条范围(最大和最小值)
[slot] void QProgressDialog::setRange(int minimum, int maximum);

// 得到进度条当前的值
int QProgressDialog::value() const;
// 设置进度条当前的值
void QProgressDialog::setValue(int progress);

bool QProgressDialog::autoReset() const;
// 当value() = maximum()时，进程对话框是否调用reset()，此属性默认为true。
void QProgressDialog::setAutoReset(bool reset);

bool QProgressDialog::autoClose() const;
// 当value() = maximum()时，进程对话框是否调用reset()并且隐藏，此属性默认为true。
void QProgressDialog::setAutoClose(bool close);

// 判断用户是否按下了取消键, 按下了返回true, 否则返回false
bool wasCanceled() const;

// 重置进度条
// 重置进度对话框。wascancelled()变为true，直到进程对话框被重置。进度对话框被隐藏。
[slot] void QProgressDialog::cancel();
// 重置进度对话框。如果autoClose()为真，进程对话框将隐藏。
[slot] void QProgressDialog::reset();

// 信号
// 当单击cancel按钮时，将发出此信号。默认情况下，它连接到cancel()槽。
[signal] void QProgressDialog::canceled();

// 设置窗口的显示状态(模态, 非模态)
/*
参数:
    Qt::NonModal  -> 非模态
    Qt::WindowModal -> 模态, 阻塞父窗口
    Qt::ApplicationModal -> 模态, 阻塞应用程序中的所有窗口
*/
void QWidget::setWindowModality(Qt::WindowModality windowModality);
```