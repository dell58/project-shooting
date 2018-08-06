#ifndef ENEMY_H
#define ENEMY_H
#include "Boss.h"


class Enemy:public Boss
{
public:
    Enemy();
public slots:
  virtual  void  random_move();
  virtual  void  check_hit();
  virtual  void  check_hit2();



};

#endif // ENEMY_H
