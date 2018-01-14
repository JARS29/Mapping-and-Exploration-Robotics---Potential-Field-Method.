#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <robot.h>
#include <map.h>
#include "ui_mainwindow.h"
#include <QTimer>
#include <threadmap.h>
#include <threadrobot.h>
#include <QGLWidget>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
    void update();



    public slots:
        void on_Ad_pressed();
        void on_Ad_released();
        void on_Izq_pressed();
        void on_Izq_released();
        void on_Der_pressed();
        void on_Der_released();
        void on_At_pressed();
        void on_At_released();

    private:
        Ui::MainWindow *ui;
        Robot* piooner;
        Map* space;
        threadrobot *Navegador;
        QTimer Timer;
        threadmap *bm;

#endif // MAINWINDOW_H
};
