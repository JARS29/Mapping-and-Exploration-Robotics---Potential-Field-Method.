#ifndef GLWIDGET_H
#define GLWIDGET_H



#include <QGLWidget>
#include <QTimer>
#include <map.h>
#include <robot.h>

#define TRH 1000;


class GLWidget : public QGLWidget{
    public:

        explicit GLWidget(QWidget *parent = 0);
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);
        Robot* piooner;
        QTimer timer;
        Map* space;


};


#endif // GLWIDGET_H
