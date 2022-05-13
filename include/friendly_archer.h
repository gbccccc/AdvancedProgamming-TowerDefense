#ifndef FRDARCHER_H
#define FRDARCHER_H

#include "friendly.h"

class FrdArcher : public Friendly
{
private:
    bool attack(Enemy *enm);
public:
    FrdArcher(CellLoc loc, Dir dir, GameMap &gmp);

    void update();
    void update_range();

    void paint(QPainter &painter);
    void draw_attack_effect(QPainter &painter);
};

#endif // FRDARCHER_H
