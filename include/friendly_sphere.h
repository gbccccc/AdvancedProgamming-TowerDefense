#ifndef FRIENDLY_SPHERE_H
#define FRIENDLY_SPHERE_H

#include<QPainter>
#include "friendly.h"
#include "enemy.h"

class FrdSphere : public Friendly
{
private:
    bool attack(Enemy *enm);
public:
    FrdSphere(CellLoc loc, Dir dir, GameMap &gmp);

    void update();
    void update_range();

    void paint(QPainter &painter);
    void draw_attack_effect(QPainter &painter);

};

#endif // FRIENDLY_SPHERE_H
