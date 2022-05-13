#ifndef BUFFDAMAGEUP_H
#define BUFFDAMAGEUP_H

#include "buff.h"

class buffDamageUp : public Buff
{
public:
    buffDamageUp(Enemy *enm, unsigned length);
    ~buffDamageUp();

    void add_buff(Enemy *enm);
    void rm_buff(Enemy *enm);
};

#endif // BUFFDAMAGEUP_H
