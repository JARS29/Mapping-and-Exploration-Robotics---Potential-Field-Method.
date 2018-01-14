#include "threadrobot.h"

threadrobot::threadrobot(Map *m, Robot *rbt, int t)
        {
    Myrobot = rbt;
    mp = m;
    time =t;
}


void threadrobot::run(){
    int robox,roboy;
    double ang,angrobot,dif;
    while(true){
        robox=(int) mp->convert2map(Myrobot->getXPos(),1);
        roboy=(int) mp->convert2map(Myrobot->getYPos(),0);
        ang= mp->angpotencial(robox,roboy);
        angrobot= Myrobot->robot.getTh();
       mp->vez(robox,roboy);
       mp->putPath(robox,roboy);


dif = (ang-angrobot);
        //dif = fmod((dif+180+360),360) - 180;
//      dif = (ang-angrobot);
//        if (dif <-190)
//            ang+=360;
//        else if(dif>190)
//            ang-=360;


//        dif = (ang-angrobot);
        cout<< ang << " " << angrobot<< "  "<< dif<<endl;


if(dif <= 90){
    dif = dif * (PI/180);
    Myrobot->robot.setVel2(50-50*sin(dif),50+50*sin(dif));
}else{
    dif = dif * (PI/180);
    Myrobot->robot.setVel2(10-20*sin(dif),10+20*sin(dif));
}

//if(dif>5  || dif<-5){
//    if (dif>0 && dif<90)
//        Myrobot->rotaciona(-50,1);
//     else if(dif>0 && dif>= 90)
//         Myrobot->rotaciona(-50,0);
//     else if (dif<0 && dif>-90)
//         Myrobot->rotaciona(50,1);
//     else if (dif<0 && dif<=-90)
//         Myrobot->rotaciona(50,0);
//       }
//    else
//        Myrobot->Move(80,80);

        QThread::msleep(time);
    }
}




