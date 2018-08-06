#ifndef BOSS_H
#define BOSS_H
#include <cstdlib>
#include "bullet.h"
#include <QList>


class Boss:  public bullet
{


public:
    Boss();
public slots:
    virtual void random_move();
    virtual void check_hit();
    virtual void delete_item();


protected:
   int choose;
   int health=100;

};

#endif // BOSS_H
