#ifndef BUFF_H
#define BUFF_H

#include "enemy.h"

class Buff
{
public:
    Buff(Enemy *enm, unsigned length);
    virtual ~Buff() = 0;

    void resume_time_set();
    bool update();

    virtual void rm_buff(Enemy *enm) = 0;

    void change_enemy_damage(Enemy *enm, double times) {enm->damage *= times;}

private:
    Enemy *enm;
    unsigned length;
    unsigned beginTime;
    unsigned lastUpdateTime;
};

#endif // BUFF_H
