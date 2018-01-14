#include "robot.h"

using namespace std;

#define REAL 0
  int Robot::isConnected()
  { return(robot.isConnected());
  }


Robot::Robot() {
        int argc = 4;
        char** argv = (char **) new char[4];
        Aria::init();

        argv[0] = "-rh";
       //argv[1] = "192.168.1.11";  //physic robot
        argv[1] = "localhost";    //simulator (mobilesim)
        argv[2] = "-remoteLaserTcpPort";
        argv[3] = "10002";

        parser = new ArArgumentParser (&argc, argv);
        robotConnector =  new ArRobotConnector(parser, &robot);
        robot.addRangeDevice(&sick);

        if(!robotConnector->connectRobot()){
              cout<<"Error:Robot not Connected "<<endl;
              Aria::exit(1);
        }else cout<<"Robot Connected!"<<endl;




        robot.setHeading(0);
        robot.runAsync(true);
        robot.enableMotors();
        robot.setRotVelMax(10);


  }

  void Robot::destroy() { desconectar();Aria::shutdown(); }
  void Robot::pararMovimento() {   robot.stop(); }
  void Robot::desconectar()    {  robot.stopRunning(true); }

  int Robot::getSonar(int i){  return(Sensores[i]);}
  void Robot::getAllSonar(int *sensores)
  { for(int i=0;i<8;i++) sensores[i]=(int)(robot.getSonarRange(i));
  }
  void Robot::readSensores()
  { for(int i=0;i<8;i++) Sensores[i]=(int)(robot.getSonarRange(i));
   }
  float Robot::getXPos()   { return   (robot.getX()/10);}
  float Robot::getYPos()     { return   (robot.getY()/10);}
  float Robot::getAngBase () { return   (robot.getTh()); }
  void Robot::initMov()      {  robot.setVel2(50,50);  }



  void Robot::RT1(int RT){
     if(RT ==0){ //Derecha
         int i=0;
         while(1){
         robot.setVel2(50,-50);
         i++;
         if (i>40000)
            break;
         }
     }
     else if(RT==1){
         robot.setVel2(-50,50);//Izquierda
        }
     }

  void Robot::Rotar(int sent){


      if (sent==0){ //Derecha

          robot.setVel2(20,-40);


      }
      else if (sent==1){ //Izquierda


         robot.setVel2(-40,20);

    }
  }
  void Robot::Move(double vl,double vr)
  {
      robot.setVel2(vl,vr);
  }

  void Robot::espera(int time){
      ArUtil::sleep(time);

  }

 int Robot::sensors(int i){
      readSensores();
      int S[8];
      for (int j=0; j<8; j++){
          S[j]=getSonar(j);
      }
      return S[i];
  }


void Robot::rotaciona(double degrees, int sentido){
    robot.setDeltaHeading(degrees);
    if (sentido==0)
        robot.setVel((0));
    else if(sentido==1)
        robot.setVel(50);
    else if (sentido==2)
        robot.setVel(-50);
}
