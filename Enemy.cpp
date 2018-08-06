#include "Enemy.h"
#include "mainwindow.h"
#include "skill.h"

Enemy::Enemy()
{
  health=3;
}
void Enemy::random_move()
{
    setPos(x(), y()+3);
    if(y()>620)
    {
       // this->scene()->removeItem(this);
        delete this;
    }

}

void Enemy::check_hit()
{
    QList<QGraphicsItem*> hit_enemy=collidingItems() ;
    int n= hit_enemy.size();
    for(int i =0 ;i<n;++i)
    {
        if(typeid(*hit_enemy[i])==typeid (bullet))//if the enemy hit the bullet
           {   // emit score_increase();
                scene()->removeItem(hit_enemy[i]);//remove the hit bullet on scene
                delete hit_enemy[i];//remove the actual bullet im memory
                health -=1;
                if((health-=1) < 0)//if the enemy health <=0 delete it
                {
                    MainWindow::add=1;
                    delete_item();
                }

                return;
            }
    }
}

void Enemy::check_hit2()
{
    QList<QGraphicsItem*> hit_enemy=collidingItems() ;
    int n= hit_enemy.size();
    for(int i =0 ;i<n;++i)
    {
        if(typeid(*hit_enemy[i])==typeid (Skill))//if the enemy hit the bullet
           {   // emit score_increase();
               // scene()->removeItem(hit_enemy[i]);//remove the hit bullet on scene
                //delete hit_enemy[i];//remove the actual bullet im memory
                health = health-3;
                if(health<=0)//if the enemy health <=0 delete it
                {
                    MainWindow::add=1;
                    delete_item();
                }

                return;
            }
    }
}


