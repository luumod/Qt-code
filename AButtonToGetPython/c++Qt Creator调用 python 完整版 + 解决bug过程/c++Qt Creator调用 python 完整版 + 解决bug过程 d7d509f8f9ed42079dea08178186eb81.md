# c++Qt Creator调用 python 完整版 + 解决bug过程

category: 后端开发
date: 2023/06/18
status: Published
summary: 在Qt中实现对 Python模块的调用，以提高效率，这篇文章给出了全过程，一步一步来绝不会出现错误！
tags: Python, Qt
type: Post

**文章首发于我的个人博客：[欢迎大佬们来逛逛](https://www.helloylh.com/)**

# 创建项目

选择创建 `qmake` 项目：

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled.png)

选择创建 `MSVC 64bit` 版本：

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%201.png)

首先我们先创建一个普通的`python文件`：

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%202.png)

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%203.png)

<aside>
💡 注意文件名不要是 `[test.py](http://test.py)` ，因为python中存在一个此文件，会产生冲突

</aside>

输入以下内容用于测试python及**常用库的导入**

```cpp
import numpy as np
import pandas as pd

def hello():
    print("hello")
```

---

# 配置python环境

选择`**工具 - 外部 - 配置**`  

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%204.png)

选择`**外部工具**` 点击`**添加**`：**添加工具**

 

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%205.png)

我们需要依次设置这**三个参数**：

1. 执行档：你的`python.exe`的路径，我使用的是`anaconda3`的python，因此我的路径是：**F:\Tools\Ana\python.exe**
2. 参数：直接复制粘贴：`%{CurrentDocument:FilePath}`
3. 工作目录：直接复制粘贴：`%{CurrentDocument:Path}`

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%206.png)

输入完成后，点击`应用` 然后`确定`

可以给你的环境改个名字：我的是 `python3.10`版本.

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%207.png)

切换到你的python文件中，测试是否正确：

选择**`工具 -  外部 - python310`**

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%208.png)

运行如下：说明配置python环境成功，也就是说你以后写的python代码就可以在这个地方直接运行了。

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%209.png)

---

# 导入CPython包

我们想要真正的在Qt中调用Python，就必须要一个头文件：**`<Python.h>`**

这里面包含了很多Python与C互通的接口。

但是如果我们直接输入：**`#include <Python.h>`** 会报错，根本就找不到！！

我们需要导入。

检查以下我们刚才配置环境时，与**`Python.exe` 同级**目录下的 **`include`** 文件夹下有没有 **`Python.h`**文件，如果有就说明可以实现。

> **如果没有这个文件，你最好重新选择一个Python.exe，重新实现配置Python环境这一节，因为即使你配置好了环境，但是因为没有这个头文件也无法使用。**
> 

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2010.png)

如果有，则我们开始导入：

**右键项目名称**：选择**`添加库`**。

选择添加**外部库**：

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2011.png)

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2012.png)

注意这个地方**非常重要！！！**

我们要填写两个参数：

1. 库文件：就是你的 `**libs`** 文件夹位置的`python310.lib`，我的位于：**F:\Tools\Ana\libs\python310.lib**
2. 包含路径：就是刚才介绍的include的文件夹位置，我的位于：**F:\Tools\Ana\include**
3. **注意其他的地方选择要和我的一样。**

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2013.png)

点击下一步，完成，接着你就会跳转到 **`.pro`** 文件中：

**并且添加了如下的内容**。

其中就包含了我们所需要的 libs 和 include 等配置信息，我们直接保存即可。

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2014.png)

# 其他坑点

## Python.h 头文件报错

到这时我们就已经配置完成了，我们现在可以使用 **`Python.h`** 了，但是你会发现报一个错误，这是因为Qt的slots 和 python.h这个文件中的这个变量冲突了。

我们执行以下操作：

找到 **`object.h`** 文件：

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2015.png)

并且在这个位置修改如下：即添加一个 #undef 和#define 即可。

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2016.png)

使用**管理员模式保存**，这个错误就解决了。

---

## ModuleNotFoundError: No module named 'encodings’ 完美解决

之后我们可以测试以下，输入以下代码：

获取Python文件中的这个函数模块，然后再调用：

```cpp
#include <QCoreApplication>
#include <Python.h>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

		//初始化
    Py_Initialize();

    PyObject* module=PyImport_ImportModule("testPython");
    if (!module){
        qInfo()<<"Python file cant open!";
        return -1;
    }
    PyObject* pFunc=PyObject_GetAttrString(module,"hello");
    if (!pFunc){
        qInfo()<<"the Python function cant load!";
        return -1;
    }
		//调用函数
    PyObject_CallFunction(pFunc,NULL);

    Py_Finalize();
    return a.exec();
}
```

但是，之后你就会发现一个惊人的错误：

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2017.png)

这是怎么回事，但是我在 anaconda3 中的Python中运行（因为我使用就是这个python）是存在这个模块的：

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2018.png)

这并不是你的问题，解决如下：

> **PYTHONHOME 环境变量是用于指定Python 安装路径的，而 PYTHONPATH 环境变量是用于指定Python 模块搜索路径的**
> 
1. 首先我们需要规定python的**`home`** ，即使用这样一个函数：注意这里的python安装路径是这样的：**F:\Tools\Ana**

```cpp
//添加搜索python安装路径
Py_SetPythonHome(L"F:\\Tools\\Ana");
```

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2019.png)

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2020.png)

之后我们就解决了！！！但是这样做是不兼容的，因为我们如果要将项目打包发给别人，**别人可没有这个路径！！！**因此这个路径只能有你自己拥有，**换句话说如果我们不写这一条语句就好了！！！改用环境变量！！**

1. 添加**系统环境变量**：**PYTHONHOME=F:\\Tools\\Ana**

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2021.png)

之后你把上面这条语句**直接删除**即可，注意：添加环境变量可能需要重启电脑生效，请耐心等待！

看到了吗，我们已经删除了并且**不会出现这个报错了**！

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2022.png)

## 找不到python文件

但是我们又出现了一个新的错误，即加载python时找不到这个文件，注意我的 **`testPython`** 是python文件名，**不要加 .py后缀**。

这个问题是由于你的  **qt生成的 .exe 程序找不到这个python文件**，把他们放到同一目录下即可：

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2023.png)

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2024.png)

如何找到这个路径不用我多说了吧！！

---

# 成功！

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2025.png)

![Untitled](c++Qt%20Creator%E8%B0%83%E7%94%A8%20python%20%E5%AE%8C%E6%95%B4%E7%89%88%20+%20%E8%A7%A3%E5%86%B3bug%E8%BF%87%E7%A8%8B%20d7d509f8f9ed42079dea08178186eb81/Untitled%2026.png)

---

参考链接：

[Qt C++ Python 混合编程测试文档](https://zhuanlan.zhihu.com/p/612714596)

[Qt Creator中调用Python的常见问题_python path configuration: pythonhome = (not set) _妥善的博客-CSDN博客](https://blog.csdn.net/yi_777/article/details/112102757)

[解决QT C++调用python显示错误ModuleNotFoundError: No module named ‘encodings‘)及打包发布问题_modulenotfounderror: no module named 'encodings_代码行者的博客-CSDN博客](https://blog.csdn.net/qq_29766669/article/details/113386992?spm=1001.2101.3001.6650.11&utm_medium=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~Rate-11-113386992-blog-129957875.235^v38^pc_relevant_sort_base1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~Rate-11-113386992-blog-129957875.235^v38^pc_relevant_sort_base1&utm_relevant_index=12)

[Qtcreator中C++调用python方法_:-1: error: lnk1146: 没有用选项“/libpath:”指定的参数_alxe_made的博客-CSDN博客](https://blog.csdn.net/alxe_made/article/details/83382159)

[python嵌入错误‘No module named site’的解决方案_no module named site pythonpath_游蓝海的博客-CSDN博客](https://blog.csdn.net/you_lan_hai/article/details/8592697)