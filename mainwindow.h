#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
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
    int getTime();
    void setTime(int time);

private slots:
    void stop();
    void start();
    void contin();
    void restart();
    void save();
    void load();
    void timeStart();
    void PaintAllElements();
    void paintWithoutApple();
    void createSnake(int i);
    void timeGo();
    void failed();
    void on_action_5_triggered();

private:
    Ui::MainWindow *ui;
    QPushButton *but[7];
    QSpinBox *spi[2];
    int timeCount = 0;
    QTimer *timer;
    void setButtonStatus(int i); //0.未开始 1.游戏 2.暂停 3.终止
    void paintAll();
    void set_items_disabled(QComboBox *com, int a);
    void set_items_abled(QComboBox *com, int a);
};
#endif // MAINWINDOW_H
