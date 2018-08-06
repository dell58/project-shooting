#include "character.h"
#include "dragon_bullet.h"
#include "Enemy.h"
#include "mainwindow.h"


character::character()
{
    health = 10;
  //  MainWindow::get_character_health=health;
}

void character::check_hit()
{
    QList<QGraphicsItem*> hit_enemy=collidingItems() ;
    int n= hit_enemy.size();
    for(int i =0 ;i<n;++i)
    {
        if(typeid(*hit_enemy[i])==typeid (dragon_bullet) || typeid(*hit_enemy[i])==typeid(Enemy))//if the character hit the bullet or the enemy
           {   // emit score_increase();
                scene()->removeItem(hit_enemy[i]);//remove the hit bullet on scene
                delete hit_enemy[i];//remove the actual bullet im memory
                health=health-1;
                MainWindow::check_character_health=1;
                MainWindow::get_character_health=health;
               // MainWindow::add=2;
                if((health)<=0)//if the charater health <=0 delete it
                {
                    MainWindow::get_character_health=0;
                    MainWindow:: check_health=1;
                    delete_item();
                }

                return;
            }
    }
}
