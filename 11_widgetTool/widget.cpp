#include "widget.h"

class SpinBox :public QSpinBox{
public:
    SpinBox(QWidget* parent=nullptr)
        :QSpinBox(parent){
        strs<<"NULL"<<"一"<<"二"<<"三"<<"四"<<"五"<<"六"<<"日";
    }
    QString textFromValue(int value)const override{

        return strs[value];
    }
private:
    QStringList strs;
};

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    QTimer* dateTimer=new QTimer(this);
    dateTimer->callOnTimeout(this,&Widget::timeGoOn);
    dateTimer->start(100);


    resize(640,480);
    init();
    testQRubberBand();
}

Widget::~Widget()
{
}

void Widget::init()
{

}

void Widget::testQKeySequenceEdit()
{
    auto btn=new QPushButton(this);
    btn->move(200,0);
    connect(btn,&QPushButton::clicked,this,&Widget::onClicked);

    key = new QKeySequenceEdit(this);

    //相对于Widget窗口来说的快捷键设置
    QShortcut* st=new QShortcut(this);
    st->setKey(QKeySequence("Ctrl+Shift+A"));
    connect(st,&QShortcut::activated,this,&Widget::activated_Ctrl_Shift_A);

    new QShortcut(QKeySequence::StandardKey::SelectAll,this,[](){
        qInfo()<<"SelectAll 被激活";
    });
}

void Widget::testQSpinBox()
{
    sp=new SpinBox(this);
    sp->setRange(1,7);

    //设置值
    sp->setValue(5);

    //循环
    sp->setWrapping(true);

    //步长
    sp->setSingleStep(1);

    //前缀后缀
    sp->setPrefix("周");
    sp->setSuffix("上学");

    //特殊显示最小值
    sp->setSpecialValueText("最底部!");

    //显示方式：直接看到，干净的
    qInfo()<<sp->text()<<sp->cleanText();
}

void Widget::testQDateTimeEdit()
{
    dt=new QDateTimeEdit(this);

    //设置当前时间
    dt->setDateTime(QDateTime::currentDateTime());

    //设置显示格式
    dt->setDisplayFormat("yyyy年MM月dd日-hh时mm分ss秒");

    //获取某段数值
    qInfo()<<dt->sectionCount()<<dt->sectionAt(2)<<dt->sectionText(dt->sectionAt(2));

    //日历弹出
    dt->setCalendarPopup(true);
}

void Widget::testQComboBox()
{
    cbx=new QComboBox(this);
    //currentData

    QStringList datas{"北京","成都","济南","西安","沈阳","杭州","南京"};
    QStringList itemDatas{"北京市","四川省","山东省","陕西省","辽宁省","浙江省","江苏省"};
    cbx->addItems(datas);
    for (int i=0;i<datas.count();i++){
        cbx->setItemData(i,itemDatas[i]);
    }
    connect(cbx,&QComboBox::currentIndexChanged,this,[=](int index){
        qInfo()<<"当前选择: "<<cbx->currentText()<<cbx->currentData().toString();
    });

    //可以编辑插入
    cbx->setEditable(true);

    //可以重复
    //cbx->setDuplicatesEnabled(true);

    //根据内容调整尺寸
    cbx->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);


    return;
    cbx->addItem("唱跳");
    cbx->addItem("RAP");
    cbx->addItem("篮球");
    cbx->addItem(style()->standardIcon(QStyle::StandardPixmap::SP_DirHomeIcon),"吃鸡");
    cbx->insertSeparator(4);
    cbx->addItems(QStringList{"蔡徐坤","陈立农","范丞丞"});
}

void Widget::testQSlider()
{
    //Qt::Orientation::Horizontal
    sld=new QSlider(this);
    sld->setGeometry(100,100,20,100);

    sld->setRange(0,100);
    //手动设置值
    //sld->setValue(50);

    connect(sld,&QSlider::valueChanged,this,[=](int value){
        qInfo()<<value;
    });

    auto sbar=new QScrollBar(this);
    sbar->resize(20,100);

    auto dial=new QDial(this);
    dial->setGeometry(200,200,50,50);
}

void Widget::testQRubberBand()
{
    rband=new QRubberBand(QRubberBand::Shape::Line,this);

    //选中按钮
    for (int i=0;i<5;i++){
        for (int j=0;j<5;j++){
            auto chx=new QCheckBox(QString::number(i*5+j),this);
            chx->move(i*50,j*50);
        }
    }
}

void Widget::onClicked()
{
    qInfo()<<key->keySequence();
}

void Widget::activated_Ctrl_Shift_A()
{
    qInfo()<<"Ctrl_Shift_A 被激活";
}

void Widget::timeGoOn()
{
    //时间流逝
    //dt->setDateTime(QDateTime::currentDateTime());

    //滑块移动
    //sld->setValue(sld->value()+1);
}

void Widget::mousePressEvent(QMouseEvent *ev)
{
    //橡皮条拖动
    origin=ev->pos(); //保存开始的位置
    rband->setGeometry(QRect(origin,QSize()));
    rband->show();
}

void Widget::mouseMoveEvent(QMouseEvent *ev)
{
    rband->setGeometry(QRect(origin,ev->pos()).normalized());
}

void Widget::mouseReleaseEvent(QMouseEvent *ev)
{
    rband->hide();
    qInfo()<<rband->geometry();


    //处理批量点击按钮
    auto lists=this->children();
    for (auto& x:lists){
        auto chx=dynamic_cast<QCheckBox*>(x);
        if (chx && rband->geometry().contains(chx->geometry())){
            chx->setChecked(!chx->isChecked());
        }
    }
}

