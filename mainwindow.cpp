#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "glwidget.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    piooner = new Robot();
    space = new Map();

    ui->widget->space = space;
    ui->widget->piooner = piooner;


    Navegador = new threadrobot(space,piooner,100);

    bm = new threadmap(Navegador,space,piooner,100);
    bm->start();
    QTimer *timer = new QTimer( this );
    timer->setInterval(300);

    timer->start();

}

MainWindow::~MainWindow(){
    delete ui;
}



void MainWindow::on_Ad_pressed(){
     piooner->Move(80,80);
     int x = space->convert2map(piooner->getXPos(), 1);
     int y = space->convert2map(piooner->getYPos(), 0);
     //space->putPath(x, y);
}

void MainWindow::on_Ad_released(){
     piooner->pararMovimento();
}

void MainWindow::on_Izq_pressed(){
     piooner->Rotar(1);
     int x = space->convert2map(piooner->getXPos(), 1);
     int y = space->convert2map(piooner->getYPos(), 0);
     //space->putPath(x, y);
}

void MainWindow::on_Izq_released(){
     piooner->pararMovimento();
}

void MainWindow::on_Der_pressed(){
     piooner->Rotar(0);
     int x = space->convert2map(piooner->getXPos(), 1);
     int y = space->convert2map(piooner->getYPos(), 0);
    //space->putPath(x, y);
}
void MainWindow::on_Der_released(){
     piooner->pararMovimento();
}

void MainWindow::on_At_pressed(){
     piooner->Move(-80,-80);
     int x = space->convert2map(piooner->getXPos(), 1);
     int y = space->convert2map(piooner->getYPos(), 0);
     //space->putPath(x, y);
}

void MainWindow::on_At_released(){
     piooner->pararMovimento();
}



