#include "aboutwindow.h"
#include <QDebug>
#include <QTextEdit>

aboutWindow::aboutWindow(QWidget *parent)
    :QWidget(parent)
{
    resize(480,320);
    QTextEdit* edit =new QTextEdit(this);
    edit->setMarkdown("# 使用方法： \\n 1. 拖拽一个需要加载所需库的exe文件 \\n "
                      " 2. 点击生成，会在原exe路径下自动加载所需要的库文件 \\n"
                      " 3. 点击测试来检查是否加载成功");

    edit->setMarkdown("# 一级标题\\n - 选项一\\n - 选项二");
}

aboutWindow::~aboutWindow()
{
    qInfo()<<"about释放";
}
