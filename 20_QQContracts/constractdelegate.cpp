#include "contractdelegate.h"
#include "contractinfo.h"
#include <QPainter>

ConstractDelegate::ConstractDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

void ConstractDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto infos = index.data(Qt::ItemDataRole::UserRole + 1).value<ContractInfo*>();
    if (!infos){
        return;
    }
    //绘制头像
    painter->drawPixmap(0,0,infos->m_picture);
}
