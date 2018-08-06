#ifndef SKILL_H
#define SKILL_H
#include "bullet.h"



class Skill:public bullet
{
public:
    Skill();
public slots:
    virtual void fly();
private:
    int use_time=3;
};

#endif // SKILL_H
