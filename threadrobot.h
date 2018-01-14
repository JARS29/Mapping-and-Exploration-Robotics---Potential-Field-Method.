#ifndef THREADROBOT_H
#define THREADROBOT_H
#include <QThread>
#include <map.h>
#include <robot.h>


class threadrobot : public QThread
{
public:
    threadrobot(Map *m, Robot *myrobot, int time);
    void run();
private:
    Robot *Myrobot;
    Map *mp;
    int time;

};

#endif // THREADROBOT_H
