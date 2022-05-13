#ifndef FRDAXE_H
#define FRDAXE_H

#include "friendly.h"

class FrdAxe : public Friendly
{
private:
    bool attack(Enemy *enm);
public:
    FrdAxe(CellLoc loc, Dir dir, GameMap &gmp);

    void update();
    void update_range();

    void paint(QPainter &painter);
    void draw_attack_effect(QPainter &painter);
};

#endif // FRDAXE_H
