#include "contractdelegate.h"
#include "contractinfo.h"
#include <QPainter>
#include <QLabel>

ContractDelegate::ContractDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

void ContractDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //放置
    if (option.state.testFlag(QStyle::StateFlag::State_MouseOver)){
        painter->fillRect(option.rect,QColor(239,237,243));
    }
    //点击
    if (option.state.testFlag(QStyle::StateFlag::State_Selected)){
        painter->fillRect(option.rect,QColor(233,231,237));
    }

    //交给父亲来处理其他：背景颜色，选中颜色
    //QStyledItemDelegate::paint(painter,option,index);

    auto infos = index.data(Qt::ItemDataRole::UserRole + 1).value<ContractInfo*>();
    if (!infos){
        return;
    }
    //绘制头像
    QRect dstRect = QRect{option.rect.x(),option.rect.y() + (option.rect.height()-42)/2,42,42};
    painter->drawPixmap(dstRect,infos->m_picture);

    int spacing = 8;

    //绘制名字
    int nameHeight = painter->fontMetrics().height();
    QPoint namePos(dstRect.right() + spacing,dstRect.y() + nameHeight);
    painter->drawText(namePos,infos->m_name);

    //绘制vip标志
    int nameWidth = painter->fontMetrics().horizontalAdvance(infos->m_name);
    QPixmap pix;
    if (infos->m_type == ContractInfo::no){
    }
    else if (infos->m_type == ContractInfo::vip){
        pix.load(":/assets/images/vip.png");
    }
    else if (infos->m_type == ContractInfo::svip){
        pix.load(":/assets/images/svip.png");
    }
    painter->drawPixmap(namePos.x() + nameWidth + 3,namePos.y() - 10,pix);

    //绘制签名

    painter->drawText(namePos.x(),namePos.y() + nameHeight + 5,infos->m_signature);

}

QSize ContractDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //调整高度
    return QSize(option.rect.width(),60);
}
