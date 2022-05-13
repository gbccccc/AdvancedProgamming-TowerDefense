#ifndef FRDBOOMER_H
#define FRDBOOMER_H

#include "friendly.h"

class FrdBomber : public Friendly
{
private:
    bool attack(Enemy *enm);
public:
    FrdBomber(CellLoc loc, Dir dir, GameMap &gmp);

    void update();
    void update_range();

    void paint(QPainter &painter);
    void draw_attack_effect(QPainter &painter);
};

#endif // FRDBOOMER_H
