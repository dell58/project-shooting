#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>


class bullet : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
    bullet();

public slots:
     virtual void fly();
     virtual void random_move();
     virtual void  check_hit();
     virtual void  check_hit2();

};

#endif // BULLET_H
