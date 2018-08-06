#ifndef CHARACTER_H
#define CHARACTER_H
#include "Boss.h"



class character:public Boss
{
public:
    character();
public slots:
    virtual void check_hit();

};

#endif // CHARACTER_H
