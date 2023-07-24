#ifndef CONTRACTSLISTVIEW_H
#define CONTRACTSLISTVIEW_H

#include <QWidget>
#include <QListView>
#include <QStandardItemModel>
#include <QList>

class ContractInfo;
class ContractsListView : public QListView
{
    Q_OBJECT
public:
    ContractsListView(QWidget* parent=nullptr);
    ~ContractsListView();
    void init();
public slots:
    void onDoubleClicked(const QModelIndex& idx);
private:
    QStandardItemModel* m_itemModel=nullptr;// 模型

    QList<ContractInfo*> m_infos;
};

#endif // CONTRACTSLISTVIEW_H
