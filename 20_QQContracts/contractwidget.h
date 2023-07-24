#ifndef CONTRACTWIDGET_H
#define CONTRACTWIDGET_H

#include <QWidget>

class ContractInfo;
class ContractWidget:public QWidget
{
public:
    ContractWidget(QWidget* parent =nullptr );
    ContractWidget(ContractInfo *info,QWidget* parent =nullptr);
    ~ContractWidget();
    void init();
private:
    ContractInfo* m_info;
};

#endif // CONTRACTWIDGET_H
