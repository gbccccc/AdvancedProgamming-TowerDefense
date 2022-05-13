#ifndef FRDGUARDMOTHER_H
#define FRDGUARDMOTHER_H

#include "friendly.h"

class Game;

class FrdGuardMother : public Friendly
{
private:
    Game *game;
    bool attack(Enemy *enm);
    bool attack(CellLoc loc);
public:
    FrdGuardMother(CellLoc loc, Dir dir, GameMap &gmp, Game *game);

    void update();
    void update_range();

    void paint(QPainter &painter);
    void draw_attack_effect(QPainter &painter);
};

#endif // FRDGUARDMOTHER_H
