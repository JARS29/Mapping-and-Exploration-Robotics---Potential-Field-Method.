#include "map.h"
#include <iostream>
#include <math.h>
#include <QtGlobal>
#include <glwidget.h>
using namespace std;

Map::Map(){
    for(int i = 0; i < SIZEB; i++){
        for(int j = 0; j < SIZEA; j++){
            M1[i][j] = 0.5; // bayes -
            M2[i][j] = 0; //visitado (bool)
            M3[i][j]=0; // potencial
            M4[i][j]=0; //HIMM
            M5[i][j] = 0;
        }
    }
    sizeMF = SIZEB;
    sizeMC=SIZEA;
}
int Map::angels(int i){
    int angles[8]={180, 140, 120, 100, 80, 60, 40, 0};
    return angles[i];
}
float Map::convertrad(int deg){
    return deg*PI/180.0;
}

float Map::getValueB(int x, int y){//BAYES
    return M1[y][x];
}
void Map::setValueB(int x, int y, float value){//BAYES
        M1[y][x] = value;
}

float Map::getValue(int x, int y){//HIMM
    return M4[y][x];
}
void Map::setValue(int x, int y, bool value){//HIMM
    float valor;
    setvisitado(x,y,1);
    if (value==1){ //ocupado
        valor=getValue(x,y)+3;
                }
    else{ //libre
        valor=getValue(x,y)-1;
        }

    if (valor>=15){
        valor=15;
        setPotencial(x,y,1);
                     }
    else if(valor<0){
        valor=0;
        }
    if (getValue(x,y)>12)
        setPotencial(x,y,1);

        M4[y][x] = valor;
}

int Map::convert2map(float position, bool axis){
    int nposition;
    if(axis) // ejex
        nposition = floor(position/CELDA) + SIZEA/2;
    else //eje y
        nposition = SIZEB/2 - floor(position/CELDA);

    return nposition;
}
float Map::scalemap(int x, bool z){
    float val;
    if(z) //x
        val=x*(0.005) - (1.0-0.005/2);
    else//y
        val= (1.0-0.005/2) - x*(0.005);

    return val;
}
float Map::linessensor(int s, int ang, bool axis, int i){
    float a,b;
    float an= convertrad(ang+angels(i));
    a=s*sin(an);
    a=ceil((a)*400/4900);
    a=((a/CELDA)*0.005);
    b = -s*cos(an);
    b=ceil((b)*400/4900);
    b=((b/CELDA)*0.005);
    if (axis)
        return a;
    else
        return b;
}
void Map::putPath(int x, int y){ //Trajectoria
    M5[y][x] = 1;
}
bool Map :: IsPath(int x, int y){ //Trajectoria
    return M5[y][x];
}
int Map::getSize(bool f){
    if (f)
        return sizeMF;
    else
        return sizeMC;
}
bool Map::getvisitado(int i, int j){ //visit
    return M2[j][i];
}
void Map::setvisitado(int i, int j, bool value){ //visit
    M2[j][i]=value;
}
float Map::matrixW(int i, int j){
    float value=0;
    int x=i; int y=j;
    double a1,a,a2,c1,c,c2,ab1,ab,ab2;

    a1 = getValue(x-1,y-1)*0.5;
    a = getValue(x,y-1);
    a2 = getValue(x+1,y-1)*0.5;
    c1 = getValue(x-1,y)*0.5;
    c = getValue(x,y);
    c2 = getValue(x+1,y)*0.5;
    ab1 = getValue(x-1,y+1)*0.5;
    ab = getValue(x,y+1);
    ab2 = getValue(x+1,y+1)*0.5;

    value = a1+a2+a+c1+c2+c+ab1+ab2+ab;
    if (value>=15){
        value=15;
    }
    return value;

}
bool Map::borde(int i, int j){
    return  i >= 0 && i < sizeMC && j >= 0 && j < sizeMF;
}
void Map::potencial(int xmin, int xmax, int ymin, int ymax){
    double newpot = 0.0,esq,dir,cima,baixo;
    double erropot = 1.,erromax =  0.000001;

    while(erropot > erromax){
        erropot = 0;

        //CIMA-BAIXO, ESQ-DIR
        for(int i = xmin; i < xmax; i++){
            for(int j = ymin; j < ymax; j++){
                if(getvisitado(i,j) == 1 && getValue(i,j)<12){
                    esq = dir = cima = baixo = 0.0;

                    esq = getPotencial(i-1,j);
                    dir = getPotencial(i+1,j);
                    cima = getPotencial(i,j-1);
                    baixo = getPotencial(i,j+1);

                    setPotencial(i,j,(esq + dir + cima + baixo)*0.25);
                }
            }
        }

        //        //BAIXO-CIMA,ESQ-DIR
        for(int i = xmax; i > xmin; i--){
            for(int j = ymin; j < ymax; j++){
                if(getvisitado(i,j) == 1 && getValue(i,j)<12){
                    esq = dir = cima = baixo = 0.0;

                    esq = getPotencial(i-1,j);
                    dir = getPotencial(i+1,j);
                    cima = getPotencial(i,j-1);
                    baixo = getPotencial(i,j+1);

                    setPotencial(i,j,(esq + dir + cima + baixo)*0.25);
                }
            }
        }

        //        //CIMA-BAIXO, DIR-ESQ
        for(int i = xmin; i < xmax; i++){
            for(int j = ymax; j > ymin; j--){
                if(getvisitado(i,j) == 1 && getValue(i,j)<12){
                    esq = dir = cima = baixo = 0.0;

                    esq = getPotencial(i-1,j);
                    dir = getPotencial(i+1,j);
                    cima = getPotencial(i,j-1);
                    baixo = getPotencial(i,j+1);

                    setPotencial(i,j,(esq + dir + cima + baixo)*0.25);
                }
            }
        }
        //BAIXO-CIMA, DIR-ESQ
        for(int i = xmax; i > xmin; i--){
            for(int j = ymax; j > ymin; j--){
                if(getvisitado(i,j) == 1 && getValue(i,j)<12){
                    esq = dir = cima = baixo = 0.0;

                    esq = getPotencial(i-1,j);
                    dir = getPotencial(i+1,j);
                    cima = getPotencial(i,j-1);
                    baixo = getPotencial(i,j+1);

                    newpot = (esq + dir + cima + baixo)*0.25;
                    erropot += pow(getPotencial(i,j)-newpot,2);
                    newpot= getPotencial(i,j);
                    //cout<< esq<< "  "<< dir<<"  "<< baixo<<" "<< cima"  "<<endl;
                }
            }
        }
    }
}
void Map::setPotencial(int x, int y, double value){
    M3[y][x]=value;
}

double Map::getPotencial(int x, int y){
    return M3[y][x];
}
void Map::vez(int x, int y){
    float pot; double arriba=0.0, abajo = 0.0, atras=0.0, adelante=0.0;
    if(borde(x,y)){
        atras=getPotencial(x-1,y);
        arriba=getPotencial(x,y-1);
        abajo=getPotencial(x,y+1);
        adelante=getPotencial(x+1,y);}
    cout <<atras<< "  "<< arriba<< "  "<< abajo<< "  "<< adelante<<endl;

}
float Map::angpotencial(int x, int y){
    double atr,ade,arr,aba;
    atr = getPotencial(x-1,y);
    ade = getPotencial(x+1,y);
    arr = getPotencial(x,y-1);
    aba =getPotencial(x,y+1);
    //    cout << atr<< "  "<< ade <<"  "<< arr<<"  "<< aba <<"  "<< atan2(-(aba-arr),-(ade-atr))*180/PI<<
    //         "  " <<getValue(x-1,y)<< "  " << getValue(x+1,y)<<"  "<<getValue(x,y-1)<<"  "<<getValue(x,y+1)<<endl;
    return atan2((aba-arr),(atr-ade))*(180/PI);
}


void Map::Bresenham(int x_robot, int y_robot, int  x_obst, int y_obst){
    int dx, dy, p, incE, incNE, stepx, stepy;
    int tempx = x_robot;
    int tempy = y_robot;

    dx = (x_obst - x_robot);
    dy = (y_obst - y_robot);

    if(dy < 0) dy = -dy, stepy = -1;
    else stepy = 1;

    if(dx < 0) dx = -dx, stepx = -1;
    else stepx = 1;

    setValue(tempx,tempy,0);

    if(dx > dy){
        p = 2*dy-dx;
        incE = 2*dy;
        incNE = 2*(dy-dx);

        while(tempx != x_obst){
            tempx += stepx;
            if(p < 0) p+= incE;
            else tempy += stepy, p+=incNE;

            setValue(tempx,tempy,0);
        }
    }else{
        p = 2*dx - dy;
        incE = 2*dx;
        incNE = 2*(dx-dy);
        while(tempy != y_obst){
            tempy += stepy;
            if(p < 0) p += incE;
            else tempx += stepx, p += incNE;
            setValue(tempx,tempy,0);

        }
    }
}
