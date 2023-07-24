#include "contractslistview.h"
#include "contractinfo.h"
#include "contractwidget.h"
#include "contractdelegate.h"

#define TYPE 0


ContractsListView::ContractsListView(QWidget* parent)
    :QListView(parent),
    m_itemModel(new QStandardItemModel(this))
{
    this->setModel(m_itemModel);
    this->setEditTriggers(QListView::NoEditTriggers);

#if TYPE
    this->setItemDelegate(new ContractDelegate(this));  //设置代理
#endif

    init();

    this->show();
}

ContractsListView::~ContractsListView()
{

}

void ContractsListView::init()
{
    m_infos.push_back(new ContractInfo("蔡徐坤"));
    m_infos.push_back(new ContractInfo("辞念","成功不是凭希望和梦想，而是凭努力和实践"));
    m_infos.push_back(new ContractInfo("代墨","艰难方显勇毅，磨难使得玉成"));
    m_infos.push_back(new ContractInfo("范丞丞"));


    m_itemModel->setHorizontalHeaderItem(0,new QStandardItem("头像"));
    m_itemModel->setHorizontalHeaderItem(1,new QStandardItem("信息"));
    //往模型内添加数据
    for (auto& px:m_infos){
#if TYPE
        auto item = new QStandardItem;
        item->setData(QVariant::fromValue(px));
        m_itemModel->appendRow(item);
#else
        auto item = new QStandardItem;
        item->setData(QVariant::fromValue(px));
        //设置每个项目的高度 !!!
        m_itemModel->appendRow(item);
        this->setIndexWidget(item->index(),new ContractWidget(px));
        item->setSizeHint(QSize(width(),60));

#endif
    }

    connect(this,&QListView::doubleClicked,this,&ContractsListView::onDoubleClicked);
}

void ContractsListView::onDoubleClicked(const QModelIndex& idx)
{
    auto info = idx.data(Qt::ItemDataRole::UserRole+1).value<ContractInfo*>();
    if (info){
        qInfo()<<*info;
    }
}
