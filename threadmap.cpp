#include "threadmap.h"
#include <math.h>
#include <QtGlobal>

threadmap::threadmap(threadrobot *navr, Map *m, Robot *robot, int t){
    MP = m;
    myrobot =robot;
    time =t;
    nave= navr;

}

void threadmap::Bayes(){
    for (int k=0; k<8;k++){
        float posx= myrobot->getXPos();
        float posy= myrobot->getYPos();
        float ang1= MP->convertrad(myrobot->getAngBase() + MP->angels(k));
        float x1=myrobot->sensors(k)*sin(ang1);
        x1=floor((x1)*400/4900);
        float y1=-myrobot->sensors(k)*cos(ang1);
        y1=floor((y1)*400/4900);
        x1=MP->convert2map(posx + x1,1);
        y1=MP->convert2map(posy + y1,0);
        double dist=sqrt(pow(double(x1-MP->convert2map(posx,1)),2)+(pow(double(y1-MP->convert2map(posy,0)),2)));
        float R=floor((1500)*400/4900);
        float Beta=15;
        float Ptotal;
        if (myrobot->sensors(k)<2000){
            for (int i=fabs(double(MP->convert2map(posy,0)-dist)); i<=fabs(double(MP->convert2map(posy,0)+dist));i++){
                for(int j=fabs(double(MP->convert2map(posx,1)-dist)); j<=fabs(double(MP->convert2map(posx,1)+dist)); j++){
                    if (i>=0 && i<=400 && j<=400 && j>=0){
                        double Ax=(x1-MP->convert2map(posx,1));
                        double Ay=(y1-MP->convert2map(posy,0));
                        double Bx=(j-MP->convert2map(posx,1));
                        double By=(i-MP->convert2map(posy,0));
                        double AB=Ax*Bx+Ay*By;
                        double NA=sqrt(pow(double(Ax),2) + pow(double(Ay),2));
                        double NB=sqrt(pow(double(Bx),2) + pow(double(By),2));
                        double theta = acos(AB/(NA*NB));
                        theta= theta*(180/PI);

                        if (theta<=15/2){
                            double aa=sqrt(pow(double(j-MP->convert2map(posx,1)),2)+(pow(double(i-MP->convert2map(posy,0)),2)));
                            if(aa<= dist+1.75 && aa>=dist-1.75){
                                float PH=((((R-aa)/R)+((Beta-theta)/Beta))/2)*0.98;
                                float PHE = 1.0 -PH;
                                Ptotal = ((MP->getValueB(j, i) * PH)/((MP->getValueB(j,i)*PH) + (1.0 - MP->getValueB(j,i))*PHE));
                                MP->setValueB(j,i,Ptotal);
                            }
                            if(aa>0 && aa< dist-1.75){
                                float PHE=((((R-aa)/R)+((Beta-theta)/Beta))/2);
                                float PH = 1.0 -PHE;
                                Ptotal = ((MP->getValueB(j, i) * PH)/((MP->getValueB(j,i)*PH) + (1.0-MP->getValueB(j,i))*PHE));
                                MP->setValueB(j,i,Ptotal);
                            }
                        }
                    }
                }
            }
        }
    }
}

void threadmap::HIMM(){
      int robox= MP->convert2map(myrobot->getXPos(),1);
      int roboy= MP->convert2map(myrobot->getYPos(),0);
      float x1, x2;
      float y1,y2;
       for (int i=0; i<8; i++){
            if(myrobot->getSonar(i)<=2500){
               float ang1= MP->convertrad(myrobot->getAngBase() + MP->angels(i));
               x1=myrobot->getSonar(i)*sin(ang1);
               x1=ceil((x1)*400/4900);
               y1=-myrobot->getSonar(i)*cos(ang1);
               y1=ceil((y1)*400/4900);
               x1=MP->convert2map(myrobot->getXPos()+ x1,1);
               y1=MP->convert2map(myrobot->getYPos() + y1,0);
               MP->Bresenham(robox,roboy,x1,y1);
               MP->setValue(x1+1,y1+1,1);
               MP->setValue(x1+1,y1-1,1);
               MP->setValue(x1+1,y1,1);
               MP->setValue(x1,y1+1,1);
               MP->setValue(x1,y1-1,1);
               MP->setValue(x1,y1,1);
               MP->setValue(x1-1,y1+1,1);
               MP->setValue(x1-1,y1-1,1);
               MP->setValue(x1-1,y1,1);}
        else{
                float ang1= MP->convertrad(myrobot->getAngBase() + MP->angels(i));
                x2=myrobot->getSonar(i)*sin(ang1);
                x2=ceil((x2)*400/4900);
                y2=-myrobot->getSonar(i)*cos(ang1);
                y2=ceil((y2)*400/4900);
                x2=MP->convert2map(myrobot->getXPos()+ x2,1);
                y2=MP->convert2map(myrobot->getYPos() + y2,0);
                MP->setvisitado(x2,y2,1);

             //    MP->Bresenham(robox,roboy,x2,y2);
            }
       }
}
void threadmap::run(){
    myrobot->espera(200);
    int prov=0;

       while(1){
             prov=prov+1;
             HIMM();
             myrobot->robot.setVel2(80,-80);
             if (prov>=1800000)
                break;}



   nave->start();
    while(true){
        float posx= MP->convert2map(myrobot->getXPos(),1);
        float posy =MP->convert2map(myrobot->getYPos(),0);

       MP->potencial(posx-100,posx+100,posy-100,posy+100);
       // Bayes();
        HIMM();
        QThread::msleep(time);
    }

}


