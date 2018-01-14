#include "mainwindow.h"
#include <QApplication>
#include "ui_mainwindow.h"

#include <QGLWidget>
#include <map.h>
#include "iostream"
#include <QVBoxLayout>

using namespace  std;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);    
    MainWindow w;


    w.show();
    return a.exec();


  return 0;
}
