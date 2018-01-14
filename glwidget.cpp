#include "glwidget.h"
#include "iostream"
#include "mainwindow.h"
#include <robot.h>

using namespace std;

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent){
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}
void GLWidget::initializeGL(){
    glClearColor(1,1,1,0);
   }
void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);


//    setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
//   setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

}
void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
     glPointSize(4);
     glBegin(GL_POINTS);
    // mapeamento
     for(int i = 0; i < space->getSize(true); i++){
         for(int j = 0; j < space->getSize(false); j++){
            if(space->getPotencial(i,j)!=-1){
                //Bayes
                 glColor3f(1-space->getPotencial(i,j),1-space->getPotencial(i,j),1-space->getPotencial(i,j));

                //Bayes
                // glColor3f(1-space->getValueB(i,j),1-space->getValueB(i,j),1-space->getValueB(i,j));
            //HIMM
                 //glColor3f(1-space->getValue(i,j)/15,1-space->getValue(i,j)/15,1-space->getValue(i,j)/15);

                 float x = space->scalemap(i,1);
                 float y = space->scalemap(j,0);

                 glVertex2f(x,y);
                 }
         }
     }
     glEnd();

     glPointSize(4);
     glBegin(GL_POINTS);

     for(int i = 0; i < space->getSize(true); i++){
         for(int j = 0; j < space->getSize(false); j++){
            if(space->getValue(i,j)==15){
                //Bayes
                 //glColor3f(1-space->getPotencial(i,j),1-space->getPotencial(i,j),1-space->getPotencial(i,j));

                //Bayes
                // glColor3f(1-space->getValueB(i,j),1-space->getValueB(i,j),1-space->getValueB(i,j));
            //HIMM

                 glColor3f(0,0,0.7);

                 float x = space->scalemap(i,1);
                 float y = space->scalemap(j,0);

                 glVertex2f(x,y);
                 }
         }
     }
     glEnd();

//Trayectoria
    glPointSize(2);
    glColor3f(1,0,0);
    glBegin(GL_POINTS);

    for(int i = 0; i < space->getSize(true); i++){
        for(int j = 0; j < space->getSize(false); j++){
           if(space->IsPath(i,j)==1){
               float x = space->scalemap(i,1);
               float y = space->scalemap(j,0);
               glVertex2f(x,y);}
        }
    }
 glEnd();

//Lineas sensor
    glColor3f(1,0,0);
    glLineWidth(2);
    glBegin(GL_LINES);
    float mapy=space->scalemap(space->convert2map(piooner->getYPos(),0),0);
    float mapx= space->scalemap(space->convert2map(piooner->getXPos(),1),1);
    for (int i=0; i<8; i++){
        glBegin(GL_LINES);
        glVertex2f(mapx,mapy);
        glVertex2f(mapx + space->linessensor(piooner->sensors(i),piooner->getAngBase(),1, i),
                   mapy+space->linessensor(piooner->sensors(i),piooner->getAngBase(),0, i));
        glEnd();
}

//   for (int k=0; k<8;k++){  //bayes
//           if (S[k]<=1500)
//            space->bayes(piooner->getAngBase(),piooner->getXPos(),piooner->getYPos(),S[k],space->angels(k));

//    }
//    for (int l=0; l<8;l++){

//        S[l]=piooner->sensors(l);
//    if (S[l]<=2000)
//   space->HIMM(piooner->getAngBase(),piooner->getXPos(),piooner->getYPos(),S[l],space->angels(l));
//       }


//    space->potencial(space->convert2map(piooner->getXPos(),1)-50,space->convert2map(piooner->getXPos(),1)+50,
//            space->convert2map(piooner->getYPos(),0)-50,space->convert2map(piooner->getYPos(),0)+50);


}
