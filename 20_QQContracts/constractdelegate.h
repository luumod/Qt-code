#ifndef CONSTRACTDELEGATE_H
#define CONSTRACTDELEGATE_H

#include <QWidget>
#include <QStyledItemDelegate>

class ConstractDelegate: public QStyledItemDelegate
{
public:
    ConstractDelegate(QObject* parent = nullptr);
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // CONSTRACTDELEGATE_H
