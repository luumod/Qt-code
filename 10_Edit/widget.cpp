#include "widget.h"
#include <QLineEdit>
#include <QDebug>
#include <QPushButton>
#include <QCompleter>
#include <QTextCursor>
#include <QMenu>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(640,480);

    init();
    testTextEdit();
}

Widget::~Widget()
{
}

void Widget::init()
{
    auto btn=new QPushButton("get",this);
    btn->move(200,0);
    connect(btn,&QPushButton::clicked,this,&Widget::onClicked);
}

void Widget::testLineEdit()
{
    edit=new QLineEdit(this);

    //设置文本
    //edit->setText("设置文本");

    //设置显示模式
    edit->setEchoMode(QLineEdit::EchoMode::Normal);

    //设置占位提示文本
    edit->setPlaceholderText("请输入信息");

    //设置清空按钮
    edit->setClearButtonEnabled(true);

    //设置自动补全
    QStringList hints;
    hints<<"123456"<<"你好"<<"于良浩"<<"ylhhhhh";
    auto comp =new QCompleter(hints,this);
    edit->setCompleter(comp);

    //设置输入掩码
    //edit->setInputMask("NN:NN:NN:NN");

    //允许拖拽
    edit->setDragEnabled(true);
}

void Widget::testTextEdit()
{
    tedit=new QTextEdit(this);

    //普通文本的插入
    tedit->setPlainText("普通文本");

    //HTML文本
    tedit->setHtml("<h1>一级标题</h1>");

    //markdown文本
    tedit->setMarkdown("# 一级标题\n## 二级标题\n### 三级标题");

    tedit->setText("自动识别");

    QTextCursor cs=tedit->textCursor();
    QTextCharFormat format;
    format.setFontUnderline(true);
    format.setUnderlineColor(Qt::green);
    format.setForeground(Qt::blue);
    cs.insertText("插入内容",format);

}

void Widget::onClicked()
{
    //edit->insert("插入");
    //text: 实际文本
    //displayText: 看到的是什么就是什么
    //qInfo()<<edit->text()<<edit->displayText();
    //qInfo()<<edit->isModified();
    //edit->setModified(false);
    //edit->cursorBackward(false,1);

    //每次移动一个单词长度
    //edit->cursorWordBackward(true);
    //edit->setTextMargins(10,0,0,0);

    //普通文本
    //tedit->insertPlainText("edit");
    //qInfo()<<tedit->toPlainText();

    //HTML
    //tedit->insertHtml("<h2>二级标题</h2>");
    //qInfo()<<tedit->toHtml();

    //qInfo()<<tedit->toMarkdown();


}

