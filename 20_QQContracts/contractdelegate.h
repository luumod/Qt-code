#ifndef CONSTRACTDELEGATE_H
#define CONSTRACTDELEGATE_H

#include <QWidget>
#include <QStyledItemDelegate>

class ContractDelegate: public QStyledItemDelegate
{
public:
    ContractDelegate(QObject* parent = nullptr);
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // CONSTRACTDELEGATE_H
