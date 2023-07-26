#ifndef INPUTINFO_H
#define INPUTINFO_H

#include <QWidget>
namespace Ui {
class InputInfo;
}
class InputInfo : public QWidget
{
    Q_OBJECT

public:
    explicit InputInfo(QWidget *parent = nullptr);
    ~InputInfo();
    void input();
    int colCount()const;
    int rowCount()const;
signals:
    void finished();
private:
    Ui::InputInfo *ui;

    int row;
    int col;
};

#endif // INPUTINFO_H
