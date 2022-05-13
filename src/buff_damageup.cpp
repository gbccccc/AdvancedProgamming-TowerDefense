#include "buff_damageup.h"

buffDamageUp::buffDamageUp(Enemy *enm, unsigned length):
    Buff(enm, length)
{
    add_buff(enm);
}

buffDamageUp::~buffDamageUp()
{

}

void buffDamageUp::add_buff(Enemy *enm)
{
    change_enemy_damage(enm, 1.25);
}

void buffDamageUp::rm_buff(Enemy *enm)
{
    change_enemy_damage(enm, 0.8);
}
