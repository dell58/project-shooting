#include "skill.h"
#include "mainwindow.h"

Skill::Skill()
{

}

void Skill::fly()
{
    setPos(x(), y() - 4);
    if(y() < 0) {
        this->scene()->removeItem(this);
        delete this;
    }
}

