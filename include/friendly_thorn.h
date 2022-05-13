#ifndef FRDTHORN_H
#define FRDTHORN_H

#include "friendly.h"

class FrdThorn : public Friendly
{
private:
    bool attack(Enemy *enm);
public:
    FrdThorn(CellLoc loc, Dir dir, GameMap &gmp);

    void update();
    void update_range();

    void paint(QPainter &painter);
    void draw_attack_effect(QPainter &painter);
};

#endif // FRDTHORN_H
