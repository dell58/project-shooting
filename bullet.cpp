#include "bullet.h"

bullet::bullet()
{

}

void bullet::fly()
{
    setPos(x(), y() - 4);
    if(y() < 0) {
        this->scene()->removeItem(this);
        delete this;
    }
}



void bullet::random_move()
{

}

void bullet::check_hit()
{

}

void bullet::check_hit2()
{

}
