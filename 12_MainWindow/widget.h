#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QDockWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();
    void testMenuBar();
    void testToolBar();
    void testStatusBar();
    void testDockWidget();
    void SystemTrayIcon();
public:
    auto createDockWidget(const QString& title)->QDockWidget*{
        auto DockWidget=new QDockWidget(title,this);
        return DockWidget;
    }
public slots:
    void on_Ctrl_O();
    void on_Ctrl_S();
    void on_Alt_E();
};
#endif // WIDGET_H
