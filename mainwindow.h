#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <cstdlib>
#include <QKeyEvent>
#include <QLabel>
#include <QFont>
#include <QLCDNumber>
#include <QProgressBar>

#include "character.h"
#include "Boss.h"
#include "dragon_bullet.h"
#include "bullet.h"
#include "Enemy.h"
#include "skill.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static int add;//check add score
    static int get_health;//get the health.. boss
    static int check_health;//check if item delete
    static int get_character_health;//get the charater's health
    static int check_character_health;//check the charater's health if it is drcreased

public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    void item_move();//func  to move character
    void bullet_shooting();//charater auto shooting
    void mon_shooting();//boss auto shooting
    void spawn_enemy();//spawn small dragon
    void increase();//increase the score
    void decrease();//decrease health
    void count_use_time();
    void disconnect_bullet();//disconnect func
    void disconnect_fire();//disconnect func
    void disconnect_enemy();
    void progress();//set boss progressbar
    void show_end();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *frame;//the frame
    QLCDNumber *scorenumber;//score number display
    QLCDNumber *characterhealth;//display the character's health
    QLCDNumber *skilltime;//display skill use times
    QProgressBar *bosshealth;//boss health display
    QTimer *timer;//control the speed of bullet
    QTimer *timer2;//control the generate speed of bullet and dragon_bullet, also the check_hit()
    QTimer *timer3;//control the signal of move_item()
    QTimer *timer_dragon_bullet;
    QTimer *timer_dragon_bullet2;
    QTimer *spawn;//connect the spawn func
    QTimer *small_dragon_fly;//connect the small dragon's fly()
    QTimer *timer4;//connect the  disconnect func
    Boss *dragon;//the boss
    character *player;//the player
    int move_variable=0;//control the keyboard
    int small_dragon_pos;
    int score =0 ;//initial score value
    int count_skill=5;
};

#endif // MAINWINDOW_H














