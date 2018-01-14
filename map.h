#ifndef MAP_H
#define MAP_H
#define SIZEA 400
#define SIZEB 400

#define CELDA 8
#define PI 3.14159265


#include<math.h>
#include <QTimer>

class Map{
    public:
        Map();
        bool getvisitado(int i , int j);
        void setvisitado (int i, int j, bool value);
        bool borde(int i, int j);
        float getValueB(int x, int y);
        void setValueB(int x, int y, float value);

        float getValue(int x, int y);
        void setValue(int x, int y, bool value);

        int convert2map(float position, bool axis);
        float scalemap(int x, bool z);
        float convertrad(int deg);
        float linessensor(int s, int ang, bool axis, int i);

        void putPath(int x, int y);
        bool IsPath(int x, int y);

        void bayes(float rad, float posx, float posy, float s, float ang);
        void HIMM(float rad, float posx, float posy, float s, float ang);

        int getSize(bool f);
        int angels(int i);

        float matrixW(int i, int j);
        void Bresenham(int x_robot, int y_robot, int  x_obst, int y_obst);

        void potencial(int xmin, int xmax, int ymin, int ymax);
        float angpotencial(int x, int y);
        void setPotencial(int x, int y, double value);
        double getPotencial(int x, int y);
        void vez(int x, int y);


    private:
        QTimer timer;
        int sizeMC, sizeMF;
        float M1[SIZEB][SIZEA]; // bayes
        bool M2[SIZEB][SIZEA];  // visitado
        double M3[SIZEB][SIZEA];  //Potencial
        float M4[SIZEB][SIZEA];     //HIMM
        bool M5[SIZEB][SIZEA];


};

#endif // MAP_H
