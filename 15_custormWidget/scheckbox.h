#ifndef SCHECKBOX_H
#define SCHECKBOX_H

#include <QWidget>

namespace Ui {
class SCheckBox;
}

class SCheckBox : public QWidget
{
    Q_OBJECT

public:
    explicit SCheckBox(QWidget *parent = nullptr);
    ~SCheckBox();
protected:
    void mousePressEvent(QMouseEvent* ev)override;
private:
    Ui::SCheckBox *ui;
    bool cut = false;
};

#endif // SCHECKBOX_H
