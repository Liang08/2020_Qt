#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "snakedata.h"
#include <QPixmap>
#include <QDebug>
#include <QPainter>
#include <QSpinBox>
#include <QComboBox>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("贪吃蛇");
    paintWithoutApple();

    but[0] = ui->startButton;
    but[1] = ui->stopButton;
    but[2] = ui->continueButton;
    but[3] = ui->restartButton;
    but[4] = ui->exitButton;
    but[5] = ui->saveButton;
    but[6] = ui->loadButton;

    ui->spinBox->setRange(0, 39);
    ui->spinBox_2->setRange(0, 39);
    spi[0] = ui->spinBox;
    spi[1] = ui->spinBox_2;

    timer = new QTimer(this);

    //设置焦点
    for(int i = 0; i < 6; i ++){
        but[i]->setFocusPolicy(Qt::NoFocus);
    }
    for(int i = 0; i < 2; i ++){
        spi[i]->setFocusPolicy(Qt::NoFocus);
    }
    ui->comboBox->setFocusPolicy(Qt::NoFocus);

    set_items_disabled(ui->comboBox, 0);
    set_items_disabled(ui->comboBox, 2);
    set_items_abled(ui->comboBox, 1);
    set_items_abled(ui->comboBox, 3);

    setButtonStatus(0);

    //signals and slots
    connect(but[0], SIGNAL(clicked()), this, SLOT(start()));
    connect(but[1], SIGNAL(clicked()), this, SLOT(stop()));
    connect(but[2], SIGNAL(clicked()), this, SLOT(contin()));
    connect(but[3], SIGNAL(clicked()), this, SLOT(restart()));
    connect(but[5], SIGNAL(clicked()), this, SLOT(save()));
    connect(but[6], SIGNAL(clicked()), this, SLOT(load()));
    connect(ui->action, SIGNAL(triggered()), this, SLOT(start()));
    connect(ui->action_2, SIGNAL(triggered()), this, SLOT(stop()));
    connect(ui->action_3, SIGNAL(triggered()), this, SLOT(contin()));
    connect(ui->action_4, SIGNAL(triggered()), this, SLOT(restart()));
    connect(ui->action_7, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->action_8, SIGNAL(triggered()), this, SLOT(load()));
    connect(ui->label, SIGNAL(freshen()), this, SLOT(PaintAllElements()));
    connect(ui->label, SIGNAL(freshen_0()), this, SLOT(paintWithoutApple()));
    connect(ui->label, SIGNAL(wrong()), this, SLOT(failed()));
    connect(ui->label, SIGNAL(startTime()), this, SLOT(timeStart()));
    for(int i = 0; i < 2; i ++)
        connect(spi[i], SIGNAL(valueChanged(int)), this, SLOT(createSnake(int)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(createSnake(int)));
    connect(timer, SIGNAL(timeout()), this, SLOT(timeGo()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setButtonStatus(int i){
    switch (i) {
    case 0 :
        but[0]->setEnabled(true);
        ui->action->setEnabled(true);
        but[1]->setEnabled(false);
        ui->action_2->setEnabled(false);
        but[2]->setEnabled(false);
        ui->action_3->setEnabled(false);
        but[3]->setEnabled(false);
        ui->action_4->setEnabled(false);
        but[5]->setEnabled(false);
        ui->action_7->setEnabled(false);
        but[6]->setEnabled(true);
        ui->action_8->setEnabled(true);
        ui->label->setAttribute(Qt::WA_TransparentForMouseEvents, false);
        ui->widget_4->setEnabled(true);
        ui->label->status = 0;
        break;
    case 1 :
        but[0]->setEnabled(false);
        ui->action->setEnabled(false);
        but[1]->setEnabled(true);
        ui->action_2->setEnabled(true);
        but[2]->setEnabled(false);
        ui->action_3->setEnabled(false);
        but[3]->setEnabled(false);
        ui->action_4->setEnabled(false);
        but[5]->setEnabled(false);
        ui->action_7->setEnabled(false);
        but[6]->setEnabled(false);
        ui->action_8->setEnabled(false);
        ui->label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        ui->widget_4->setEnabled(false);
        ui->label->status = 1;
        break;
    case 2 :
        but[0]->setEnabled(false);
        ui->action->setEnabled(false);
        but[1]->setEnabled(false);
        ui->action_2->setEnabled(false);
        but[2]->setEnabled(true);
        ui->action_3->setEnabled(true);
        but[3]->setEnabled(true);
        ui->action_4->setEnabled(true);
        but[5]->setEnabled(true);
        ui->action_7->setEnabled(true);
        but[6]->setEnabled(false);
        ui->action_8->setEnabled(false);
        ui->label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        ui->widget_4->setEnabled(false);
        ui->label->status = 2;
        break;
    default :
        but[0]->setEnabled(false);
        ui->action->setEnabled(false);
        but[1]->setEnabled(false);
        ui->action_2->setEnabled(false);
        but[2]->setEnabled(false);
        ui->action_3->setEnabled(false);
        but[3]->setEnabled(true);
        ui->action_4->setEnabled(true);
        but[5]->setEnabled(false);
        ui->action_7->setEnabled(false);
        but[6]->setEnabled(false);
        ui->action_8->setEnabled(false);
        ui->label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        ui->widget_4->setEnabled(false);
        ui->label->status = 3;
        break;
    }
}


//slots
void MainWindow::stop(){
    setButtonStatus(2);
    timer->stop();
}


void MainWindow::start(){
    setButtonStatus(1);
    ui->label->createApple();
}


void MainWindow::contin(){
    setButtonStatus(1);
    timer->start(150);
}


void MainWindow::restart(){
    setButtonStatus(0);
    timeCount = 0;
    ui->timeLabel->setText(QString::number(timeCount));
    ui->label->snake_0.data.clear();
    ui->label->snake_0.snakeInit();
    memset(ui->label->ob.obs, 0, sizeof (ui->label->ob.obs));
    paintWithoutApple();
}


void MainWindow::save(){
    QString path = QFileDialog::getSaveFileName(this,
                   tr("Open File"), ".", tr("Text Files(*.txt)"));
    if(!path.isEmpty()){
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"),
                                 tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << "Snake\n";
        out << ui->label->snake_0.getDirection() << "\n";
        out << ui->label->snake_0.data.size() << "\n";
        for (int i = 0; i < ui->label->snake_0.data.size(); i ++) {
            out << ui->label->snake_0.data[i].x << "\n";
            out << ui->label->snake_0.data[i].y << "\n";
        }
        out << "Obstacle\n";
        int n = 0;
        for (int i = 0; i < 40; i ++) {
            for (int j = 0; j < 40; j ++) {
                if(ui->label->ob.obs[i][j] == 1)
                    n += 1;
            }
        }
        out << n << "\n";
        for (int i = 0; i < 40; i ++) {
            for (int j = 0; j < 40; j ++) {
                if(ui->label->ob.obs[i][j] == 1){
                    out << i << "\n";
                    out << j << "\n";
                }
            }
        }
        out << "Apple\n";
        out << ui->label->applePosition[0] << "\n";
        out << ui->label->applePosition[1] << "\n";
        out << "Time\n";
        out << getTime();
        file.close();
    }
    else{
        QMessageBox::warning(this, tr("Path"),
                                     tr("You did not select any file."));
    }

}


void MainWindow::load(){
    setButtonStatus(2);
    QString path = QFileDialog::getOpenFileName(this,
                   tr("Load File"), ".", tr("Text Files(*.txt)"));
    if(!path.isEmpty()){
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::warning(this, tr("Read File"),
                                     tr("Cannot open file:\n%1").arg(path));
            return;
        }
        ui->label->snake_0.data.clear();
        ui->label->snake_0.snakeInit();
        memset(ui->label->ob.obs, 0, sizeof (ui->label->ob.obs));
        QTextStream in(&file);
        QString str = in.readLine();
        if(str == "Snake"){
            int dir = in.readLine().toInt();
            ui->label->snake_0.setDirection(dir);
            int n = in.readLine().toInt();
            for (int i = 0; i < n; i ++) {
                int x_0 = in.readLine().toInt();
                int y_0 = in.readLine().toInt();
                if(i == 0 || i == 1)
                    ui->label->snake_0.data[i] = Position(x_0, y_0);
                else
                    ui->label->snake_0.data.push_back(Position(x_0, y_0));
            }
        }
        str = in.readLine();
        if (str == "Obstacle"){
            int n = in.readLine().toInt();
            for (int i = 0; i < n; i ++) {
                int x_0 = in.readLine().toInt();
                int y_0 = in.readLine().toInt();
                ui->label->ob.obs[x_0][y_0] = 1;
            }
        }
        str = in.readLine();
        if (str == "Apple"){
            ui->label->applePosition[0] = in.readLine().toInt();
            ui->label->applePosition[1] = in.readLine().toInt();
        }
        str = in.readLine();
        if (str == "Time"){
            int t = in.readLine().toInt();
            setTime(t);
        }
        paintAll();
        file.close();
    }
    else{
        QMessageBox::warning(this, tr("Path"),
                                    tr("You did not select any file."));
    }

}


void MainWindow::PaintAllElements(){
    paintAll();
}


void MainWindow::failed(){
    timer->stop();
    setButtonStatus(3);
    QMessageBox::about(this, "Failed", "Game Failed!");
}


void MainWindow::timeGo(){
    timeCount ++;
    ui->timeLabel->setText(QString::number(timeCount));
    if(ui->label->getAppleNum() > 0)
        ui->label->snakeEatApple();
    else
        ui->label->snakeGo();
    if(ui->label->snake_0.data[0].x == ui->label->applePosition[0] && ui->label->snake_0.data[0].y == ui->label->applePosition[1]){
        ui->label->setAppleNumber();
        ui->label->createApple();
    }
}


//初始化snake的位置
void MainWindow::createSnake(int){
    int x[3];
    for (int i = 0; i < 2; i ++) {
        x[i] = spi[i]->text().toInt();
    }
    if(x[1] == 0){
        set_items_abled(ui->comboBox, 1);
        set_items_disabled(ui->comboBox, 0);
    }else if(x[1] == 39){
        set_items_abled(ui->comboBox, 0);
        set_items_disabled(ui->comboBox, 1);
    }else{
        set_items_abled(ui->comboBox, 1);
        set_items_abled(ui->comboBox, 0);
    }
    if(x[0] == 0){
        set_items_abled(ui->comboBox, 3);
        set_items_disabled(ui->comboBox, 2);
    }else if(x[0] == 39){
        set_items_abled(ui->comboBox, 2);
        set_items_disabled(ui->comboBox, 3);
    }else{
        set_items_abled(ui->comboBox, 2);
        set_items_abled(ui->comboBox, 3);
    }
    ui->label->setSnake(x[0], x[1]);
    x[2] = ui->comboBox->currentIndex();
    switch (x[2]) {
    case 0 :
        ui->label->setSnakeTail(x[0], x[1]-1);
        break;
    case 1 :
        ui->label->setSnakeTail(x[0], x[1]+1);
        break;
    case 2 :
        ui->label->setSnakeTail(x[0]-1, x[1]);
        break;
    default:
        ui->label->setSnakeTail(x[0]+1, x[1]);
        break;
    }
    if (ui->label->touchObstacle(0) || ui->label->touchObstacle(1))
        but[0]->setEnabled(false);
    else
        but[0]->setEnabled(true);
    if(x[1] != 0 && x[2] != 0)
        ui->label->snake_0.setDirection(0);
    else if(x[1] != 39 && x[2] != 1)
        ui->label->snake_0.setDirection(1);
    else if(x[0] != 0 && x[2] != 2)
        ui->label->snake_0.setDirection(2);
    else
        ui->label->snake_0.setDirection(3);
}


void MainWindow::timeStart(){
    timer->start(150);
}


void MainWindow::set_items_disabled(QComboBox *com, int a){
        QModelIndex index = com->model()->index(a, 0);
        QVariant v(0);
        com->model()->setData(index, v, Qt::UserRole - 1);
}


void MainWindow::set_items_abled(QComboBox *com, int a){
        QModelIndex index = com->model()->index(a, 0);
        QVariant v(-1);
        com->model()->setData(index, v, Qt::UserRole - 1);
}


//绘制
void MainWindow::paintAll(){
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
    brush.setStyle(Qt::Dense1Pattern);
    painter.setBrush(brush);
    for(int i = 0; i < 40; i ++){
        for(int j = 0; j < 40; j ++){
            if(ui->label->ob.obs[i][j] == 1)
                painter.drawRect(25 * i, 25 * j, 25, 25);
        }
    }
    brush.setColor(Qt::red);
    brush.setStyle(Qt::Dense2Pattern);
    painter.setBrush(brush);
    painter.drawEllipse(25 * ui->label->applePosition[0], 25 * ui->label->applePosition[1], 25, 25);
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(25 * ui->label->snake_0.data[0].x, 25 * ui->label->snake_0.data[0].y, 25, 25);
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    for(unsigned int i = 1; i < ui->label->snake_0.data.size(); i ++){
        painter.drawRect(25 * ui->label->snake_0.data[i].x, 25 * ui->label->snake_0.data[i].y, 25, 25);
    }
    ui->label->setPixmap(pixmap);
}


void MainWindow::paintWithoutApple(){
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
    brush.setStyle(Qt::Dense1Pattern);
    painter.setBrush(brush);
    for(int i = 0; i < 40; i ++){
        for(int j = 0; j < 40; j ++){
            if(ui->label->ob.obs[i][j] == 1)
                painter.drawRect(25 * i, 25 * j, 25, 25);
        }
    }
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(25 * ui->label->snake_0.data[0].x, 25 * ui->label->snake_0.data[0].y, 25, 25);
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    for(unsigned int i = 1; i < ui->label->snake_0.data.size(); i ++){
        painter.drawRect(25 * ui->label->snake_0.data[i].x, 25 * ui->label->snake_0.data[i].y, 25, 25);
    }
    ui->label->setPixmap(pixmap);
}


int MainWindow::getTime(){
    return timeCount;
}


void MainWindow::setTime(int time){
    timeCount = time;
}



void MainWindow::on_action_5_triggered()
{
    this->close();
}
