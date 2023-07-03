#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDialog>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QLabel>
#include <QColorDialog>
#include <QButtonGroup>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void testQMenu();
    void testMessage();
    void testQFileDialog();
    void testFontDialog();
    void testQColorDialog();
public slots:
    void actionOnDialog();
    void actionOnHalfDialog();
    void actionOnNoDialog();
private:
    QPushButton* button=nullptr;
    //QDialogButtonBox* _dbbox;
    QLabel* lab=nullptr;
};
#endif // WIDGET_H
