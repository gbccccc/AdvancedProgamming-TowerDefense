#ifndef FRIENDLY_GUARD_H
#define FRIENDLY_GUARD_H

#include "friendly.h"

class FrdGuard : public Friendly
{
private:
    bool attack(Enemy *enm);
public:
    FrdGuard(CellLoc loc, Dir dir, GameMap &gmp);

    void update();
    void update_range();

    void paint(QPainter &painter);
    void draw_attack_effect(QPainter &painter);
};

#endif // FRIENDLY_GUARD_H
