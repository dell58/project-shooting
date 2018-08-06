#ifndef DRAGON_BULLET_H
#define DRAGON_BULLET_H
#include "bullet.h"


class dragon_bullet:public bullet
{
public:
    dragon_bullet();
public slots:
    virtual void fly();
    virtual void check_hit();
    virtual void delete_item();

};

#endif // DRAGON_BULLET_H
