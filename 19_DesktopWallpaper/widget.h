#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>   //1. 设置模型
#include "rolemodel.h" //2. 切换模型
#include <QMap>
#include <QString>
#include <QPushButton> //3. 显示按钮
#include "settings.h"
#include "fullwindow.h" //全屏

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void init();
    void loadModelResource();
    void setSystemTray();
public slots:
    void updateModel();
protected:
    void resizeEvent(QResizeEvent* ev)override;
    void mousePressEvent(QMouseEvent* ev)override;
    void contextMenuEvent(QContextMenuEvent* ev)override;
private:
    QLabel* m_roleModelLab;

    int m_index=0;
    int m_frames=6;
    QMap<QString,RoleModel> m_roles;

    Settings* m_windowSettings=nullptr;

    QString currentPicture;

    //*----*
    FullWindow* m_wallpaper =nullptr;

    //右键菜单
    QMenu* m_contextMenu=nullptr;
};

#endif // WIDGET_H
