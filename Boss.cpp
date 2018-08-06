#include "Boss.h"
#include "mainwindow.h"
#include <QDebug>
Boss::Boss()
{
 choose  = 25;
 //MainWindow::get_health=health;
}

void Boss::random_move()
{   //int mv;
    if(x()+25>410)
        choose=-25;
    if(x()<0)
        choose = 25;
    setPos(x()+choose,y());
    /*switch (choose) {
    case 0:
        if(x()+25>900)
        {
            choose = 1;
            break;
        }
        if(y()+25>70)
        {
            choose = 1;
            break;
        }
        setPos(x(),y()+25);
        setPos(x()+25,y());
        break;
    case 1:
        if(x()-25<60)
        {
            choose = 0;
            break;
        }
        if(y()-25<20)
        {
            choose = 0;
            break;
        }
        setPos(x()-25,y());
        setPos(x(),y()-25);
        break;
    case 2:
        if(y()+25>70)
            break;
        setPos(x(),y()+25);
        break;
    case 3:
        if(y()-25<20)
            break;
        setPos(x(),y()-25);
        break;

    }*/

}

void Boss::check_hit()
{
    QList<QGraphicsItem*> hit_enemy=collidingItems() ;
    int n= hit_enemy.size();
    for(int i =0 ;i<n;++i)
    {
        if(typeid(*hit_enemy[i])==typeid (bullet))//if the boss hit the bullet
           {   // emit score_increase();
                scene()->removeItem(hit_enemy[i]);//remove the hit bullet on scene
                delete hit_enemy[i];//remove the actual bullet im memory
                health -=1;
                MainWindow::get_health=health;
                if(health <= 0)//if the boss health <=0 delete it
                {
                    MainWindow::check_health=1;
                    delete_item();
                }

                return;
            }
    }
    //qDebug()<<"10"<<endl;
}

void Boss::delete_item()
{
        this->scene()->removeItem(this);
        //delete this;
}
