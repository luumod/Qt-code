# Qt学习12：常用Layout布局方式总结

category: 后端开发
date: 2023/06/27
status: Published
summary: Qt学习记录：常用布局QBoxLayout，QGridLayout，QFormLayout，QStackedLayout，QTabWidget，QStackedWidget，QSplitter等类详解
tags: Qt
type: Post

**文章首发于我的个人博客：[欢迎大佬们来逛逛](https://www.helloylh.com/)**

# **布局管理类**

布局管理器类用于对我们窗口中的控件进行**排序放置。**如果我们有很多的控件，那么你一定会想到我们该如何排序这些控件的位置呢，我们可以通过**Layout**布局管理类来自动管理我们的窗口控件布局。

它包括几个主要的布局类：

- **QBoxLayout**：盒子布局
- **QGridLayout**：网格布局
- **QFormLayout**：表单布局
- **QStackedLayout**：堆栈布局

---

设置布局的基本步骤：

1. 创建控件
2. 创建布局管理类
3. 将控件添加到布局管理类中
4. 设置布局管理类为此时的窗口布局（这一步可以没有，因为当第二步的时候，就可以直接设置）

## BoxLayout：盒子布局

QBoxLayout可以在水平方向或垂直方向上排列控件，它分别派生了`QHBoxLayout`、`QVBoxLayout`子类。

- **QHBoxLayout**：水平布局，在水平方向上排列控件，即：左右排列。
- **QVBoxLayout**：垂直布局，在垂直方向上排列控件，即：上下排列。

基本函数功能：

- **addWidget**：添加控件到布局中
- **addStretch**：添加拉伸区域
- **addLayout**：布局中添加布局，用于嵌套布局
- insert等其他函数

基本使用：

```cpp
void Widget::testQBoxLayout()
{
    //创建控件
    QLabel* lab = new QLabel("请输入账号",this);
    QLineEdit* edit = new QLineEdit(this);

    //创建布局
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);
    //设置不同的方向
    //layout->setDirection(QBoxLayout::Direction::Up);

    //布局中添加控件
    layout->addWidget(lab);
    layout->addWidget(edit);

    //将布局添加到窗口
    //this->setLayout(layout);  设置了this，所以不用设置这一步
}
```

我们可以随意拉伸：

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled.png)

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%201.png)

---

## 布局嵌套

布局可以进行嵌套，因为其具有`addLayout`这个函数，**我们可以在一个主布局中添加多个子布局，每个子布局中又含有一些控件。**

例如下面的代码，我们**模拟登录**：

1. 首先我们创建**账号**标签和用户账号输入框，然后把这两个添加到一个**水平布局**中
2. 然后我们创建**密码**标签和用户密码输入框，然后把这两个添加到一个**水平布局**中
3. **最后我们把这两个水平布局合并到一个总的垂直布局中**

水平盒子布局：`**QHBoxLayout**`

垂直盒子布局：`**QVBoxLayout**`

```cpp
void Widget::testNestLayout()
{
    auto lab1 = new QLabel("username",this);
    auto edit1 = new QLineEdit(this);
    auto lab2 = new QLabel("password",this);
    auto edit2 = new QLineEdit(this);

    //创建水平的布局，但是不指定父对象，最后再添加一个最终的布局
    QHBoxLayout* layout1= new QHBoxLayout();
    QHBoxLayout* layout2= new QHBoxLayout();

    layout1->addWidget(lab1);
    layout1->addWidget(edit1);

    layout2->addWidget(lab2);
    layout2->addWidget(edit2);

    //设置一个最终的布局，然后添加this
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout1);
    vlayout->addLayout(layout2);
}
```

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%202.png)

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%203.png)

---

## 其他功能

我们创建五个按钮用于测试：

- **addStretch**：添加拉伸条
- **setContentsMargins**：设置边距
- **setStretchFactor**：设置拉伸因子
- **setSpacing**：设置每个控件之间距离
- **itemAt**：获取布局内的控件元素
1. 首先我们创建五个按钮控件然后把他们添加到**水平布局**中。
2. 然后我们为每个控件之间添加一个**拉伸区域**。

```cpp
void Widget::testButton()
{
    QPushButton* btn1 = new QPushButton("btn1",this);
    QPushButton* btn2 = new QPushButton("btn2",this);
    QPushButton* btn3 = new QPushButton("btn3",this);
    QPushButton* btn4 = new QPushButton("btn4",this);
    QPushButton* btn5 = new QPushButton("btn5",this);

    //创建布局
    QHBoxLayout* hlayout =new QHBoxLayout(this);
    hlayout->addWidget(btn1);
    //设置按钮之间的拉伸空间
    hlayout->addStretch(1);
    hlayout->addWidget(btn2,2); //按钮内的拉伸方式
    hlayout->addStretch(2);

    hlayout->addWidget(btn3,3);
    hlayout->addStretch(3);

    hlayout->addWidget(btn4,4);
    hlayout->addStretch(4);

    hlayout->addWidget(btn5);

    //设置边距
    hlayout->setContentsMargins(10,10,10,10);

    //设置按钮之间的间距
    hlayout->setSpacing(10);

    //设置拉伸因子
    //hlayout->setStretchFactor(btn1,2,this);

    //获取布局内的元素(包括拉伸因子控件)
    auto wgs = hlayout->itemAt(0);
    auto w_btn1 = static_cast<QPushButton*>(wgs->widget());
    qInfo()<<w_btn1->text()<<hlayout->count();
}
```

例如初始状态是这样的：

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%204.png)

如果我们在

- btn1 和 btn2 之间设置addStretch（1）
- btn2 和 btn3 之间设置addStretch（2）
- btn3 和 btn4 之间设置addStretch（3）
- btn4 和 btn5 之间设置addStretch（4）

那么就会出现这样的情况：

有没有注意到他们**每个之间的距离**就是呈比例关系：**1：2：3：4**

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%205.png)

注意到我们的 **`btn4`** 为什么其本身还会变大？ **因为在 addWidget的时候我们还可以为控件设置拉伸系数。**

其他函数的功能请自己测试。

另外我们获取第一个按钮，并且对它进行操作，可以使用**`itemAt(index)`** 来指定获取布局中的第index个控件，从0开始，注意：**addStretch创建的也是一个控件**，因此要注意index的值。

获取第一个按钮itemAt获得的是`**QLayoutItem**`，需要强转为QPshButton类型。

```cpp
auto wgs = hlayout->itemAt(0);
auto w_btn1 = static_cast<QPushButton*>(wgs->widget());
qInfo()<<w_btn1->text()<<hlayout->count();
```

---

## GridLayout：网格布局

网格布局也叫格栅布局(多行多列)

他是为每个控件指定一个行和列的值进行排列的。我们看一个例子：

假如我们需要实现这样的一个窗口，那么该如何创建，使用何种布局类？

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%206.png)

代码如下：

前面的添加控件不用多说了，我们重点关注**`addWidget`**的过程：

其构造函数如下：

- **QWidget**：添加的控件
- **fromRow**：在第几行
- **fromColumn**：在第几列
- **rowSpan**：占用几行
- **columnSpan**：占用几列
- 对齐方式

```cpp
void QGridLayout::addWidget(QWidget *,int fromRow,int fromColumn,int rowSpan,int columnSpan, Qt::Alignment alignment = Qt::Alignment())
```

我们的GridLayout具有如下的二维的结构，当我们添加控件时需要指定其的具体位置。

上面的案例就是如下的构造，我们直接在addWidget的时候指定即可。

例如在添加图片的时候：

表示左上角坐标**（0，0）**，占地**两行两列**。

```cpp
glayout->addWidget(Icon,0,0,2,2);//(0,0)的位置开始，占据两行两列
```

对于输入框，我们指定它们占地**一行两列**。

有了这个图我们就很容易理解这些位置关系了。

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%207.png)

```cpp
void Widget::testGridLayout()
{
    //图标
    auto Icon = new QLabel(this);
    auto accountEdit = new QLineEdit(this);
    auto btn1 = new QPushButton("注册账号",this);
    auto passwdEdit = new QLineEdit(this);
    auto btn2 = new QPushButton("找回密码",this);
    auto cbx1 = new QCheckBox("记住密码",this);
    auto cbx2 = new QCheckBox("自动登录",this);
    auto loginbtn = new QPushButton("登录",this);

    accountEdit->setPlaceholderText("QQ号码/手机/邮箱");
    passwdEdit->setPlaceholderText("密码");

    Icon->setPixmap(QPixmap(":/C++.jpg").scaled(90,90));  //添加图标
    //创建Grid布局并应用
    auto glayout = new QGridLayout(this);

    //默认是垂直的，需要自己设置相对位置：
    glayout->addWidget(Icon,0,0,2,2);//(0,0)的位置开始，占据两行两列
    glayout->addWidget(accountEdit,0,2,1,2);
    glayout->addWidget(btn1,0,4,1,1);
    glayout->addWidget(passwdEdit,1,2,1,2);
    glayout->addWidget(btn2,1,4,1,1);
    glayout->addWidget(cbx1,2,2,1,1);
    glayout->addWidget(cbx2,2,3,1,1);
    glayout->addWidget(loginbtn,3,2,1,2);

    //设置尺寸限制
    //glayout->setSizeConstraint(QGridLayout::SetFixedSize); //固定大小
    //glayout->setSizeConstraint(QGridLayout::SetMaximumSize); //尺寸: [无穷小,最大值]

}
```

---

## **3，表单布局(FormLayout)**

表单布局可以请轻松的创建**表单结构**。

主要函数和功能：

- **addRow**：添加一行

在addRow中，我们可以指定标签文本（QFormLayout::LabelRole）和控件或者子布局（QFormLayout::FieldRole）

```cpp
void addRow(const QString &labelText, QWidget *field)
void addRow(const QString &labelText, QLayout *field)
```

我们要创建一个登录框，我们**只创建两个编辑框**就行了，然后两个账号和密码的提示标签我们可以用参数一直接指定。

```cpp
void Widget::testQFormLayout()
{
    auto edit1 =new QLineEdit(this);
    auto edit2 =new QLineEdit(this);
    //表单布局
    QFormLayout* flayout = new QFormLayout(this);
    //一行一行的添加
    flayout->addRow("username",edit1); //自动添加标签，标签对应的后面的控件
    flayout->addRow("password",edit2);
}
```

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%208.png)

如果我们想要为某个控件直接设置贯穿一行，我们可以设置`**QFormLayout::SpanningRole`** 角色

其他的角色：

- QFormLayout::LabelRole：只在标签区域
- QFormLayout::FieldRole：只在文本区域
- QFormLayout::SpanningRole：贯穿一整行。

```cpp
flayout->setWidget(2,QFormLayout::SpanningRole,btn);
```

设置换行策略：**setRowWrapPolicy**

- **QFormLayout::DontWrapRows**：字段总是放在它们的标签旁边(默认样式)
- **QFormLayout::WrapLongRows**：标签有足够的空间适应，如果字段对的最小大小大于可用空间，输入框会被换到下一行
- **QFormLayout::WrapAllRows**：字段总是在它们的标签下面。

例如设置WrapAllRows：

```cpp
flayout->setRowWrapPolicy(QFormLayout::RowWrapPolicy::WrapAllRows);
```

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%209.png)

---

## StackedLayout：堆栈布局

QStackedLayout继承自QLayout。

QStackedLayout类提供了**多页面切换的布局**，一次只能看到一个界面。

```cpp
void Widget::testQStackedLayout()
{
    QLabel* lab1 = new QLabel("你好",this);
    QLabel* lab2 = new QLabel("我是",this);
    QLabel* lab3 = new QLabel("大帅哥",this);

    lab1->setStyleSheet("background-color: red");
    lab2->setStyleSheet("background-color: blue");
    lab3->setStyleSheet("background-color: green");

    //堆栈布局
    QStackedLayout* slayout = new QStackedLayout(this);
    slayout->addWidget(lab1);   //0
    slayout->addWidget(lab2);   //1
    slayout->addWidget(lab3);   //2

    //切换界面
    auto cutBtn = new QPushButton("点击切换界面",this);
    connect(cutBtn,&QPushButton::clicked,this,[=](){
        //切换当前显示索引
        slayout->setCurrentIndex((slayout->currentIndex()+1)%slayout->count());
        //提升控件的显示等级到堆栈最顶端
        cutBtn->raise();
    });
}
```

运行如下：

点击切换按钮即可**切换界面**。

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%2010.png)

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%2011.png)

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%2012.png)

---

## QStackedWidget

提供了类似QStackedLayout更方便的组合。

```cpp
void Widget::testQStackedWidget()
{
    QLabel* lab1 = new QLabel("你好",this);
    QLabel* lab2 = new QLabel("我是",this);
    QLabel* lab3 = new QLabel("大帅哥",this);
    lab1->setStyleSheet("background-color: red");
    lab2->setStyleSheet("background-color: blue");
    lab3->setStyleSheet("background-color: green");

    QStackedWidget* sWidget = new QStackedWidget(this);
    sWidget->addWidget(lab1);
    sWidget->addWidget(lab2);
    sWidget->addWidget(lab3);

    QHBoxLayout* box_layout = new QHBoxLayout(this);
    box_layout->addWidget(sWidget);

    auto btn = new QPushButton("点击切换界面");
    connect(btn,&QPushButton::clicked,this,[=](){
        sWidget->setCurrentIndex((sWidget->currentIndex()+1)%sWidget->count());
    });
    btn->show();
}
```

## **QTabWidget**

提供了便捷的分页显示功能，类似于编辑器中打开不同文件：

- **setTabsClosable**：设置可以关闭
- **removeTab**：点击关闭后关闭此Tab

```cpp
void Widget::testQTabWidget()
{
    resize(640,480);
    QTextEdit* text1 = new QTextEdit(this);
    QTextEdit* text2 = new QTextEdit(this);
    QTextEdit* text3 = new QTextEdit(this);
    text1->setStyleSheet("background-color: red");
    text2->setStyleSheet("background-color: blue");
    text3->setStyleSheet("background-color: green");

    QTabWidget* tWidget = new QTabWidget(this);
    tWidget->addTab(text1,"test1.txt");
    tWidget->addTab(text2,"test2.txt");
    tWidget->addTab(text3,"test3.txt");

    tWidget->setTabsClosable(true); //可以关闭
    connect(tWidget,&QTabWidget::tabCloseRequested,this,[=](int index){
        tWidget->removeTab(index);
    });

}
```

效果如下：

在上面点击切换，并且可以关闭。

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%2013.png)

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%2014.png)

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%2015.png)

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%2016.png)

---

# Splitter：分割器

splitter允许用户通过**拖动子部件之间的边界来控制它们的大小**。

 任何数量的小部件都可以由单个拆分器控制。QSplitter的典型用法是创建几个小部件并使用 insertWidget()或addWidget()添加它们。

```cpp
void Widget::testQSplitter()
{
    auto text1 = new QTextEdit(this);
    auto text2 = new QTextEdit(this);

    QSplitter* splitter = new QSplitter(this);
    splitter->addWidget(text1);
    splitter->addWidget(text2);
    //设置为预览模式：false
    splitter->setOpaqueResize(true);
}
```

鼠标放在中间的间隔上我们便可以**左右拖动**他们的距离。

![Untitled](Qt%E5%AD%A6%E4%B9%A012%EF%BC%9A%E5%B8%B8%E7%94%A8Layout%E5%B8%83%E5%B1%80%E6%96%B9%E5%BC%8F%E6%80%BB%E7%BB%93%2025d01615622e4049b047ed97a5de78e3/Untitled%2017.png)