#ifndef ROBOT_H
#define ROBOT_H

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <Aria.h>

#define GirarBase          1
#define ConexaoSerial      1
#define ConexaoRadio       2
#define ConexaoSimulacao   3

using namespace std;

class Robot{
    public:
        ArRobot robot;
        ArSonarDevice sonarDev;
        ArSick   sick;

        ArLaserConnector *laserConnector;
        ArRobotConnector *robotConnector;
        ArArgumentParser *parser;
        ArSimpleConnector *simpleConnector;
        ArAnalogGyro *gyro;
        ArSerialConnection con1;

        int Sensores[8];
        Robot();

        void destroy();
        void desconectar();
        void pararMovimento();
        void readSensores();

        int  getSonar(int i);
        int  isConnected();
        void headg();
        float getXPos();
        float getYPos();
        float getAngBase();

        void initMov();
        void getAllSonar(int *sensores);
        void Move(double vl,double vr);
        void getLaser();
        void Rotar(int sent);
        void RT1 (int RT);
        void espera(int time);
        void escribir();
        int sensors(int i);
        void rotaciona(double degrees, int sentido);
};

#endif // ROBOT_H
