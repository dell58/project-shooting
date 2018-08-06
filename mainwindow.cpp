#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 1000, 800)),
    timer(new QTimer),
    timer2(new QTimer),
    timer3(new QTimer),
    timer_dragon_bullet(new QTimer),
    timer_dragon_bullet2(new QTimer),
    spawn(new QTimer),
    small_dragon_fly(new QTimer),
    timer4(new QTimer)
{

    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
   // scorelabel =new QLabel;
    ui->scorelabel->setText(tr("Score:"));
    ui->scorelabel->setGeometry(680,30,70,50);
    ui->scorelabel->setFont(QFont("Ubuntu",16));
    ui->character->setText(tr("Health:"));
    ui->character->setGeometry(680,250,70,50);
    ui->character->setFont(QFont("Ubuntu",16));
    ui->skilltime->setText(tr("Skill Times:"));
    ui->skilltime->setGeometry(660,460,120,50);
    ui->skilltime->setFont(QFont("Ubuntu",16));
    ///////////////////////////
    scorenumber= new QLCDNumber(this);
    scorenumber->setPalette(Qt::black);
    scorenumber->setDigitCount(6);
    scorenumber->display(0);
    scorenumber->setGeometry(680,100,70,50);
    connect(timer2,SIGNAL(timeout()),this,SLOT(increase()));
    characterhealth=new QLCDNumber(this);
    characterhealth->setPalette(Qt::black);
    characterhealth->setDigitCount(3);
    characterhealth->display(10);
    characterhealth->setGeometry(680,320,70,50);
    connect(timer2,SIGNAL(timeout()),this,SLOT(decrease()));
    skilltime=new QLCDNumber(this);
    skilltime->setPalette(Qt::black);
    skilltime->setDigitCount(5);
    skilltime->display(count_skill);
    skilltime->setGeometry(680,540,70,50);
    connect(timer2,SIGNAL(timeout()),this,SLOT(count_use_time()));
    ///////////////////////////////////
    bosshealth = new QProgressBar(this);
    bosshealth->setGeometry(100,30,400,20);
    bosshealth->setMaximum(100);
    connect(timer2,SIGNAL(timeout()),this,SLOT(progress()));
    ///////////////////////////////////////
    frame = new QGraphicsPixmapItem(QPixmap(":/res/frame.png").scaled(900,750));
    frame->setPos(0,0);
    scene->addItem(frame);
    /////////////////////////////player
    player = new character;
    player->setPixmap(QPixmap(":/res/character.png").scaled(80,80));
    player->setPos(300, 600);
    scene->addItem(static_cast<QGraphicsPixmapItem*>(player));
    timer2->start(150);//bullet generate per/150ms
    timer3->start(15);//signal item move
    connect(timer2,SIGNAL(timeout()),this,SLOT(bullet_shooting()));//auto shooting
    /////////////////
    timer4->start(1);
    connect(timer4,SIGNAL(timeout()),this,SLOT(disconnect_bullet()));//disconnect bullet prevent crash
    connect(timer4,SIGNAL(timeout()),this,SLOT(disconnect_fire()));//disconnect fire dragon bullet
    //////////////////////
    connect(timer3,SIGNAL(timeout()),this,SLOT(item_move()));//press key to move item
    player->connect(timer2,SIGNAL(timeout()),player,SLOT(check_hit()));//hit and delete
    ///////////////////////
    srandom(time(NULL));//random seed
    /////////the dragon boss
    dragon = new Boss;
    dragon->setPixmap(QPixmap("/home/pd2vm/project3/res/fire_dragon.png").scaled(300,300));
    dragon->setPos(200,10);
    dragon->connect(timer2,SIGNAL(timeout()),dragon,SLOT(random_move()));//dragon move
    dragon->connect(timer2,SIGNAL(timeout()),dragon,SLOT(check_hit()));//hit and delete
    scene->addItem(static_cast<QGraphicsPixmapItem*>(dragon));
    timer_dragon_bullet2->start(1500);//per 1.5 s shoot a bullet
    connect(timer_dragon_bullet2,SIGNAL(timeout()),this,SLOT(mon_shooting()));
    //////////////////the enemy small dragon spawn
    spawn->start(2000);//per 2 seconds spawn an enemy
    connect(spawn,SIGNAL(timeout()),this,SLOT(spawn_enemy()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(disconnect_enemy()));
  //  connect(timer2,SIGNAL(timeout()),this,SLOT(increase()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(show_end()));//show Game end
    ui->show->hide();

    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        move_variable=1;
      //if(player->y()<0)
         //  break;
       // player->setPos(player->x(), player->y() - 25);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        move_variable=2;
      // if(player->y()>600)
        //    break;
        //player->setPos(player->x(), player->y() + 25);
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        move_variable=3;

     //  if(player->x()<150)
       //     break;
       // player->setPos(player->x() - 25, player->y());
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        move_variable=4;
      //if(player->x()>750)
           //break;
        //player->setPos(player->x() + 25, player->y());
        break;
    case Qt::Key_Space:
        if(count_skill<=0)
            break;
        count_skill-=1;
    Skill *d = new Skill;
    d->setPixmap(QPixmap(":/res/skill.png").scaled(600, 500));
    d->setPos(player->x() + player->pixmap().width() / 2 - d->pixmap().width() / 2, player->y()-150);
    timer->start(10);
    d->connect(timer, SIGNAL(timeout()),d, SLOT(fly()));//calling per/10ms
    scene->addItem(static_cast<QGraphicsPixmapItem*>(d));
    break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Right:
    case Qt::Key_Left:
    case Qt::Key_Up:
    case Qt::Key_Down:
        move_variable = 0;
        break;
    }

}

void MainWindow::item_move()
{
    switch(move_variable)
    {
    case 1:
        if(player->y()<20)
             break;
        player->setPos(player->x(), player->y() - 10);
        break;
    case 2:
        if(player->y()>640)
             break;
        player->setPos(player->x(), player->y() + 10);
        break;
    case 3:
        if(player->x()<63)
             break;
        player->setPos(player->x() - 10, player->y());
        break;
    case 4:
        if(player->x()>550)
             break;
        player->setPos(player->x() + 10, player->y());
        break;
    case 0:
        break;

    }
}


void MainWindow::bullet_shooting()
{
    bullet *b = new bullet;
    b->setPixmap(QPixmap(":/res/bullet.png").scaled(100, 100));
    b->setPos(player->x() + player->pixmap().width() / 2 - b->pixmap().width() / 2, player->y() - 7);
    timer->start(10);
    b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));//calling per/10ms
    scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
}

void MainWindow::mon_shooting()
{
    dragon_bullet* b1=new dragon_bullet;
    b1->setPixmap(QPixmap(":/res/dragon_bullet.png").scaled(100, 100));
    b1->setPos(dragon->x() + dragon->pixmap().width() / 2 - b1->pixmap().width() / 2,dragon->y()+150);
    timer_dragon_bullet->start(40);
    b1->connect(timer_dragon_bullet, SIGNAL(timeout()), b1, SLOT(fly()));//calling per/10ms
    b1->connect(timer2,SIGNAL(timeout()),b1,SLOT(check_hit()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(b1));

}

void MainWindow::spawn_enemy()
{
    Enemy *small_dragon=new Enemy;
    small_dragon_pos=random()%530;
    small_dragon->setPixmap(QPixmap(":/res/enemy.png").scaled(200,200));
    small_dragon->connect(timer2,SIGNAL(timeout()),small_dragon,SLOT(check_hit()));//hit and delete
    small_dragon->connect(timer2,SIGNAL(timeout()),small_dragon,SLOT(check_hit2()));//
    small_dragon->setPos(small_dragon_pos,0);
    small_dragon_fly->start(30);
    small_dragon->connect(small_dragon_fly,SIGNAL(timeout()),small_dragon,SLOT(random_move()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(small_dragon));
}

void MainWindow::increase()
{
    if(add==1)
    {
        score+=200;
        scorenumber->display(score);//lcdnumber
        add=0;
    }
   // qDebug()<<score<<endl;

}

void MainWindow::decrease()
{
    if(check_character_health==1)
    {
        characterhealth->display(get_character_health);
        check_character_health=0;
    }
}

void MainWindow::count_use_time()
{
    skilltime->display(count_skill);
}

void MainWindow::disconnect_bullet()
{
    if(check_health==1)
    {
        disconnect(timer2,SIGNAL(timeout()),this,SLOT(bullet_shooting()));
    }
}

void MainWindow::disconnect_fire()
{
    if(check_health==1)
    {
        disconnect(timer_dragon_bullet2,SIGNAL(timeout()),this,SLOT(mon_shooting()));

    }
}

void MainWindow::disconnect_enemy()
{
    if(check_health==1)
    {
        disconnect(spawn,SIGNAL(timeout()),this,SLOT(spawn_enemy()));
    }
}

void MainWindow::progress()
{
    bosshealth->setValue(get_health);//progressbar
}

void MainWindow::show_end()
{
    if(check_health==1)
    {
       // QLabel *show = new QLabel(this);
        ui->show->setGeometry(190,400,300,100);
        ui->show->setText(tr("Game End!"));
        ui->show->setFont(QFont("Ubuntu",35));
        ui->show->show();
    }
}
int  MainWindow::add=0;
int  MainWindow::get_health=200;
int  MainWindow::check_health=0;
int  MainWindow::get_character_health=0;
int  MainWindow::check_character_health=0;































