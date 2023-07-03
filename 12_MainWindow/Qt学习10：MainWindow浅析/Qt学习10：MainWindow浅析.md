# Qt学习10：MainWindow浅析

category: 后端开发
date: 2023/06/12
status: Published
summary: Qt学习记录：MainWindow结构 QMenuBar  QToolBar QDockWidget QStatusBar 与 QSystemTrayIcon 托盘等
tags: Qt
type: Post

**文章首发于我的个人博客：[欢迎大佬们来逛逛](https://www.helloylh.com/)**

# QMainWindow的基本结构

- **QMenuBar**：菜单栏
- **QToolBar**：工具栏
- **QDockWidget**：浮动窗口
- **QStatusBar**：状态栏

![Untitled](https://s2.loli.net/2023/06/20/aLgqnNjkPIDe69y.png)

---

## QMenuBar

菜单栏：只能有唯一一个。

![Untitled 1.png](https://s2.loli.net/2023/06/20/74TSGuilfdp8PKH.png)

通过 `**menuBar()**` 来获得MainWindow**唯一**的菜单栏

继承自：QWidget

基本操作函数：

1. **addAction**：添加行为QAction
2. **addMenu**：添加菜单
3. **addSeparator**：添加分割线

我们在添加Menu后还可以接着对Menu进行**嵌套操作。**比如对一个菜单项添加项目：`addAction` 

我们可以指定很多对此菜单项的行为的操作：

例如直接对这个菜单项行为**添加快捷键**

```cpp
// QMenu的addAction
QAction *addAction(const QIcon &icon, const QString &text)
QAction *addAction(const QString &text, const QObject *context, Functor functor, const QKeySequence &shortcut = 0)
```

对于菜单条的addMenu可以直接使用 `“文本(&E)”` 的方式**设置快捷键**

信号：

1. **hovered**：鼠标悬停
2. **triggered**：鼠标点击

槽函数：

1. **setVisible**：设置是否可见

```cpp
void MainWindow::testMenuBar()
{
    auto mainMenuBar=menuBar();
    QMenu* fileMenu=mainMenuBar->addMenu("文件");
    QMenu* pro=fileMenu->addMenu("项目");
    pro->addAction("打开");
    pro->addAction("保存",this,&MainWindow::on_Ctrl_S,QKeySequence("Ctrl+S"));
    pro->addAction("新建");
    fileMenu->addSeparator();
    fileMenu->addAction("关闭");
    fileMenu->addAction("视图");

    QMenu* editMenu=mainMenuBar->addMenu("编辑(&E)");

    connect(mainMenuBar,&QMenuBar::hovered,this,[=](QAction* act){
        qInfo()<<act->text();
    });
}
```

---

## QToolBar

工具栏：可以有多个。

![Untitled 2.png](https://s2.loli.net/2023/06/20/crEth4lwzxusSP5.png)

在一个工具栏上面可以添加很多**控件**

它继承自：`QWidget` 

通过 **`addToolBar()`** 来获得工具栏。

基本操作函数：

1. **addAction**：添加行为
2. **addWidget**：**添加控件**。通过这个函数可以添加很多继承自QWidget的控件，例如按钮，文本框等。
3. **setFloatable**：设置是否浮动
4. **setMoveable**：设置是否能够移动

在工具栏上添加很多控件以实现工具栏的效果：

```cpp
void MainWindow::testToolBar()
{
    auto mainToolBar=addToolBar("ToolBar1");
    mainToolBar->addAction(style()->standardPixmap(QStyle::StandardPixmap::SP_ArrowRight),"前进");
    mainToolBar->addAction(style()->standardPixmap(QStyle::StandardPixmap::SP_ArrowLeft),"后退");
    mainToolBar->addSeparator();

    auto chx=new QCheckBox("自动保存",this);
    mainToolBar->addWidget(chx);
    
    auto edit=new QLineEdit(this);
    edit->setPlaceholderText("搜索内容");
    mainToolBar->addWidget(edit);

    auto btn=new QPushButton("搜索",this);
    mainToolBar->addWidget(btn);

    auto toolbtn=new QToolButton(this);
    toolbtn->resize(150,150);
    toolbtn->setText("返回桌面");
    toolbtn->setIcon(style()->standardPixmap(QStyle::StandardPixmap::SP_DesktopIcon));
    toolbtn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    mainToolBar->addWidget(toolbtn);
}
```

---

## QStatusBar

状态栏：只能有唯一一个

![Untitled](Qt%E5%AD%A6%E4%B9%A010%EF%BC%9AMainWindow%E6%B5%85%E6%9E%90%2044f43f9b49f6496ea99f0c51ef10cc0c/Untitled%203.png)

表示这个窗口的状态。

它继承自：`QWidget`

使用 **`statusBar()`** 来获得窗口中唯一的状态栏控件。

基本操作函数：

1. **addAction**：添加行为
2. **addWidget**：添加控件
3. **addPermanentWidget**：在右侧添加控件与行为（默认在左边）

信号：

1. **messageChanged**：状态信息改变时

槽函数：

1. **showMessage**：显示信息
2. **clearMessage**：清除信息

我们可以使用 showMessage 来对状态栏显示某种信息：

```cpp
void MainWindow::testStatusBar()
{
    auto sBar=statusBar();
    sBar->addWidget(new QLabel("准备就绪",this));
    sBar->addWidget(new QPushButton("发射",this));
    sBar->addPermanentWidget(new QLabel("完成",this));
}
...
void MainWindow::on_Ctrl_S()
{
		//显示信息，持续两秒
    statusBar()->showMessage("保存成功",2000);
}
```

---

## QDockWidget

浮动（可停靠）窗口：可以有多个

![Untitled](Qt%E5%AD%A6%E4%B9%A010%EF%BC%9AMainWindow%E6%B5%85%E6%9E%90%2044f43f9b49f6496ea99f0c51ef10cc0c/Untitled%204.png)

类似于 VS 中的窗口。

它继承自：`QWidget`

它表示一个浮动（可停靠）的窗口，可以拖动它的位置，或者固定它的位置。

注意：如果需要对这个窗口进行测试，必须首先设置一个**中心区域**：

```cpp
setCentralWidget(new QPlainTextEdit(this));
```

因为只有设置了这个中心文本区域后，我们才能看到浮动窗口的正确的显示位置。

通过 **`addDockWidget()`** 来添加浮动窗口：在某个区域添加一个浮动窗口

```cpp
void QMainWindow::addDockWidget(Qt::DockWidgetArea area, QDockWidget *dockwidget)
```

基本操作函数：

1. **tabifyDockWidget**：设置浮动窗口的重叠
2. **setFloating**：设置可浮动，否则是停靠的。

```cpp
void MainWindow::testDockWidget()
{
    //设置中心区域
    setCentralWidget(new QPlainTextEdit(this));
    
    auto DockWidget1=createDockWidget("解决方案资源管理器");
    auto DockWidget2=createDockWidget("团队资源管理器");
    auto DockWidget3=createDockWidget("命令窗口");
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea,DockWidget1);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea,DockWidget2);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea,DockWidget3);

    //设置浮动窗口的堆叠
    tabifyDockWidget(DockWidget1,DockWidget2);
    tabifyDockWidget(DockWidget2,DockWidget3);
}
```

---

# QSystemTrayIcon

系统的托盘图片：只能有唯一一个。

![Untitled](Qt%E5%AD%A6%E4%B9%A010%EF%BC%9AMainWindow%E6%B5%85%E6%9E%90%2044f43f9b49f6496ea99f0c51ef10cc0c/Untitled%205.png)

图中的 M 就是我的程序的图片。

通过QSystemTrayIcon 的构造函数来创建一个托盘图标，并且显示出来：

注意：必须传递一个图片和调用show()，否则不会显示。

```cpp
auto trayIcon=new QSystemTrayIcon(QIcon(":/icon.png"),this);
trayIcon->show();
```

它继承自：`QObject`

基本操作函数：

1. **setContextMenu**：设置上下文菜单，可用于鼠标右键图标显示的菜单
2. **setIcon**：设置图标
3. **setToolTip**：设置图标的文本解释

信号：

1. **activated**：激活状态，enum QSystemTrayIcon::ActivationReason的枚举表示了所有可能的状态

槽函数：

1. **hide**：隐藏
2. **show**：显示
3. **showMessage**：显示一条信息

我们为这个托盘图标设置了一个菜单，并且鼠标右键和双击都可以显示出来。

我们还在菜单中设置了一些行为：控制程序退出与窗口最小化切换。

```cpp
void MainWindow::SystemTrayIcon()
{
    auto trayIcon=new QSystemTrayIcon(QIcon(":/icon.png"),this);
    trayIcon->show();

    QMenu* trayMenu=new QMenu(this);
    trayMenu->addAction("退出",qApp,[=](){
        qApp->quit(); //退出系统
    });
    trayMenu->addSeparator();
    trayMenu->addAction("最小化",this,[=](){
        this->setVisible(!this->isVisible());
    });
    trayMenu->addAction("别点我",this,[=](){
        //trayIcon->showMessage("警告，电脑即将爆炸","错误操作，爆炸倒计时!");
        qInfo()<<"!!!!";
    });
    //添加上下文菜单
    trayIcon->setContextMenu(trayMenu);

    trayIcon->setToolTip("你好");

    //处理激活原因
    connect(trayIcon,&QSystemTrayIcon::activated,this,[=](QSystemTrayIcon::ActivationReason reason){
        switch (reason) {
        case QSystemTrayIcon::Unknown:  //0

            break;
        case QSystemTrayIcon::Context:  //1

            break;
        case QSystemTrayIcon::DoubleClick://2
            //弹出菜单
            trayIcon->contextMenu()->popup(QCursor::pos());
            break;
        case QSystemTrayIcon::Trigger:  //左键点击
            //窗口切换
            this->setVisible(!this->isVisible());
            break;
        default:
            break;
        }
        qInfo()<<reason;
    });
}
```