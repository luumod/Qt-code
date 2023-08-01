

#include "diagramtextitem.h"
#include "diagramscene.h"

//! [0]
DiagramTextItem::DiagramTextItem(QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}
//! [0]

//! [1]
QVariant DiagramTextItem::itemChange(GraphicsItemChange change,
                                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
        //发送项目选择改变信号： DiagramTextItem
        emit selectedChange(this);
    return value;
}
//! [1]

//! [2]
void DiagramTextItem::focusOutEvent(QFocusEvent *event)
{
    //结束编辑Text
    //qInfo()<<"focusOutEvent";
    setTextInteractionFlags(Qt::NoTextInteraction);
    //结束编辑文字时发送信号
    emit lostFocus(this);
    QGraphicsTextItem::focusOutEvent(event);
}
//! [2]

//! [5]
void DiagramTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (textInteractionFlags() == Qt::NoTextInteraction)
        setTextInteractionFlags(Qt::TextEditorInteraction);
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}
//! [5]
