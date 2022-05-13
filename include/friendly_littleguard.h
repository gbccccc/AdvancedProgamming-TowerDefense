#ifndef LITTLEGUARD_H
#define LITTLEGUARD_H

#include "friendly.h"

class FrdLittleGuard : public Friendly
{
private:
    bool attack(Enemy *enm);
public:
    FrdLittleGuard(CellLoc loc, Dir dir, GameMap &gmp);

    void update();
    void update_range();

    void paint(QPainter &painter);
    void draw_attack_effect(QPainter &painter);
};

#endif // LITTLEGUARD_H
