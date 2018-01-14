#ifndef THREADMAP_H
#define THREADMAP_H
#include <QThread>
#include <robot.h>
#include <map.h>
#include <threadrobot.h>



class threadmap : public QThread
{
public:

    threadmap(threadrobot *navr, Map *mapa, Robot *robot, int time);
    void HIMM();
    void Bayes();
    void run();
private:
    Map *MP;
    Robot *myrobot;
    threadrobot *nave;
    int time;
};

#endif // THREADMAP_H
