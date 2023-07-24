#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QButtonGroup>


QT_BEGIN_NAMESPACE
namespace Ui {
class TopWidget;
}
QT_END_NAMESPACE

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();
    void addButtonsToButtonGroup();
Q_SIGNALS:
    void ChangeModel(const QString& form);
    void ChangeWallpeper(const QString& wallpaper);
public Q_SLOTS:
    void on_set_clicked();
    void on_model1_clicked();
    void on_model2_clicked();
    void on_model3_clicked();
    void on_buttonClose_clicked();

private slots:
    void on_buttonChoice_clicked();

private:
    Ui::TopWidget *ui;

    bool uniformGril;

    QButtonGroup* m_buttonGroup;

    QButtonGroup* m_radioGroup;


};

#endif // SETTINGS_H
