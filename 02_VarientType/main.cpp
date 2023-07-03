#include <QCoreApplication>
#include <QDebug>
#include <QPoint>
#include <QVariant>
#include <QLine>
#include <QSize>
#include <QRect>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QElapsedTimer>
#include <QList>
#include <QStringList>
#include <QMap>
#include <QHash>
#include <QtGlobal>
class student{
public:
    student(){}
    student(int num,QString str):num(num),name(str){}
    friend bool operator<(const student& s1,const student& s2){
        return s1.num<s2.num;
    }
    friend bool operator==(const student& s1,const student& s2){
        return s1.num==s2.num;
    }
    friend size_t qHash(const student& s){
        return s.num;
    }
    friend QDebug operator<<(QDebug out,const student& st){
        out<<st.num<<" "<<st.name;
        return out;
    }
private:
    int num;
    QString name;
};

void Output(){

    qint8 age=127;
    quint64 tel=1251515551;
    //输出
    //C风格
    qDebug("age: %d",age); //自动插入空格
    //C++风格
    qDebug()<<"age:"<<age; //不需要换行
    qDebug().nospace()<<"Hello"<<tel;

    qDebug()<<QString("hello ylh");
    //取消引用
    qDebug().noquote()<<QString("hello ylh");

    qInfo()<<"qInfo";
    qWarning()<<"qWarning";
    qCritical()<<"qCritical";
    qFatal("qFatal: file is not exists"); //不能使用流输出

}
void testQByteArray(){
    QByteArray name="ylh";
    qInfo().noquote()<<name;
    name.append(" is");
    name.push_back(" nb");
    name.push_front("hhh ");
    name.prepend("666 ");
    qInfo()<<name;
    name.remove(0,10);
    qInfo()<<name;
    name.chop(1); //尾部删除n个字符
    qInfo()<<name;
    name.truncate(5);

    name="I'm ylh, very nb hhh";
    if (name.contains("very")){
        qInfo()<<"Yes";
    }
    qInfo()<<name.startsWith('I');
    qInfo()<<name.endsWith('h');

    auto pos=name.indexOf("I");
    qInfo()<<pos;
    for (auto& x:name){
        qInfo()<<x;
    }

    QByteArray num;
    num.setNum(1314520,16);
    qInfo()<<num;

    qInfo()<<QByteArray::number(9999);

    QByteArray number="88888";
    qInfo()<<number.toLongLong()<<number.toDouble();
}
void testQString(){
    QString name("yulianghao is a good boy");
    qInfo()<<name;

    name.replace("GOOD","boy",Qt::CaseInsensitive);
    qInfo()<<name;

    QString _name="于良浩";
    qint32 age=18;
    QString job="study";
    qInfo()<<_name+QString::number(age)+job;

    qInfo()<<QString::asprintf("我叫%s,今年%d岁了,我的工作是%s",
        _name.toStdString().data(),age,job.toStdString().data());
    //Qt风格格式化
    qInfo()<<QString("我叫%1,今年%2岁了,我的工作是%3,%1这个名字泰酷辣").arg(_name).arg(age).arg(job);

    //格式化
    auto str=QString("%1天,%2:%3:%4")
                   .arg(15).arg(2,2,10,QChar('0'))
                   .arg(5,2,10,QChar('0')).arg(20);
    qInfo()<<str;

    QString s("于良浩hello");
    //获取本地编码
    qInfo()<<s.toLocal8Bit();
    //获取utf-8编码
    qInfo()<<s.toUtf8();
}
void testQByteArrayAndQString(){
    QByteArray array("hello于");
    qInfo()<<array.size(); //字节个数，一个汉字3个字节
    qInfo()<<array;

    QString string("hello于");
    qInfo()<<string.size(); //字符的个数
    qInfo()<<string;
}
class ylh{
public:
    ylh(){}
    ylh(const QString& s):s(s){}
    friend QDebug operator<<(QDebug out,const ylh& y){
        out<<y.s;
        return out;
    }
private:
    QString s;
};
void testQVariant(){
    //QVariant变体类型
    QVariant q(520);
    qInfo()<<q;

    //获取值
    qInfo()<<q.value<int>();
    q.setValue("hello ylh");
    qInfo()<<q;

    q=QVariant::fromValue(QString("hello ylh"));
    qInfo()<<q;
    qInfo()<<q.typeName();
    qInfo()<<q.metaType().name();

    ylh y("我是于良浩");
    QVariant var;
    var.setValue(y); //通过setValue来设置
    qInfo()<<var; //重载输出

    qInfo()<<var.value<ylh>();
    qInfo()<<QVariant::fromValue(ylh("hhhh"));


    //QVariant的应用+自定义类型
    var.setValue(ylh("我是帅哥"));
    if (var.canConvert<ylh>()){
        auto y=var.value<ylh>();
        qInfo()<<y;
        qInfo()<<"转换成功!";
    }

}
void testQPoint(){
    QPoint pos(2,5);
    qInfo()<<pos;
    qInfo()<<pos.manhattanLength();
    qInfo()<<pos.x()<<pos.y();
    qInfo()<<QPoint(QPoint(1,1)-QPoint(3,3)).manhattanLength();
}
void testQLine(){
    QLine line(1,1,10,10);
    qInfo()<<line;
    line.translate(1,2);
    qInfo()<<line;
    qInfo()<<line.translated(1,2);
}
void testQSize(){
    QSize size(640,480);
    qInfo()<<size;
    qInfo()<<size.transposed();//交换

    QSize sz1(640,480),sz2(960,320);
    qInfo()<<sz1.boundedTo(sz2); //最小包含
    qInfo()<<sz1.expandedTo(sz2); //最大覆盖
    qInfo()<<QSize(480,640).scaled(QSize(10,10),Qt::IgnoreAspectRatio);
    qInfo()<<QSize(480,640).scaled(QSize(10,10),Qt::KeepAspectRatio);
    qInfo()<<QSize(480,640).scaled(QSize(10,10),Qt::KeepAspectRatioByExpanding);
}
void testQRect(){
    QRect rect(0,0,100,100);

    qInfo()<<rect;
    qInfo()<<rect.x()<<rect.y();
    rect.setRect(5,5,50,50);
    qInfo()<<rect;

    //矩形移动
    rect.moveTo(0,0);
    qInfo()<<rect;
    rect.moveCenter(QPoint(0,0));
    qInfo()<<rect;

    //往中间缩小
    qInfo()<<QRect(0,0,100,100).adjusted(5,5,-5,-5);

}
void testQDate(){
    QDate date(2022,10,1);
    qInfo()<<date;
    qInfo()<<date.year();
    date=date.addYears(5);
    qInfo()<<date;

    //格式化字符串
    qInfo()<<date.toString(Qt::DateFormat::ISODate);
    qInfo()<<date.toString(QString("yyyy年MM月dd日"));
    //获取当前时间
    auto cur=QDate::currentDate();
    qInfo()<<cur.toString(QString("yyyy年MM月dd日"));
}
void testQTime(){
    QTime time(5,20,20);
    qInfo()<<time;

    qInfo()<<time.toString(QString("am hh时mm分ss秒"));

    qInfo()<<QTime::currentTime();

    qInfo()<<QTime::fromString("15:05:09");
}
void testQDateTime(){
    QDateTime dt=QDateTime::currentDateTime();
    qInfo()<<dt;

    auto date=dt.date();
    auto time=dt.time();
}
void testQElapsedTimer(){
    //时间计时器
    QElapsedTimer timer;
    timer.start();
    int cnt=0;
    for (int i=1;i<=1e5;i++){
        cnt++;
    }
    qInfo()<<timer.elapsed();
    while (cnt--){}
    qInfo()<<timer.elapsed();
}
void testQList(){
    QList<int> ls{1,2,3,4};;
    //java风格
    QListIterator JIter(ls);
    while (JIter.hasNext()){
        qInfo()<<JIter.next();
    }
    for (auto& x:ls){
        qInfo()<<x;
    }

    QList<QString> names;
    names<<"111"<<"222"<<"333";
    qInfo()<<names;

    names.removeFirst();
    qInfo()<<names;

    qInfo()<<names.indexOf("222");

    QList<qint32> a{1,2,3,4,5,6,7,8};
    qInfo()<<a.at(2);
    a.emplace(1,999); //在指定的位置创建元素
    a.emplaceBack(9);
    a.emplaceFront(0);
    qInfo()<<"是否以9结尾: "<<a.endsWith(9);
    qInfo()<<"是否以0开始: "<<a.startsWith(0);
    qInfo()<<a.first();
    qInfo()<<a.last();
    qInfo()<<a.mid(5); //返回子序列
    qInfo()<<a;
}
void testQStringList(){
    QStringList lstring{"hello","nihao"};
    qInfo()<<lstring;

    qInfo()<<lstring.contains("HeLLo",Qt::CaseSensitivity::CaseInsensitive);

    qInfo()<<lstring.join('+'); //拼接字符串

    //字符串分割
    QString str{"I'm ylh next to meet you"};
    QStringList slist=str.split(" ");
    slist.push_back("ylh");

    //替换字符串对象中所有的目标字符为指定的字符
    slist.replaceInStrings("ylh","ylhhhhh");
    slist.replaceInStrings("e","h");

    qInfo()<<slist;
}
void testQMap(){

    //自定义值类型
    QMap<int,student> stu;
    stu.insert(1,student(18,"ylh"));
    stu.insert(2,student(19,"lyx"));
    stu.insert(3,student(20,"lb"));

    qInfo()<<stu.keys();
    qInfo()<<stu.values();
    qInfo()<<stu.toStdMap(); //转换为std::map
    qInfo()<<stu;

    //自定义键类型: 需要提供operator<规则
    QMap<student,int> stu2;
    stu2.insert(student(18,"ylh"),1);
    stu2.insert(student(16,"lpd"),2);
    stu2.insert(student(20,"cif"),3);

    qInfo()<<stu2;

    //QHash自定义键类型：需要提供operator==和qHash函数
    QHash<student,int> stu3;
    stu2.insert(student(18,"ylh"),1);
    stu2.insert(student(16,"lpd"),2);
    stu2.insert(student(20,"cif"),3);

}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    testQMap();
    return a.exec();
}
