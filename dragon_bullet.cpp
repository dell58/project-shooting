#include "dragon_bullet.h"
#include "skill.h"
dragon_bullet::dragon_bullet()
{

}

void dragon_bullet::fly()
{
    setPos(x(), y()+4);
    if(y()>670)
    {
        this->scene()->removeItem(this);
        delete this;
    }
}

void dragon_bullet::check_hit()
{
    QList<QGraphicsItem*> hit_enemy=collidingItems() ;
    int n= hit_enemy.size();
    for(int i =0 ;i<n;++i)
    {
        if(typeid(*hit_enemy[i])==typeid (Skill))//if the boss hit the bullet
           {
                    delete_item();

                return;
            }
    }
}

void dragon_bullet::delete_item()
{
    this->scene()->removeItem(this);
    delete this;
}
