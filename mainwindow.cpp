#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "snakedata.h"
#include <QPixmap>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    paintBackground();
    but[0] = ui->startButton;
    but[1] = ui->stopButton;
    but[2] = ui->continueButton;
    but[3] = ui->restartButton;
    but[4] = ui->exitButton;
    but[5] = ui->saveButton;
    but[6] = ui->loadButton;
    setButtonStatus(0);
    connect(but[0], SIGNAL(clicked()), this, SLOT(start()));
    connect(but[1], SIGNAL(clicked()), this, SLOT(stop()));
    connect(but[2], SIGNAL(clicked()), this, SLOT(contin()));
    connect(but[3], SIGNAL(clicked()), this, SLOT(restart()));
    connect(but[6], SIGNAL(clicked()), this, SLOT(load()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setButtonStatus(int i){
    switch (i) {
    case 0 :
        but[1]->setEnabled(false);
        but[2]->setEnabled(false);
        but[3]->setEnabled(false);
        but[5]->setEnabled(false);
        but[0]->setEnabled(true);
        but[6]->setEnabled(true);
        break;
    case 1 :
        but[0]->setEnabled(false);
        but[1]->setEnabled(true);
        but[2]->setEnabled(false);
        but[3]->setEnabled(false);
        but[5]->setEnabled(false);
        but[6]->setEnabled(false);
        break;
    case 2 :
        but[0]->setEnabled(false);
        but[1]->setEnabled(false);
        but[2]->setEnabled(true);
        but[3]->setEnabled(true);
        but[5]->setEnabled(true);
        but[6]->setEnabled(false);
        break;
    default :
        but[0]->setEnabled(false);
        but[1]->setEnabled(false);
        but[2]->setEnabled(false);
        but[3]->setEnabled(true);
        but[5]->setEnabled(false);
        but[6]->setEnabled(false);
        break;
    }
}

void MainWindow::stop(){
    setButtonStatus(2);
}

void MainWindow::start(){
    setButtonStatus(1);
}

void MainWindow::contin(){
    setButtonStatus(1);
}

void MainWindow::restart(){
    setButtonStatus(0);
}

void MainWindow::load(){
    setButtonStatus(1);
}

void MainWindow::paintBackground(){
    QPixmap pixmap = QPixmap(1001, 1001);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);
    for(int i = 0; i < 40; i ++){
        for(int j = 0; j < 40; j ++){
            painter.drawRect(25 * i, 25 * j, 25 * i + 25, 25 * j + 25);
        }
    }
    QBrush brush;
    brush.setColor(Qt::blue);
    painter.setBrush(brush);
    for(int i = 0; i < 40; i ++){
        for(int j = 0; j < 40; j ++){
            if(ui->label->ob.obs[i][j] == 1)
            painter.drawRect(25 * i, 25 * j, 25 * i + 25, 25 * j + 25);
        }
    }
    ui->label->setPixmap(pixmap);
}


