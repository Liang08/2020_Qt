#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "snakedata.h"
#include "obstacle.h"
#include "snakelabel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void stop();
    void start();
    void contin();
    void restart();
    void load();
    void obstaclePaint();

private:
    Ui::MainWindow *ui;
    QPushButton *but[7];
    void setButtonStatus(int i); //0.未开始 1.游戏 2.暂停 3.终止
    void paintBackground();
};
#endif // MAINWINDOW_H
