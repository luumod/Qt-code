#include "widget.h"
#include <QListView>
#include <QStandardItemModel>
#include <QStandardItem>

#include <QApplication>


enum NAME: int{one ,two, three, four};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ///创建一个视图
    QListView view;
    //无法修改
    view.setEditTriggers(QAbstractItemView::NoEditTriggers);
    view.show();

    //创建一个模型
    QStandardItemModel* itemModel = new QStandardItemModel(&view);

    //视图中添加模型
    view.setModel(itemModel);

    //模型添加数据
    itemModel->appendRow(new QStandardItem("蔡徐坤"));
    itemModel->appendRow(new QStandardItem(view.style()->standardPixmap(QStyle::StandardPixmap::SP_FileIcon),"陈立农"));

    //获取项目
    qInfo()<<itemModel->item(1)->text();
    //检查有效性
    auto item = itemModel->itemFromIndex(itemModel->index(2,0));
    if (item){
        qInfo()<<item->text();
    }
    qInfo()<<itemModel->itemFromIndex(itemModel->index(0,0))->text();


    //设置角色数据
    itemModel->appendRow(new QStandardItem("范丞丞"));
    itemModel->setData(itemModel->index(2,0),"修改后的范丞丞",Qt::ItemDataRole::EditRole);
    itemModel->setData(itemModel->index(2,0),QColor(255,0,0),Qt::ItemDataRole::DecorationRole);

    itemModel->appendRow(new QStandardItem("王琳凯"));
    itemModel->setData(itemModel->index(3,0),QPixmap(":/dog.png").scaled(32,32),Qt::ItemDataRole::DecorationRole);

    //获取数据
    qInfo()<<itemModel->data(itemModel->index(3,0));

    //对Item直接设置数据
    QStandardItem* sItem = new QStandardItem("玛卡巴卡");
    sItem->setData(QColor(0,255,255),Qt::ItemDataRole::DecorationRole);
    itemModel->appendRow(sItem);


    //点击后获取其数据
    QObject::connect(&view,&QListView::clicked,[=](const QModelIndex& index){
        qInfo()<<index.data();
        qInfo()<<index.data(Qt::ItemDataRole::UserRole+1).toInt();
    });

    //自定义角色数据
    itemModel->item(0)->setData(NAME::one,Qt::ItemDataRole::UserRole+1);
    itemModel->item(1)->setData(NAME::two,Qt::ItemDataRole::UserRole+1);
    itemModel->item(2)->setData(NAME::three,Qt::ItemDataRole::UserRole+1);
    itemModel->item(3)->setData(NAME::four,Qt::ItemDataRole::UserRole+1);

    return a.exec();
}
