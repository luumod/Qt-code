# Qt学习14：Designer设计师

category: 后端开发
date: 2023/07/01
status: Published
summary: Qt学习记录：Designer设计师初步了解，基本操作与功能。
tags: Qt
type: Post

**文章首发于我的个人博客：[欢迎大佬们来逛逛](https://www.helloylh.com/)**

# 什么是**Designer设计师？**

简单来说就是通过拖拖拽拽就可以实现窗口上控件的布局。

## **1. 创建带UI文件的项目**

我们在之前的学习中都是不用这个按钮的，现在我们需要点击它，项目就会自动生成一个 `widget.ui`  文件。

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled.png)

项目创建完成后点击  `widget.ui` 文件

这个文件的大概布局如下：

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%201.png)

## 2. **UI设计器的基本使用**

在`Contains` 中我们可以让这个控件里添加一些子控件，例如 **button group**，因此我们添加一个按钮组，然后添加如下的按钮：

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%202.png)

可以看到我们的按钮位置很乱，因此我们使用 **ctrl+单击**，来选择这五个按钮，然后点击上面的排列方式：垂直布局，其实就是**创建了一个垂直的布局**。

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%203.png)

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%204.png)

可以看到，在按钮组中又添加了一个垂直布局，然后又包含有4个按钮。

接下来我们对按钮的样式进行更改：

**直接选择某个控件，更改属性：文本，是否可选，尺寸信息（QWidget）等等**

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%205.png)

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%206.png)

注意这里的名称是我们**控件的对象名称**，不是文本名称。

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%207.png)

## 3. 关联信号与槽

如下：我们创建了一个`Widget`，然后在里面添加了这两个`QPushButton`：

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%208.png)

接下来我们关联他们两个的**信号与槽**：

**第一种方法：转到槽**

1. 右键按钮
2. 选择 **转到槽**
3. 我们就可以选择相应的**触发信号**
4. 然后我们就**直接跳转到了槽函数中**，我们直接处理事件即可！

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%209.png)

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%2010.png)

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%2011.png)

```cpp
void Widget::on_pushButton_clicked()
{
    auto file = QFileDialog::getOpenFileName(this,"打开文件");
    qInfo()<<file;
}
```

**第二种方法：通过信号与槽编辑器**。

1. 点击 `+` 号可以添加一个信号与槽的连接。

为了变量的可读性我们更改变量的名字。

我们只需要添加这一条记录然后保存，神奇的一幕发生了！ 我们无须编写任何的函数就自动连接好了，我们可以直接使用（**原理下面讲**）。

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%2012.png)

---

# UI文件解析与designer设计师原理

你有没有想到过上面的操作原理是什么，凭什么我们点击了两下就可以实现所有的功能？

这就用到了我们的  **ui 文件**

在我们设计完成后返回时，会看到这样一个文件：

这就是我们刚才**界面操作所生成的xml文件。**

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%2013.png)

这个xml文件内包含了我们之前在界面操作时的所有的选择与更改内容。

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%2014.png)

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%2015.png)

实际上我们刚才对窗口的操作就是对xml文件的操作，它提供了可视化的方便之处。

---

注意到我们的`widget.cpp` 文件中存在一个:

```cpp
#include "./ui_widget.h"
```

他是xml文件自动生成的一个头文件，位于：

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%2016.png)

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%2017.png)

然后我们打开看看。

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%2018.png)

可以看到里面的内容跟实际上就是我们所创建控件对象，然后分别在这两个函数中进行操作。

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%2019.png)

注意这个命名空间：

![Untitled](Qt%E5%AD%A6%E4%B9%A014%EF%BC%9ADesigner%E8%AE%BE%E8%AE%A1%E5%B8%88%2048cdc49f8759458fad30e51c1e8d7b90/Untitled%2020.png)

回到我们的 `widget.h` 文件中，发现其有一个

```cpp
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget ....
private:
    Ui::Widget *ui;
}
```

实际上就是创建了一个刚才的UI对象，然后在构造函数中：

```cpp
Widget::Widget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::Widget)
{
    ui->setupUi(this);
}
```

实际上就是调用了刚才的 setupUi函数。

---

# 信号与槽**原理**

这一个函数起到了这个作用：

```cpp
QMetaObject::connectSlotsByName(Widget);
```

查阅文档可知：

---

递归搜索给定对象的所有子对象，并将来自它们的匹配信号连接到遵循以下形式的对象槽：

```cpp
void on_<object name>_<signal name>(<signal parameters>);
```

让我们假设我们的对象有一个 QPushButton 类型的子对象，对象名为 button1。 捕捉按钮的 clicked() 信号的插槽是：

```cpp
void on_button1_clicked();
```

如果对象本身具有正确设置的对象名称，则其自身的信号也连接到其各自的插槽。

可以发现刚才的 ”打开文件“ 的操作就是这样的。

**因此我们使用这种方式可以直接手动创建信号与槽，只需遵循规则就行。**

---

# **自定义控件**

在使用Qt设计师进行窗口设计时，我们会通过拖拽使用设计师中的原生控件来进行界面的开发，但有时候那些标准窗口部件无法满足我们的需求，这时候就需要我们进行自定义控件的使用。而自定义控件又有两种方法，**提升法**及**插件法**，接下来咱们一一学习。

**创建项目：**

1. 先创建一个带界面文件的项目，然后右击项目名称，添加新文件...
2. 选择Qt->Qt设计师界面类
3. 界面模板选择Widget，并修改好类名，点击下一步，直至完成。
4. 将创建的界面类的文件添加到CMakeLists.txt中，并保存
5. 这边我要自定义的是一个开关控件，所以选择了在ui界面上添加了一个label，修改控件名称并调整合适大小

**添加资源：**

1. 将下面两种图片添加到，资源文件中
    
    > PS：记得将资源文件添加到CMakeLists.txt文件中哦
    > 
2. 回到scheckbox.ui文件，选中lable，找到属性中的styleSheet，添加资源，选择image，点击OK
3. 选择资源文件，这边选择check_off.png，点击OK
4. 看到出现下列界面(有效样式表)，点击OK
5. 这里将label的文本置空，同时修改控件的objectName，可以调整一下大小

“**提升到” 操作：**

1. 回到widget.ui，界面中添加一个widget控件，修改名称后选中控件，右键提升为…
2. 如图，新建提升的类，这里输入前面添加的ui界面设计师类名，点击添加
3. 勾选中刚刚添加的ImageSwitch类，选择提升
4. 这里可以看到widget控件已经成功提升为SCheckBox类
5. 编译运行，可以看到程序运行后就会出现之前添加的默认关闭的一个图片，这里我们可以重写SCheckBox类的鼠标按下事件来实现图片的切换。

```cpp
void SCheckBox::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"event:"<<event;
    if(switchFlag)
    {
        ui->switch_cbx->setStyleSheet("image: url(:/images/check_off.png);");
    }
    else
    {
        ui->switch_cbx->setStyleSheet("image: url(:/images/check_on.png);");
    }
     switchFlag = !switchFlag;
}
```

> PS:没有UI界面文件的类也可以提升哦，不过需要自己在paintEvent内绘制或者通过样式表指定
>